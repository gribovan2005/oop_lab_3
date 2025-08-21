#include "TransformManager.h"

#include "ManagerSolution.h"

#include "TransformationData.h"

void TransformManager::move(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    *object->getTransformation() += MoveData(param);
}

void TransformManager::rotate(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    *object->getTransformation() += RotationData(param);
}

void TransformManager::scale(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    *object->getTransformation() += ScaleData(param);
}

void TransformManager::move_composite(const Vector3 &param)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto composite = scene->get_composite();

    for (const auto &[id, obj] : *composite)
    {
        *obj->getTransformation() += MoveData(param);
    }
}

void TransformManager::rotate_composite(const Vector3 &param)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto composite = scene->get_composite();

    for (const auto &[id, obj] : *composite)
    {
        *obj->getTransformation() += RotationData(param);
    }

}

void TransformManager::scale_composite(const Vector3 &param)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto composite = scene->get_composite();

    for (const auto &[id, obj] : *composite)
    {
        if (obj->isVisible())
        {
            *obj->getTransformation() += ScaleData(param);
        }
    }
}