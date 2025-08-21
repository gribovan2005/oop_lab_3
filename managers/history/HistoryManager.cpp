#include "HistoryManager.h"
#include <QDebug>
#include "ManagerSolution.h"

void HistoryManager::getPrevState(int objectId)
{
    auto memento = careTaker.getMemento(objectId);

    auto sceneManager = ManagerSolution::getSceneManager();
    auto obj = sceneManager->getObject(objectId);

    obj->restoreMemento(memento);
}

void HistoryManager::saveState(int objectId)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto obj = sceneManager->getObject(objectId);

    auto data = CareTaker::saveData(obj, obj->createMemento());

    careTaker.setMemento(objectId, data);
}

void HistoryManager::saveCompositeState()
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();

    for (const auto &[id, obj] : *scene->get_composite())
    {
        auto data = CareTaker::saveData(obj, obj->createMemento());
        careTaker.setMemento(id, data);
    }
}

void HistoryManager::restoreCompositeState()
{   
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();

    for (const auto &[id, obj] : *scene->get_composite())
    {
        qDebug() << "object" << id;
        auto memento = careTaker.getMemento(id);
        obj->restoreMemento(memento);
    }
}

