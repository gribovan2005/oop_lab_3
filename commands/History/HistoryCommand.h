#ifndef HISTORYCOMMAND_H
#define HISTORYCOMMAND_H

#include <Command.h>

class HistoryCommand : public Command {};

class SaveStateCommand : public HistoryCommand
{
public:
    SaveStateCommand() = delete;
    explicit SaveStateCommand(int id);

    void execute() override;

private:
    int objectId;
};

class RestoreStateCommand : public HistoryCommand
{
public:
    RestoreStateCommand() = delete;
    explicit RestoreStateCommand(int id);

    void execute() override;

private:
    int objectId;
};



class SaveCompositeStateCommand : public HistoryCommand
{
public:
    SaveCompositeStateCommand() = default;

    void execute() override;
};

class RestoreCompositeStateCommand : public HistoryCommand
{
public:
    RestoreCompositeStateCommand() = default;

    void execute() override;
};

#endif 
