#include "transactions.h"
#include <iostream>
#include <iomanip>


// Constructor for Transaction
Transaction::Transaction(int id,
                         const QString& timestamp,
                         const QString& customerName,
                         const QVector<QString>& itemsPurchased,
                         const QString& itemType,
                         int quantity,
                         double amount)
    : id(id), timestamp(timestamp), customerName(customerName),
    itemsPurchased(itemsPurchased), itemType(itemType),
    quantity(quantity), amount(amount) {}

Transactions::Transactions() {}

Transactions& Transactions::getInstance() {
    static Transactions instance;
    return instance;
}

void Transactions::addTransaction(const Transaction& t) {
    transactionList.push_back(t);
}

const QVector<Transaction>& Transactions::getTransactions() const {
    return transactionList;
}
