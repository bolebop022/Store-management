#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QVector>
#include <QString>

struct Transaction {
    int id;
    QString timestamp;
    QString customerName;
    QVector<QString> itemsPurchased;
    QString itemType;
    int quantity;
    double amount;

    Transaction(int id,
                const QString& timestamp,
                const QString& customerName,
                const QVector<QString>& itemsPurchased,
                const QString& itemType,
                int quantity,
                double amount);
};

class Transactions
{
public:
    static Transactions& getInstance();
    void addTransaction(const Transaction& t);
    void listTransactions() const;
    const QVector<Transaction>& getTransactions() const;

private:
    QVector<Transaction> transactionList;
    static Transactions * transactionInstance_;
    Transactions();
    Transactions(const Transactions&) = delete;
    Transactions& operator=(const Transactions&) = delete;

};

#endif // TRANSACTIONS_H
