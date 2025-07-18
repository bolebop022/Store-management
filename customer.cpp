#include "customer.h"

Customer::Customer(const QString& name): name(name) {}

const Product& Customer::buyProduct(const Product& product){
    // productsPurchased[product] += 1;
    return product;
}
