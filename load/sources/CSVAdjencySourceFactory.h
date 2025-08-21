#ifndef CSVADJENCYSOURCEFACTORY_H
#define CSVADJENCYSOURCEFACTORY_H

#include "ModelSourceFactory.h"
#include "CSVEdgeSource.h"

class CSVAdjencySourceFactory : public ModelSourceFactory
{
public:
    virtual std::shared_ptr<ModelSource> create(const std::string &path) override;
};

#endif 
