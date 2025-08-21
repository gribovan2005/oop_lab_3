#include "HistoryCommand.h"

#include "ManagerSolution.h"

SaveStateCommand::SaveStateCommand(int id)
{
    objectId = id;
}
void SaveStateCommand::execute()
{
    auto manager = ManagerSolution::getHistoryManager();
    manager->saveState(objectId);
}

RestoreStateCommand::RestoreStateCommand(int id)
{
    objectId = id;
}
void RestoreStateCommand::execute()
{
    auto manager = ManagerSolution::getHistoryManager();
    manager->getPrevState(objectId);
}


void SaveCompositeStateCommand::execute()
{
    auto manager = ManagerSolution::getHistoryManager();
    manager->saveCompositeState();
}


void RestoreCompositeStateCommand::execute()
{
    auto manager = ManagerSolution::getHistoryManager();
    manager->restoreCompositeState();
}