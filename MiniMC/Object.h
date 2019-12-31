#pragma once
#include "Vector3.h"
#include "demoBlock.h"
namespace GameLogic {
    class PhysicsComponent;
    class RenderComponent;
    class LogicObject {
    public:
        LogicObject();
        ~LogicObject();
        Vector3 position;//first translate, then rotate.
        Vector3 rotation;
        void setPosition(double x,double y, double z);
        void setPosition(const Vector3& vec);
        void setRotation(double x, double y, double z);

        PhysicsComponent*physicsObject;
        RenderComponent*renderObject;
    };
    class PhysicsComponent
    {
        friend class LogicObject;
        PhysicsComponent(LogicObject* parent);
    public:
        void* physicsParent;
        void setIntoMap();

        Vector3 velocity;
        bool isRigid, isTerrain;
        LogicObject* logicObject;
    };
    class RenderComponent {
        friend class LogicObject;
        RenderComponent(LogicObject* parent);
    public:
        void setPosition(double x, double y, double z);
        DemoBlock demoBlock;
        LogicObject* logicObject;
    };
}