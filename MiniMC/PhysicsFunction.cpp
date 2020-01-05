#include "CubicRoom.h"
#include "PhysicsFunction.h"
#include "LogicWorld.h"

namespace Physics
{
    const double gravity[3]{ 0,-5,0 };
    const double JumpVelocity[3]{ 0, 8, 0 };
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
        for (int x = 0; x < CubicRoom::x; ++x)
        {
            for (int y = 0; y < CubicRoom::y; ++y)
            {
                for (int z = 0; z < CubicRoom::z; ++z)
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
    inline void clampIndex(double&velocity, int max, int min,int index,int maxIndex)
    {
        if (velocity < 0)
        {
            if (index - 1 >= 0)
            {
                min = max - 1;
            }
        }
        else if (velocity > 0)
        {
            if (index + 1 < maxIndex)
            {
                max = min + 1;
            }
        }
    }
    inline void giveFriction(double& value)
    {
        const static double friction = 0.01;
        if (value <= friction)
        {
            value += friction;
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
        int indexX = cube->x, indexY = cube->y, indexZ = cube->z;
        Vector3& velocity = playerPhysics->velocity;
        //TODO: velocity shouldn't be too fast to check collision
        if (!GameLogic::WorldControler::onTheGround)
        {
            Vector3 targetPosition = GameLogic::WorldControler::player->position + velocity;
            int minX = indexX, maxX = indexX, minY = indexY, maxY = indexY, minZ = indexZ, maxZ = indexZ;
            clampIndex(velocity.x, maxX, minX, indexX, CubicRoom::x);
            clampIndex(velocity.y, maxY, minY, indexY, CubicRoom::y);
            clampIndex(velocity.z, maxZ, minZ, indexZ, CubicRoom::z);
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

                            }
                        }
                    }
                }
            }
            giveFriction(velocity.x);
            giveFriction(velocity.z);
            velocity.y += Gravity;
        }
        else
        {

            //may jump
        }

    }
    void PhysicsFunction::updateObject(GameLogic::LogicObject* object) {
        CubicRoom* cube = (CubicRoom*)object->physicsObject->physicsParent;
        if (object->physicsObject->velocity == Vector3{0, 0, 0}) {

        }
        else {

        }
    }
}
