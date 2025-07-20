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
    bool operator==(const Product& other) const {
        return productName.compare(other.productName, Qt::CaseInsensitive) == 0 &&
               productType.compare(other.productType, Qt::CaseInsensitive) == 0;
    }

    bool operator<(const Product& other) const {
        return productName.compare(other.productName, Qt::CaseInsensitive) < 0;
    }
    const QString& getName() const {return productName;};
    const QString& getType() const {return productType;};
};

#endif // PRODUCT_H
