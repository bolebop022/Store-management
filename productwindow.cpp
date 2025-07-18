#include "productwindow.h"
#include "bookfactory.h"
#include "magazinefactory.h"
#include "store.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

ProductWindow::ProductWindow(QWidget* parent): QDialog(parent) {
    setWindowTitle("Store");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* info = new QLabel("Complete the required data");

    QHBoxLayout* itemTypeLayout = new QHBoxLayout(this);
    QHBoxLayout* itemNameLayout = new QHBoxLayout(this);

    QLabel* itemTypeLabel = new QLabel("Item type");
    itemCBox = new QComboBox(this);
    itemCBox->addItem("Book", "B");      // Display text, internal user data "B"
    itemCBox->addItem("Magazine", "M");
    itemTypeLayout->addWidget(itemTypeLabel, 0, Qt::AlignLeft);
    itemTypeLayout->addWidget(itemCBox, 0, Qt::AlignRight);


    QLabel* itemNameLabel = new QLabel("Name of item:");
    itemNameInput = new QLineEdit(this);
    itemNameLayout->addWidget(itemNameLabel, 0, Qt::AlignLeft);
    itemNameLayout->addWidget(itemNameInput, 0, Qt::AlignRight);

    QPushButton * addItemButton = new QPushButton("Add item", this);
    connect(addItemButton, &QPushButton::clicked, this, &ProductWindow::addItem);

    layout->addWidget(info, 0, Qt::AlignCenter);
    layout->addLayout(itemTypeLayout);
    layout->addLayout(itemNameLayout);
    layout->addWidget(addItemButton, 0, Qt::AlignCenter);

}

void ProductWindow::addItem(){

    QString name = itemNameInput->text();
    QString itemType = itemCBox->currentData().toString();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a product name.");
        return;
    }

    std::unique_ptr<IProductFactory> factory;
    if(itemType=="B")
        factory = std::make_unique<BookFactory>();
    else if(itemType == "M")
        factory = std::make_unique<MagazineFactory>();
    Store& store =  Store::getInstance();

    store.addProduct(std::move(factory->createProduct(name)), 1);

    QMessageBox::information(this, "Success", "Product added!");
    itemNameInput->clear();
}
