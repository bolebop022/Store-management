#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QMap>

#include "product.h"

class Customer
{
public:
    Customer(const QString& name);
    const Product& buyProduct(const Product& product);
    const QString& getName() const;
private:
    QString name;
    std::map<Product, int> productsPurchased;
};

#endif // CUSTOMER_H
