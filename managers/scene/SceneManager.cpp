#include "SceneManager.h"
#include <QDebug>
SceneManager::SceneManager() : scene_(std::make_shared<Scene>())
{}

std::shared_ptr<Scene> SceneManager::getScene() const
{
    return scene_;
}

void SceneManager::setScene(const std::shared_ptr<Scene> &scene)
{
    scene_ = scene;
}

std::shared_ptr<BaseObject> SceneManager::getObject(int objId)
{
    return scene_->getObject(objId);
}

bool SceneManager::removeObject(int objectId)
{
    return scene_->removeObject(objectId);
}

int SceneManager::addObject(const std::shared_ptr<BaseObject> &object)
{
    return scene_->addObject(object);
}


void SceneManager::comp_objects(std::vector<int> &Object_ids)
{
    scene_->comp_objs(Object_ids);
}

