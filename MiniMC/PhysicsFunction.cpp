#include "CubicRoom.h"
#include "PhysicsFunction.h"
#include "LogicWorld.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Physics
{
    const double Gravity = 0.01;
    const double Friction = 0.001;
    const float moveSpeed = 0.1f;
    const double jumpSpeed = 0.2;
    bool isMoving = false;
    using GameLogic::Vector3;
    static bool checkIn(const Vector3& point, const Vector3& minBound, const Vector3& maxBound)
    {
#define clamp(x, y, z) (x <= y && y <= z)
        return clamp(minBound.x, point.x, maxBound.x) && clamp(minBound.y, point.y, maxBound.y) && clamp(minBound.z, point.z, maxBound.z);
    }

    bool PhysicsFunction::doRaycast(const Vector3& startPoint, const Vector3& direction, PhysicsComponent*& hitOne, Vector3*& point)
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
        Vector3 origin = startPoint - CubicRoom::offset;
        origin.x = round(origin.x);
        origin.y = round(origin.y);
        origin.z = round(origin.z);
        int startX = (int)origin.x - 3, startY = (int)origin.y - 3, startZ = (int)origin.z - 3;
        int endX = (int)origin.x + 3, endY = (int)origin.y + 3, endZ = (int)origin.z + 3;
        if (startX < 0)
            startX = 0;
        if (startY < 0)
            startY = 0;
        if (startZ < 0)
            startZ = 0;

        if (endX > CubicRoom::mapLengthX)
            endX = CubicRoom::mapLengthX;
        if (endY > CubicRoom::mapLengthY)
            endY = CubicRoom::mapLengthY;
        if (endZ > CubicRoom::mapLengthZ)
            endZ = CubicRoom::mapLengthZ;

        for (int x = startX; x < endX; ++x)
        {
            for (int y = startY; y < endY; ++y)
            {
                for (int z = startZ; z < endZ; ++z)
                {
                    CubicRoom* cube = CubicRoom::map[x][y][z];
                    for (PhysicsComponent* unit : cube->list)
                    {
                        position = &unit->logicObject->position;
                        bound[0] = *position + unit->bound[0];
                        bound[1] = *position + unit->bound[1];

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
                        if (counter < 2)
                            continue;
                        if (delta[0] > delta[1])
                        {
                            delta[0] = delta[1];
                            trueHitPoint[0] = trueHitPoint[1];
                        }
                        if (delta[0] < minDelta)
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
    constexpr void clampIndex(double& velocity, int& max, int& min, int index, int maxIndex)
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
    constexpr void giveFriction(double& value, double friction)
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
    template<typename T>
    constexpr T LineHitOnXFace(const T& pointA, T& pointB, double& xFace, const T& velocity)
    {
        double temp = (xFace - pointA.x) / velocity.x;
        return T{ xFace, pointA.y + velocity.y * temp, pointA.z + velocity.z * temp };
    }
    template<typename T>
    constexpr T LineHitOnYFace(const T& pointA, T& pointB, double& yFace, const T& velocity)
    {
        double temp = (yFace - pointA.y) / velocity.y;
        return T{ pointA.x + velocity.x * temp, yFace, pointA.z + velocity.z * temp };
    }
    template<typename T>
    constexpr T LineHitOnZFace(const T& pointA, T& pointB, double& zFace, const T& velocity)
    {
        double temp = (zFace - pointA.z) / velocity.z;
        return T{ pointA.x + velocity.x * temp, pointA.y + velocity.y * temp, zFace };
    }
#define inFace(X,y,z) \
    constexpr bool in##X##face(const Vector3& a, const Vector3& b, const Vector3& target)\
    {\
        return a.y < target.y && target.y < b.y && a.z < target.z && target.z < b.z;\
    }
    //inFace(X, y, z)
    constexpr bool inXface(const Vector3& a, const Vector3& b, const Vector3& target)
    {
        return a.y < target.y && target.y < b.y && a.z < target.z && target.z < b.z;
    }
    constexpr bool inYface(const Vector3& a, const Vector3& b, const Vector3& target)
    {
        return a.x <= target.x && target.x <= b.x && a.z <= target.z && target.z <= b.z;
    }
    constexpr bool inZface(const Vector3& a, const Vector3& b, const Vector3& target)
    {
        return a.x < target.x && target.x < b.x && a.y < target.y && target.y < b.y;
    }
    //inFace(Z, x, y)
    void checkInRange(Vector3& position)
    {
        if(position.x < 0)
        {
            position.x = 0;
        }
        else if(position.x > CubicRoom::mapLengthX + CubicRoom::offset.x)
        {
            position.x = CubicRoom::mapLengthX + CubicRoom::offset.x;
        }
        if(position.y < 0)
        {
            position.y = 0;
        }
        else if(position.y > CubicRoom::mapLengthY + CubicRoom::offset.y)
        {
            position.y = CubicRoom::mapLengthY + CubicRoom::offset.y;
        }
        if(position.z < 0)
        {
            position.z = 0;
        }
        else if(position.z > CubicRoom::mapLengthZ + CubicRoom::offset.z)
        {
            position.z = CubicRoom::mapLengthZ + CubicRoom::offset.z;
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
        clampIndex(velocity.x, maxX, minX, cube->indexX, CubicRoom::mapLengthX);
        clampIndex(velocity.y, maxY, minY, cube->indexY, CubicRoom::mapLengthY);
        clampIndex(velocity.z, maxZ, minZ, cube->indexZ, CubicRoom::mapLengthZ);
        const Vector3& originPosition = GameLogic::WorldControler::player->position;
        Vector3 targetPosition = GameLogic::WorldControler::player->position + velocity;

        GameLogic::WorldControler::onTheGround = false;
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
                            double distance = Vector3::sqrLength(velocity);

#define CheckOneFace(num,x,X)\
                            if (0 <= (range[num].x - originPosition.x) * (targetPosition.x - range[num].x) && targetPosition.x != range[num].x)\
                            {\
                                Vector3 hitPoint = LineHitOn##X##Face(originPosition, targetPosition, range[num].x, velocity);\
                                if (in##X##face(range[0], range[1], hitPoint))\
                                {\
                                    Vector3 temp = targetPosition;\
                                    temp.x = hitPoint.x;\
                                    double newDistance = Vector3::sqrDistance(temp, originPosition);\
                                    if (newDistance < distance)\
                                    {\
                                        targetPosition.x = hitPoint.x;\
                                        velocity.x = hitPoint.x - originPosition.x;\
                                        distance = newDistance;\
                                        GameLogic::WorldControler::onTheGround = true;\
                                        goto NextObject;\
                                    }\
                                }\
                            }

                            if (velocity.y != 0)
                            {
                                CheckOneFace(0, y, Y);
                                //CheckOneFace(1, y, Y);
                                if (0 <= (range[1].y - originPosition.y) * (targetPosition.y - range[1].y) && targetPosition.y != range[1].y)
                                {
                                    Vector3 hitPoint = LineHitOnYFace(originPosition, targetPosition, range[1].y, velocity);
                                    if (inYface(range[0], range[1], hitPoint))
                                    {
                                        Vector3 temp = targetPosition;
                                        temp.y = hitPoint.y;
                                        double newDistance = Vector3::sqrDistance(temp, originPosition);
                                        if (newDistance < distance)
                                        {
                                            targetPosition.y = hitPoint.y;
                                            velocity.y = hitPoint.y - originPosition.y;
                                            distance = newDistance;
                                            GameLogic::WorldControler::onTheGround = true;
                                            goto NextObject;
                                        }
                                    }
                                }
                            }
                            if (velocity.x != 0)
                            {
                                CheckOneFace(0, x, X);
                                CheckOneFace(1, x, X);
                            }
                            if (velocity.z != 0)
                            {
                                CheckOneFace(0, z, Z);
                                CheckOneFace(1, z, Z);
                            }
                        }
                    NextObject:
                        ;
                    }
                }
            }
        }
        checkInRange(targetPosition);
        if(targetPosition < cube->range[0] || cube->range[1] < targetPosition)
        {
            for (auto i = cube->list.begin(); i != cube->list.end(); ++i)
            {
                if(*i == playerPhysics)
                {
                    cube->list.erase(i);
                    break;
                }
            }
            GameLogic::WorldControler::player->setPosition(targetPosition);
        }
        else
        {
            playerPhysics->logicObject->position = targetPosition;
        }
        if (velocity.x != 0 || velocity.z != 0)
        {
            static int counter = 0;
            counter = (counter << 1 | isMoving) & 0xfff;
            if (!counter) {
                velocity.x = velocity.z = 0;
            }
            /*if(-Friction <= velocity.x && velocity.x <= Friction)
            {
                velocity.x = 0;
            }
            if(-Friction <= velocity.z && velocity.z <= Friction)
            {
                velocity.z = 0;
            }*/
            //giveFriction(velocity.x, abs(velocity.x * Friction));
            //giveFriction(velocity.z, abs(velocity.z * Friction));
        }
        isMoving = false;
    }
    void PhysicsFunction::updateObject(GameLogic::LogicObject* object) {
        CubicRoom* cube = (CubicRoom*)object->physicsObject->physicsParent;
        if (object->physicsObject->velocity == Vector3{0, 0, 0}) {

        }
        else {

        }
    }
}
