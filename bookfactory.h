#ifndef BOOKFACTORY_H
#define BOOKFACTORY_H

#include "iproductfactory.h"

class BookFactory: public IProductFactory
{
public:
    std::unique_ptr<Product> createProduct(const QString& name) const override;
};

#endif // BOOKFACTORY_H
