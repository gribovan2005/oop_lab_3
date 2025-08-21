#ifndef SCENECOMMAND_H
#define SCENECOMMAND_H

#include <iostream>
#include "Command.h"

class SceneCommand : public Command {};

class SceneRenderCommand : public SceneCommand
{
public:
    SceneRenderCommand() = default;
    void execute() override;
};

class SceneUnionComp : public SceneCommand
{
public:
    SceneUnionComp() = delete;

    SceneUnionComp(std::vector<int> &ids) : Object_ids(ids) {}

    void execute() override;

private:
    std::vector<int> Object_ids;
};


#endif 
