#pragma once

#include<vector>
#include "Vector3.h"
#include "Object.h"
namespace Physics
{
    using GameLogic::Vector3;
    using GameLogic::PhysicsComponent;
    const double Gravity = 0.01;
    class PhysicsFunction
    {
    public:
        /// <summary>
        /// calculate ray cast
        /// </summary>
        /// <param name="startPoint">input of the point ray started</param>
        /// <param name="direction">input of the vector direction</param>
        /// <param name="hitOne">if hit, return the object hit</param>
        /// <param name="point">if hit, give the point hit</param>
        /// <returns>if get hit</returns>
        static bool doRaycast(const Vector3& startPoint, const Vector3& direction, const PhysicsComponent*& hitOne, const Vector3*& point);

        static void updateObject(GameLogic::LogicObject* object);

        static void physicsUpdate();
    };

}
