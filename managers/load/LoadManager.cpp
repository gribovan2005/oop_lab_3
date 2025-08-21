#include "LoadManager.h"
#include <QDebug>
#include "LoadException.h"
#include "ManagerSolution.h"
#include "ModelDirectorSolution.h"
#include "SourceSolution.h"
#include "BuilderSolution.h"


int LoadManager::loadMeshModel(const std::string &path)
{
    auto sceneManager = ManagerSolution::getSceneManager();

    auto scene = sceneManager->getScene();

    auto& solution = SourceSolution::instance(); 

    auto source = solution.create(path);
    
    if (source == nullptr)
        throw WrongSourceError(__FILE__, __LINE__, "Unknown source type");
    
    auto builder = BuilderSolution::create(path, source);
    
    auto director = ModelDirectorSolution::create(ModelType::MeshModel); // посмтреть

    return scene->addObject(director->create(builder));
}
