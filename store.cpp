#include "store.h"

Store* Store::transactionStore_ = nullptr;

Store::Store() {
    // Initialize products or customers if needed
}

Store& Store::getInstance() {
    if (!transactionStore_) {
        transactionStore_ = new Store();
    }
    return *transactionStore_;
}

Transactions& Store::getTransactions() {
    return Transactions::getInstance();
}

void Store::buyProducts() {
    // your logic here
}

// ✅ Getters
const QMap<Product, int>& Store::getProducts() const {
    return products;
}

const QVector<Customer>& Store::getCustomers() const {
    return customers;
}

// ✅ Setters
void Store::setCustomers(const QVector<Customer>& newCustomers) {
    customers = newCustomers;
}

// ✅ Adders
void Store::addProduct(std::unique_ptr<Product> product, int quantity) {
    if (product) {
        products[*product] = quantity;  // Dereference unique_ptr to Product
    }
}

void Store::addCustomer(const Customer& customer) {
    customers.append(customer);
}

