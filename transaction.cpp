#include "transaction.h"

Transaction::Transaction(
    const QDateTime& timestamp,
    const QString& customerName,
    const QString& itemPurchased,
    const QString& itemType,
    int quantity) : timestamp(timestamp), customerName(customerName)
    , itemPurchased(itemPurchased), itemType(itemType), quantity(quantity){}

const QDateTime& Transaction::getTimestamp() const{
    return timestamp;
}

const QString& Transaction::getCustomerName() const{
    return customerName;
}

const QString& Transaction::getItemPurchased() const{
    return itemPurchased;
}

const QString& Transaction::getItemType() const{
    return itemType;
}

int Transaction::getQuantity() const{
    return quantity;
}
