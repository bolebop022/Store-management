#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QVector>
#include <QDateTime>

class Transaction
{
public:
    Transaction(
        const QDateTime& timestamp,
        const QString& customerName,
        const QString& itemPurchased,
        const QString& itemType,
        int quantity);
    const QDateTime& getTimestamp() const;
    const QString& getCustomerName() const;
    const QString& getItemPurchased() const;
    const QString& getItemType() const ;
    int getQuantity() const;


private:
    QDateTime timestamp;
    QString customerName;
    QString itemPurchased;
    QString itemType;
    int quantity;
};



#endif // TRANSACTION_H
