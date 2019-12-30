#include"Object.h"
namespace DataType {

    LogicObject::LogicObject(){
        physicsObject = new PhysicsComponent(this);
        renderObject = new RenderComponent(this);
    }
    LogicObject::~LogicObject() {
        delete physicsObject;
        delete renderObject;
    }
    PhysicsComponent::PhysicsComponent(LogicObject* parent):logicObject(parent), isRigid(CubePhysicsType::RigidBody){

    }
    RenderComponent::RenderComponent(LogicObject* parent):logicObject(parent) {

    }
}