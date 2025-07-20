#ifndef STORE_H
#define STORE_H

#include "transaction.h"
#include "customer.h"
#include "product.h"

#include <QMap>
#include <QVector>

class Store
{
public:
    static Store& getInstance();
    const QVector<Transaction>& getTransactions() const;


    bool buyProduct(Customer& customer, const Product& product, int quantity);

    Customer* findCustomerByName(const QString& name);
    const Customer* accessCustomerByName(const QString& name);

    const Product* accessProductByName(const QString& name);

    // ✅ Getters
    const QMap<Product, int>& getProducts() const;
    const QVector<Customer>& getCustomers() const;

    // ✅ Setters
    void setCustomers(const QVector<Customer>& customers);

    // ✅ Adders
    void addProduct(std::unique_ptr<Product> product, int quantity);
    void addCustomer(const Customer& customer);
    void addTransaction(const Transaction& transaction);
private:
    Store();
    static Store * transactionStore_;
    Store(const Store&) = delete;
    Store& operator=(const Store&) = delete;

    QMap<Product, int> products;
    QVector<Customer> customers;
    QVector<Transaction> transactions;

    bool reduceProductQuantity(const Product& product, int quantity);
};

#endif // STORE_H
