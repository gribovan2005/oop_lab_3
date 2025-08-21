#include "Scene.h"
#include <algorithm>
#include <QDebug>

Scene::Scene() : composit(std::make_shared<ObjectComposite>())
{

}

int Scene::addObject(const std::shared_ptr<BaseObject> &obj)
{
    objects_[objCount++] = obj;

    return objCount - 1;
}

bool Scene::removeObject(int objectId)
{
    return objects_.erase(objectId) > 0;
}

std::shared_ptr<BaseObject> Scene::getObject(int objectId)
{
    return objects_.at(objectId);
}

std::shared_ptr<BaseObject> Scene::get_composite()
{
    return composit;
}


void Scene::accept(BaseVisitor& v)
{
    v.visit(*this);
}


Iterator Scene::begin()
{
    return objects_.begin();
}

Iterator Scene::end()
{
    return objects_.end();
}

void Scene::comp_objs(std::vector<int> &ObjectIds)
{
    composit->clear();

    for (const auto &[id, obj] : this->objects_)
    {
        if (std::ranges::find(ObjectIds, id) != ObjectIds.end())
        {
            composit->add(this->getObject(id));
            
        }
        qDebug() << "In composit: " << id;
    } 
}