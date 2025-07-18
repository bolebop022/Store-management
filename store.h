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
    static Store& getInstance();
    Transactions& getTransactions();


    void buyProducts();

    // ✅ Getters
    const QMap<Product, int>& getProducts() const;
    const QVector<Customer>& getCustomers() const;

    // ✅ Setters
    void setCustomers(const QVector<Customer>& customers);

    // ✅ Adders
    void addProduct(std::unique_ptr<Product> product, int quantity);
    void addCustomer(const Customer& customer);
private:
    Store();
    static Store * transactionStore_;
    Store(const Store&) = delete;
    Store& operator=(const Store&) = delete;

    QMap<Product, int> products;
    QVector<Customer> customers;
};

#endif // STORE_H
