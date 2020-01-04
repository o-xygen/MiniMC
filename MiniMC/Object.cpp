#include "Object.h"
#include "CubicRoom.h"
namespace GameLogic {

    LogicObject::LogicObject(bool isStatic) :position(), renderObject(nullptr) {
        this->isStatic = isStatic;
        physicsObject = new PhysicsComponent(this);
        if (isStatic)
        {
            renderObject = new StaticRenderer(this);
        }
        else
        {
            //TODO: for dynamic objects in future
        }
    }
    LogicObject::~LogicObject() {
        delete physicsObject;
        if (renderObject)
        {
            delete renderObject;
        }
    }
    void LogicObject::setPosition(double x, double y, double z) {
        this->position.x = x;
        this->position.y = y;
        this->position.z = z;
        physicsObject->setIntoMap();
        if (isStatic)
        {
            StaticRenderer* staticRenderer = static_cast<StaticRenderer*>(renderObject);
            staticRenderer->mapX = x;
            staticRenderer->mapY = y;
            staticRenderer->mapZ = z;
        }
        else
        {
            //TODO: for dynamic objects in future
        }
    }
    void LogicObject::setPosition(const Vector3& vec) {
        setPosition(vec.x, vec.y, vec.z);
    }
    PhysicsComponent::PhysicsComponent(LogicObject* parent):
        logicObject(parent),
        isRigid(true),
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

    StaticRenderer::StaticRenderer(LogicObject* parent):RenderComponent(parent)
    {
    }
}