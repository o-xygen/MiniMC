#pragma once
#include "Vector3.h"
#include "demoBlock.h"
namespace DataType {
    class CubeRoom;
    class PhysicsComponent;
    class RenderComponent;
    class LogicObject {
    public:
        LogicObject();
        ~LogicObject();
        Vector3 position;
        PhysicsComponent*physicsObject;
        RenderComponent*renderObject;
    };
    class PhysicsComponent
    {
        friend class LogicObject;
        PhysicsComponent(LogicObject* parent);
    public:
        Vector3 velocity;
        enum CubePhysicsType
        {
            RigidBody, NonRigidBody
        }isRigid;
        LogicObject* logicObject;
    };
    class RenderComponent {
        friend class LogicObject;
        RenderComponent(LogicObject* parent);
    public:
        DemoBlock demoBlock;
        LogicObject* logicObject;
    };
}