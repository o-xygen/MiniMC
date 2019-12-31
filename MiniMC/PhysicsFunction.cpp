#include "CubicRoom.h"
#include "PhysicsFunction.h"
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
}
