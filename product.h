#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
protected:
    QString productName;
    QString productType;
    Product(const QString& productName,const QString& productType): productName(productName), productType(productType){};

public:
    bool operator<(const Product& other) const {
        return productName < other.productName;  // or your own logic to compare products
    }
    const QString& getName() const {return productName;};
    const QString& getType() const {return productType;};
};

#endif // PRODUCT_H
