#ifndef BUYPRODUCTWINDOW_H
#define BUYPRODUCTWINDOW_H

#include <QDialog>
#include <qcombobox.h>
#include <QDoubleSpinBox>
#include <qlabel.h>

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
private:
    void loadCustomers();
    void loadProducts();
    void updateProductType(int index);
};

#endif // BUYPRODUCTWINDOW_H
