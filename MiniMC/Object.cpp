#include "Object.h"
#include "CubicRoom.h"
namespace GameLogic {

    LogicObject::LogicObject():position(),rotation(){
        physicsObject = new PhysicsComponent(this);
        renderObject = new RenderComponent(this);
    }
    LogicObject::~LogicObject() {
        delete physicsObject;
        delete renderObject;
    }
    void LogicObject::setPosition(double x, double y, double z) {
        this->position.x = x;
        this->position.y = y;
        this->position.z = z;
        physicsObject->setIntoMap();
        renderObject->setPosition(x, y, z);
    }
    void LogicObject::setPosition(const Vector3& vec) {
        this->position = vec;
        physicsObject->setIntoMap();
        renderObject->setPosition(vec.x, vec.y, vec.z);
    }
    void LogicObject::setRotation(double x, double y, double z) {
        double* array = renderObject->demoBlock.rotate;
        array[0] = x;
        array[1] = y;
        array[2] = z;
    }
    PhysicsComponent::PhysicsComponent(LogicObject* parent):
        logicObject(parent),
        isRigid(true),
        isTerrain(true),
        physicsParent(nullptr){

    }
    void PhysicsComponent::setIntoMap() {
        Vector3 localPosition = this->logicObject->position - Physics::CubicRoom::offset;
        int x = (int)floorl(localPosition.x);
        int y = (int)floorl(localPosition.y);
        int z = (int)floorl(localPosition.z);
        this->physicsParent = Physics::CubicRoom::map[x][y][z];
        Physics::CubicRoom::map[x][y][z]->list.push_back(this);
    }
    RenderComponent::RenderComponent(LogicObject* parent):logicObject(parent) {

    }

    void RenderComponent::setPosition(double x, double y, double z) {
        demoBlock.position[0] = x;
        demoBlock.position[1] = y;
        demoBlock.position[2] = z;

    }
}