#include "CubicRoom.h"
#include "PhysicsFunction.h"
#include "LogicWorld.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Physics
{
    const double Gravity = 0.01;
    const double Friction = 0.01;
    const float moveSpeed = 0.05f;
    const double jumpSpeed = 0.2;
    using GameLogic::Vector3;
    static bool checkIn(const Vector3& point, const Vector3& minBound, const Vector3& maxBound)
    {
#define clamp(x, y, z) (x <= y && y <= z)
        return clamp(minBound.x, point.x, maxBound.x) && clamp(minBound.y, point.y, maxBound.y) && clamp(minBound.z, point.z, maxBound.z);
    }

    bool PhysicsFunction::doRaycast(const Vector3& startPoint, const Vector3& direction, const PhysicsComponent*& hitOne, const Vector3*& point)
    {
        static Vector3 res;
        if (direction.x == 0 && direction.y == 0 && direction.z == 0)
        {
            return false;
        }

        Vector3 hitPoint;
        int counter;
        double delta[2] = {};
        Vector3 trueHitPoint[2], bound[2], *position;

        double minDelta = DBL_MAX;
        for (int x = 0; x < CubicRoom::mapLengthX; ++x)
        {
            for (int y = 0; y < CubicRoom::mapLengthY; ++y)
            {
                for (int z = 0; z < CubicRoom::mapLengthZ; ++z)
                {
                    CubicRoom* cube = CubicRoom::map[x][y][z];
                    for (PhysicsComponent* unit : cube->list)
                    {
                        position = &unit->logicObject->position;
                        bound[0] = *position - Vector3{ 0.5,0.5,0.5 };
                        bound[1] = *position + Vector3{ 0.5,0.5,0.5 };

                        counter = 0;
                        if (direction.x != 0)
                        {
                            for (int i = 0; i < 2; ++i) {
                                double t = (bound[i].x - startPoint.x) / direction.x;
                                if (t <= 0)
                                    continue;
                                hitPoint.x = bound[i].x;
                                hitPoint.y = startPoint.y + t * direction.y;
                                hitPoint.z = startPoint.z + t * direction.z;
                                if (checkIn(hitPoint, bound[0], bound[1]))
                                {
                                    delta[counter] = t;
                                    trueHitPoint[counter++] = hitPoint;
                                    if (counter == 2)
                                        goto getTwoHitPoint;
                                }
                            }
                        }
                        if (direction.y != 0)
                        {
                            for (int i = 0; i < 2; ++i) {
                                double t = (bound[i].y - startPoint.y) / direction.y;
                                if (t <= 0)
                                    continue;
                                hitPoint.x = startPoint.x + t * direction.x;
                                hitPoint.y = bound[i].y;
                                hitPoint.z = startPoint.z + t * direction.z;
                                if (checkIn(hitPoint, bound[0], bound[1]))
                                {
                                    delta[counter] = t;
                                    trueHitPoint[counter++] = hitPoint;
                                    if (counter == 2)
                                        goto getTwoHitPoint;
                                }
                            }
                        }
                        if (direction.z != 0)
                        {
                            for (int i = 0; i < 2; ++i) {
                                double t = (bound[i].z - startPoint.z) / direction.z;
                                if (t <= 0)
                                    continue;
                                hitPoint.x = startPoint.x + t * direction.x;
                                hitPoint.y = startPoint.y + t * direction.y;
                                hitPoint.z = bound[i].z;
                                if (checkIn(hitPoint, bound[0], bound[1]))
                                {
                                    delta[counter] = t;
                                    trueHitPoint[counter++] = hitPoint;
                                    if (counter == 2)
                                        goto getTwoHitPoint;
                                }
                            }
                        }

                    getTwoHitPoint:
                        if (counter == 1)
                            continue;
                        if (delta[0] > delta[1])
                        {
                            delta[0] = delta[1];
                            trueHitPoint[0] = trueHitPoint[1];
                        }
                        if (delta[0] > minDelta)
                        {
                            minDelta = delta[0];
                            res = trueHitPoint[0];
                            hitOne = unit;
                        }
                    }
                }
            }
        }
        if (minDelta != DBL_MAX)
        {
            point = &res;
            return true;
        }
        return false;
    }

    /*void Physics::changeVelocity()
    {
        
    }*/
    inline void clampIndex(double& velocity, int& max, int& min, int index, int maxIndex, double& minusV, double& posV)
    {
        if (velocity < 0)
        {
            if (index - 1 >= 0)
            {
                min = max - 1;
            }
            minusV = velocity;
        }
        else if (velocity > 0)
        {
            if (index + 1 < maxIndex)
            {
                max = min + 1;
            }
            posV = velocity;
        }
    }
    inline void giveFriction(double& value, double friction)
    {
        if (value <= -friction)
        {
            value += -friction;
        }
        else if (value >= friction)
        {
            value -= friction;
        }
        else
        {
            value = 0;
        }
    }
    void PhysicsFunction::physicsUpdate()
    {
        /*
        for(LogicObject* object : dynamicObjects)
        {

        }
        */

        //update player
        PhysicsComponent* playerPhysics = GameLogic::WorldControler::player->physicsObject;
        CubicRoom* cube = static_cast<Physics::CubicRoom*>(playerPhysics->physicsParent);
        Vector3& velocity = playerPhysics->velocity;

        int minX = cube->indexX, maxX = cube->indexX, minY = cube->indexY, maxY = cube->indexY, minZ = cube->indexZ, maxZ = cube->indexZ;
        velocity.y -= Gravity;
        Vector3 divideVelocity[2]{};//0 -> -,1 -> +
        clampIndex(velocity.x, maxX, minX, cube->indexX, CubicRoom::mapLengthX, divideVelocity[0].x, divideVelocity[1].x);
        clampIndex(velocity.y, maxY, minY, cube->indexY, CubicRoom::mapLengthY, divideVelocity[0].y, divideVelocity[1].y);
        clampIndex(velocity.z, maxZ, minZ, cube->indexZ, CubicRoom::mapLengthZ, divideVelocity[0].z, divideVelocity[1].z);
        Vector3 targetPosition = GameLogic::WorldControler::player->position + velocity;
        for (int x = minX, y, z; x <= maxX; ++x)
        {
            for (y = minY; y <= maxY; ++y)
            {
                for (z = minZ; z <= maxZ; ++z)
                {
                    for (PhysicsComponent* object : CubicRoom::map[x][y][z]->list)
                    {
                        if (object != playerPhysics)
                        {
                            const Vector3& otherPosition = object->logicObject->position;
                            Vector3 range[2]
                            {
                                otherPosition + object->bound[0] - playerPhysics->bound[1],
                                otherPosition + object->bound[1] - playerPhysics->bound[0]
                            };
                            if (range[0] <= targetPosition && targetPosition <= range[1])
                            {
#define NO_BIGGER(a,b,c,d) \
    if(a <= b && b < c){\
        b = a;\
        d = 0;\
    }
#define NO_SMALLER(a,b,c,d) \
    if(a < b && b <= c){\
        b = c;\
        d = 0;\
    }
                                NO_BIGGER(range[0].x, targetPosition.x, otherPosition.x, divideVelocity[1].x);
                                NO_BIGGER(range[0].y, targetPosition.y, otherPosition.y, divideVelocity[1].y);
                                NO_BIGGER(range[0].z, targetPosition.z, otherPosition.z, divideVelocity[1].z);
                                NO_SMALLER(otherPosition.x, targetPosition.x, range[1].x, divideVelocity[0].x);
                                if (otherPosition.y < targetPosition.y && targetPosition.y <= range[1].y) {
                                    targetPosition.y = range[1].y;
                                    divideVelocity[0].y = 0;
                                    GameLogic::WorldControler::onTheGround = true;
                                }
                                else
                                {
                                    GameLogic::WorldControler::onTheGround = false;
                                }
                                NO_SMALLER(otherPosition.z, targetPosition.z, range[1].z, divideVelocity[0].z);
                            }
                        }
                    }
                }
            }
        }
        velocity = divideVelocity[0] + divideVelocity[1];
        playerPhysics->logicObject->position = targetPosition;

        double rad = glm::radians(GameLogic::WorldControler::playerForward[0]);
        giveFriction(velocity.x, abs(sin(rad)) * Friction);
        giveFriction(velocity.z, abs(cos(rad)) * Friction);
    }
    void PhysicsFunction::updateObject(GameLogic::LogicObject* object) {
        CubicRoom* cube = (CubicRoom*)object->physicsObject->physicsParent;
        if (object->physicsObject->velocity == Vector3{0, 0, 0}) {

        }
        else {

        }
    }
}
