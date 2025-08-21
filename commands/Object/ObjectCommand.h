#ifndef OBJECTCOMMAND_H
#define OBJECTCOMMAND_H

#include "Command.h"

#include "Vector3.h"

class ObjectCommand : public Command {};

class ObjectDeleteCommand : public ObjectCommand
{
public:
    ObjectDeleteCommand() = delete;
    explicit ObjectDeleteCommand(int id);

    void execute() override;

private:
    int objectId;
};


/*
class EdidableCommand
{
    virtual bool execute() override
    {
        // save
        return executeInternal();
    }

    protected:
        virtual bool executeInternal() = 0;
}*/


class ObjectMoveCommand : public ObjectCommand
{
public:
    ObjectMoveCommand() = delete;
    ObjectMoveCommand(int id, const Vector3 &offset);

    void execute() override;

private:
    Vector3 offset_;
    int objectId;
};

class CompositeMoveCommand : public ObjectCommand
{
public:
    CompositeMoveCommand() = delete;
    explicit CompositeMoveCommand(const Vector3 &offset);

    void execute() override;
private:
    Vector3 offset_;
};





class ObjectRotateCommand : public ObjectCommand
{
public:
    ObjectRotateCommand() = delete;

    ObjectRotateCommand(int id, const Vector3 &rotation);

    void execute() override;

private:
    Vector3 rotation_;
    int objectId;
};

class CompositeRotateCommand : public ObjectCommand
{
public:
    CompositeRotateCommand() = delete;
    explicit CompositeRotateCommand(const Vector3 &offset);

    void execute() override;
private:
    Vector3 offset_;
};






class ObjectScaleCommand : public ObjectCommand
{
public:
    ObjectScaleCommand() = delete;

    ObjectScaleCommand(int id, const Vector3 &scale);

    void execute() override;

private:
    Vector3 scale_;
    int objectId;
};

class CompositeScaleCommand : public ObjectCommand
{
public:
    CompositeScaleCommand() = delete;
    explicit CompositeScaleCommand(const Vector3 &offset);

    void execute() override;
private:
    Vector3 offset_;
};



#endif 
