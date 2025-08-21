#include "ObjectCommand.h"

#include "ManagerSolution.h"

ObjectDeleteCommand::ObjectDeleteCommand(int id)
{
    objectId = id;
}
void ObjectDeleteCommand::execute()
{
    auto manager = ManagerSolution::getSceneManager();
    manager->removeObject(objectId);
}



ObjectMoveCommand::ObjectMoveCommand(int id, const Vector3 &offset)
{
    objectId = id;
    offset_ = offset;
}
void ObjectMoveCommand::execute()
{
    auto manager = ManagerSolution::getTransformManager();
    manager->move(objectId, offset_);
}


CompositeMoveCommand::CompositeMoveCommand(const Vector3 &offset)
{
    offset_ = offset;
}
void CompositeMoveCommand::execute()
{
    auto manager = ManagerSolution::getTransformManager();
    manager->move_composite(offset_);
}




ObjectRotateCommand::ObjectRotateCommand(int id, const Vector3 &rotation)
{
    objectId = id;
    rotation_ = rotation;
}
void ObjectRotateCommand::execute()
{
    auto manager = ManagerSolution::getTransformManager();
    manager->rotate(objectId, rotation_);
}



CompositeRotateCommand::CompositeRotateCommand(const Vector3 &offset)
{
    offset_ = offset;
}
void CompositeRotateCommand::execute()
{
    auto manager = ManagerSolution::getTransformManager();
    manager->rotate_composite(offset_);
}





ObjectScaleCommand::ObjectScaleCommand(int id, const Vector3 &scale)
{
    objectId = id;
    scale_ = scale;
}
void ObjectScaleCommand::execute()
{
    auto manager = ManagerSolution::getTransformManager();
    manager->scale(objectId, scale_);
}



CompositeScaleCommand::CompositeScaleCommand(const Vector3 &offset)
{
    offset_ = offset;
}
void CompositeScaleCommand::execute()
{
    auto manager = ManagerSolution::getTransformManager();
    manager->scale_composite(offset_);
}