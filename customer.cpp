#include "customer.h"

Customer::Customer(const QString& name): name(name) {}

void Customer::buyProduct(const Product& product, int quantity){
    productsPurchased[product] += quantity;
}

const QString& Customer::getName() const{
    return name;
}

const std::map<Product,int>& Customer::getProductsPurchased() const{
    return productsPurchased;
}
