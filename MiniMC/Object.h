#pragma once
#include "Vector3.h"
namespace GameLogic {
    class PhysicsComponent;
    class RenderComponent;
    class LogicObject {
    public:
        LogicObject(bool isStatic);
        ~LogicObject();
        Vector3 position;//first translate, then rotate.
        //Vector3 rotation;
        bool isStatic;
        void setPosition(double x, double y, double z);
        void setPosition(const Vector3& vec);
        void setRotation(double x, double y, double z);

        PhysicsComponent* physicsObject;
        RenderComponent* renderObject;
    };
    class PhysicsComponent
    {
        friend class LogicObject;
        PhysicsComponent(LogicObject* parent);
    public:
        void* physicsParent;
        void setIntoMap();

        Vector3 velocity;
        Vector3 bound[2];//[0]->min,[1]->max
        bool isRigid;
        LogicObject* logicObject;
    };
    class RenderComponent {
        friend class LogicObject;
    protected:
        RenderComponent(LogicObject* parent);
    public:
        //void setPosition(double x, double y, double z);
        //DemoBlock demoBlock;

        LogicObject* logicObject;
    };
    class StaticRenderer :public RenderComponent {
        friend class LogicObject;
        StaticRenderer(LogicObject* parent);
    public:
        int mapX, mapY, mapZ;
    };

    class DynamicRenderer :public RenderComponent
    {

    };

}