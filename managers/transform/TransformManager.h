#ifndef TRANSFORMMANAGER_H
#define TRANSFORMMANAGER_H

#include <memory>

#include <BaseManager.h>

#include "Vector3.h"

class TransformManager : public BaseManager
{
public:
    TransformManager() = default;
    ~TransformManager() override = default;
    TransformManager(const TransformManager &) = delete;
    TransformManager &operator=(const TransformManager &) = delete;

    void move(int objectId, const Vector3 &param) const;
    void rotate(int objectId, const Vector3 &param) const;
    void scale(int objectId, const Vector3 &param) const;

    void move_composite(const Vector3 &param);
    void rotate_composite(const Vector3 &param);
    void scale_composite(const Vector3 &param);
};

#endif 
