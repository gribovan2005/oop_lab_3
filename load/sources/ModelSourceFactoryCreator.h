
#ifndef MODELSOURCEFACTORYCREATOR_H
#define MODELSOURCEFACTORYCREATOR_H

#include <memory>
#include <type_traits>

#include "ModelSourceFactory.h"

template <typename Derived, typename Base>
concept Derivative = std::is_base_of_v<Base, Derived> && !std::is_same_v<Base, Derived>;

template <typename Type>
concept NotAbstract = !std::is_abstract_v<Type>;

class AbstractFactoryCreator
{
public:
    virtual ~AbstractFactoryCreator() = default;
    virtual std::unique_ptr<ModelSourceFactory> createFactory() const = 0;
};

template <Derivative<ModelSourceFactory> TFactory>
requires NotAbstract<TFactory>
class ConcreteFactoryCreator : public AbstractFactoryCreator
{
public:
    std::unique_ptr<ModelSourceFactory> createFactory() const override
    {
        return std::make_unique<TFactory>();
    }
};

class ModelSourceFactoryCreatorMaker
{
public:
    template <Derivative<ModelSourceFactory> TFactory>
    requires NotAbstract<TFactory>
    static std::unique_ptr<AbstractFactoryCreator> create()
    {
        return std::make_unique<ConcreteFactoryCreator<TFactory>>();
    }
};

#endif 
