#ifndef CSVEDGESOURCEFACTORY_H
#define CSVEDGESOURCEFACTORY_H

#include "ModelSourceFactory.h"


class CSVEdgeSourceFactory : public ModelSourceFactory
{
public:
    virtual std::shared_ptr<ModelSource> create(const std::string &path) override;
};

#endif 
