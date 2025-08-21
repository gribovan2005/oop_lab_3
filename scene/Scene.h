#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "BaseObject.h"
#include "ObjectComposite.h"

class Scene
{
public:
    Scene();
    ~Scene() = default;

    int addObject(const std::shared_ptr<BaseObject> &obj);
    bool removeObject(const int id);
    std::shared_ptr<BaseObject> getObject(int objectId);
    void comp_objs(std::vector<int> &ObjectIds);

    Iterator begin();
    Iterator end();

    void accept(BaseVisitor& v);

    std::shared_ptr<BaseObject> get_composite();
private:
    ObjectMap objects_;
    int objCount = 0;
    std::shared_ptr<ObjectComposite> composit;
};

#endif 
