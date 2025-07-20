#ifndef BUYPRODUCTWINDOW_H
#define BUYPRODUCTWINDOW_H

#include <QDialog>
#include <qcombobox.h>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QListView>
#include <QStringListModel>
#include "customer.h"

class BuyProductWindow : public QDialog
{
    Q_OBJECT
public:
    BuyProductWindow(QWidget* parent = nullptr);
    void addItem();
    QComboBox* customerCBox;
    QComboBox* itemNameCBox;
    QDoubleSpinBox* itemQuantitySBox;
    QLabel* itemType;
    QListView* transactionView;
    QStringListModel* transactionModel;
signals:
    void transactionCompleted();

private:
    void loadCustomers();
    void loadProducts();
    void updateProductType(int index);
    void loadCustomerTransaction(const Customer& customer);
    void onCustomerSelectionChanged(int index);
    const Customer& loadCurrentSBoxCustomer();

};

#endif // BUYPRODUCTWINDOW_H
