#include "SceneCommand.h"
#include <QDebug>
#include "ManagerSolution.h"

void SceneRenderCommand::execute()
{
    auto manager = ManagerSolution::getDrawManager();
    manager->drawScene();
}


void SceneUnionComp::execute()
{
    auto manager = ManagerSolution::getSceneManager();
    manager->comp_objects(Object_ids);
}