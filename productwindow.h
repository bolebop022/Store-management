#ifndef PRODUCTWINDOW_H
#define PRODUCTWINDOW_H

#include <QDialog>
#include <QObject>
#include <qcombobox.h>

class ProductWindow : public QDialog
{
    Q_OBJECT
public:
    ProductWindow(QWidget* parent = nullptr);
    void addItem();
    QComboBox* itemCBox;
    QLineEdit* itemNameInput;
};

#endif // PRODUCTWINDOW_H
