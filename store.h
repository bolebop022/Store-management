#ifndef STORE_H
#define STORE_H

#include "transactions.h"
#include "customer.h"
#include "product.h"

#include <QMap>
#include <QVector>

class Store
{
public:
    Store();
    Transactions& transactions = Transactions::getInstance();
    QMap<Product, int> products;
    QVector<Customer> customer;
    void buyProducts();
    Customer getCustomer();
};

#endif // STORE_H
