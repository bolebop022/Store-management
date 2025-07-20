#include "store.h"
#include <QDebug>
#include <QTime>

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

const QVector<Transaction>& Store::getTransactions() const {
    return transactions;
}

bool Store::buyProduct(Customer& customer, const Product& product, int quantity) {
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
        if (!reduceProductQuantity(product, quantity)) {
            qDebug() << "Failed to reduce product quantity";
            return false;
        }
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Create and store transaction record
        Transaction transaction (
            QDateTime::currentDateTime(),
            customer.getName(),
            product.getName(),
            product.getType(),
            quantity);


        // Add the product to the purchased list
        customer.buyProduct(product, quantity);

        // Record the transaction
        addTransaction(transaction);

        qDebug() << "Purchase successful - Customer: " << customer.getName()
                 << ", Product: " << product.getName()
                 << ", Quantity: " << quantity;

        return true;

    } catch (const std::exception& e) {
        qDebug() << "Error during purchase: " << e.what();
        return false;
    }
}

bool Store::reduceProductQuantity(const Product& product, int quantity) {
    if (!products.contains(product)) {
        return false;
    }

    int currentQuantity = products.value(product);
    if (currentQuantity < quantity) {
        return false;
    }

    int newQuantity = currentQuantity - quantity;

    // Update quantity
    products[product] = newQuantity;

    return true;
}

// ✅ Getters
const QMap<Product, int>& Store::getProducts() const {
    return products;
}

const QVector<Customer>& Store::getCustomers() const {
    return customers;
}

Customer* Store::findCustomerByName(const QString& name){

    for (Customer& customer : customers) {
        if (customer.getName().compare(name, Qt::CaseInsensitive) == 0) {
            return &customer; // Return immediately when match is found
        }
    }
    return nullptr;
}

const Customer* Store::accessCustomerByName(const QString& name) {
    for (Customer& customer : customers) {
        if (customer.getName().compare(name, Qt::CaseInsensitive) == 0) {
            return &customer;
        }
    }
    return nullptr;
}

const Product* Store::accessProductByName(const QString& name){
    for (auto it = products.begin(); it != products.end(); ++it) {
        const Product& product = it.key();
        int quantity = it.value();
        return &product;
        // Use product and quantity here
    }
    return nullptr;
}

// ✅ Setters
void Store::setCustomers(const QVector<Customer>& newCustomers) {
    customers = newCustomers;
}

// ✅ Adders
void Store::addProduct(std::unique_ptr<Product> product, int quantity) {
    // Find products
    if (product) {
        products[*product] += quantity;  // Dereference unique_ptr to Product
    }
}

void Store::addCustomer(const Customer& customer) {
    customers.append(customer);
}

void Store::addTransaction(const Transaction& transaction){
    transactions.append(transaction);
}

