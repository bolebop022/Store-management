#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QMap>

#include "product.h"

class Customer
{
public:
    Customer(const QString& name);
    void buyProduct(const Product& product, int quantity);
    const QString& getName() const;
    const std::map<Product, int>& getProductsPurchased() const;

private:
    QString name;
    std::map<Product, int> productsPurchased;
};

#endif // CUSTOMER_H
