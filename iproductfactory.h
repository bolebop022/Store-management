#ifndef IPRODUCTFACTORY_H
#define IPRODUCTFACTORY_H

#include <QString>
#include <memory>

#include "product.h"

enum class ItemType {
    Book,
    Magazine
};

class IProductFactory{
public:
    virtual ~IProductFactory() = default;

    // Factory Method
    virtual std::unique_ptr<Product> createProduct(const QString& name) const = 0;

};

#endif // IPRODUCTFACTORY_H
