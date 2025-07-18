#include "store.h"
#include <QDebug>

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

bool Store::buyProduct(const Customer& customer, const Product& product, int quantity) {
    // Input validation
    if (quantity <= 0) {
        qDebug() << "Invalid quantity: " << quantity;
        return false;
    }

    // Check if product exists in inventory
    if (!products.contains(product)) {
        qDebug() << "Product not found in inventory: " << product.getName();
        return false;
    }

    // Check if customer exists
    bool customerExists = false;
    for (const Customer& c : customers) {
        if (c.getName() == customer.getName()) {
            customerExists = true;
            break;
        }
    }

    if (!customerExists) {
        qDebug() << "Customer not found: " << customer.getName();
        return false;
    }

    // Check if sufficient quantity is available
    int availableQuantity = products.value(product, 0);
    if (availableQuantity < quantity) {
        qDebug() << "Insufficient stock. Available: " << availableQuantity
                 << ", Requested: " << quantity;
        return false;
    }

    // Process the purchase
    try {
        // Reduce inventory
        // if (!reduceProductQuantity(product, quantity)) {
        //     qDebug() << "Failed to reduce product quantity";
        //     return false;
        // }

        // // Optional: Create and store transaction record
        // Transaction transaction;
        // transaction.setCustomer(customer);
        // transaction.setProduct(product);
        // transaction.setQuantity(quantity);
        // transaction.setTimestamp(QDateTime::currentDateTime());
        // transaction.setTotalPrice(product.getPrice() * quantity);

        // addTransaction(transaction);

        // qDebug() << "Purchase successful - Customer: " << customer.getName()
        //          << ", Product: " << product.getName()
        //          << ", Quantity: " << quantity;

        return true;

    } catch (const std::exception& e) {
        qDebug() << "Error during purchase: " << e.what();
        return false;
    }
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

