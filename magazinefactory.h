#ifndef MAGAZINEFACTORY_H
#define MAGAZINEFACTORY_H

#include "iproductfactory.h"

class MagazineFactory : public IProductFactory
{
public:
    std::unique_ptr<Product> createProduct(const QString& name) const override;
};



#endif // MAGAZINEFACTORY_H
