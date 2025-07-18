#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
protected:
    QString productName;
    QString productType;
    Product(const QString& productName,const QString& productType): productName(productName), productType(productType){};
};

#endif // PRODUCT_H
