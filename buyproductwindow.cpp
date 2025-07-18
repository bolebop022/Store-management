#include "buyproductwindow.h"
#include "bookfactory.h"
#include "iproductfactory.h"
#include "magazinefactory.h"
#include "store.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <qlineedit.h>
#include <QTimer>
#include <qpushbutton.h>

BuyProductWindow::BuyProductWindow(QWidget* parent): QDialog(parent) {
    setWindowTitle("Store");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* info = new QLabel("Complete the required data");

    QHBoxLayout* customerLayout = new QHBoxLayout(this);
    QHBoxLayout* itemNameLayout = new QHBoxLayout(this);
    QHBoxLayout* itemTypeLayout = new QHBoxLayout(this);
    QHBoxLayout* itemQuantityLayout = new QHBoxLayout(this);

    QLabel* customerLabel = new QLabel("Select the customer:");
    customerCBox = new QComboBox(this);
    loadCustomers();
    customerLayout->addWidget(customerLabel);
    customerLayout->addWidget(customerCBox);

    QLabel* itemLabel = new QLabel("Select the item:");
    itemNameCBox = new QComboBox(this);
    loadProducts();
    itemNameLayout->addWidget(itemLabel);
    itemNameLayout->addWidget(itemNameCBox);

    QLabel* itemTypeLabel = new QLabel("Item type:");
    itemType = new QLabel("");
    // Change test dynamically
    connect(itemNameCBox, QOverload<int>::of(&QComboBox::currentIndexChanged)
            , this, &BuyProductWindow::updateProductType);


    itemTypeLayout->addWidget(itemTypeLabel);

    QLabel* itemQuantityLabel = new QLabel("Item Quantity:");
    itemQuantitySBox = new QDoubleSpinBox(this);
    QPushButton* addItemButton =  new QPushButton("Add item", this);
    itemQuantityLayout->addWidget(itemQuantityLabel);
    itemQuantityLayout->addWidget(itemQuantitySBox);
    itemQuantityLayout->addWidget(addItemButton);


    connect(addItemButton, &QPushButton::clicked, this, &BuyProductWindow::addItem);


    layout->addWidget(info);
    layout->addLayout(customerLayout);
    layout->addLayout(itemNameLayout);
    layout->addLayout(itemTypeLayout);
    layout->addLayout(itemQuantityLayout);
}

void BuyProductWindow::addItem(){
    QString customerName = customerCBox->currentData().toString();
    QString itemName = itemNameCBox->currentData().toString();

    double itemQuantity = itemQuantitySBox->value();


    if (customerName.isEmpty() || itemName.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please select both customer and item.");
        return;
    }

    if (itemQuantity <= 0) {
        QMessageBox::warning(this, "Invalid Quantity", "Please enter a valid quantity greater than 0.");
        return;
    }

    Store& store = Store::getInstance();

    try {
        // Find the customer
        Customer* selectedCustomer = nullptr;
        const QVector<Customer>& customers = store.getCustomers();
        for (const Customer& customer : customers) {
            if (customer.getName() == customerName) {
                selectedCustomer = const_cast<Customer*>(&customer);
                break;
            }
        }

        if (!selectedCustomer) {
            QMessageBox::warning(this, "Error", "Selected customer not found.");
            return;
        }

        // Find the product
        Product* selectedProduct = nullptr;
        const QMap<Product, int>& products = store.getProducts();
        for (const auto& product : products.keys()) {
            if (product.getName() == itemName) {
                selectedProduct = const_cast<Product*>(&product);
                break;
            }
        }

        if (!selectedProduct) {
            QMessageBox::warning(this, "Error", "Selected product not found.");
            return;
        }

        // Check if enough quantity is available
        int availableQuantity = products.value(*selectedProduct, 0);
        if (availableQuantity < itemQuantity) {
            QMessageBox::warning(this, "Insufficient Stock",
                                 QString("Only %1 units available. Cannot purchase %2 units.")
                                     .arg(availableQuantity).arg(itemQuantity));
            return;
        }

        // Process the purchase (assuming store has a buyProduct method)
        // If your Store class has a different method name, adjust accordingly
        bool success = store.buyProduct(*selectedCustomer, *selectedProduct, static_cast<int>(itemQuantity));

        if (success) {
            QMessageBox::information(this, "Success",
                                     QString("Successfully purchased %1 units of %2 for customer %3!")
                                         .arg(itemQuantity).arg(itemName).arg(customerName));

            // Reset quantity to default
            itemQuantitySBox->setValue(1.0);

            // Refresh the products list to show updated inventory
            loadProducts();
        } else {
            QMessageBox::warning(this, "Purchase Failed", "Failed to complete the purchase transaction.");
        }

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to process purchase: %1").arg(e.what()));
    }
}


void BuyProductWindow::loadCustomers() {
    Store& store = Store::getInstance();
    const QVector<Customer>& customers = store.getCustomers();

    if (customers.isEmpty()) {
        QMessageBox::warning(this, "No Customers", "No customers are available. Please add a customer first.");
        customerCBox->setEnabled(false);
        return;
    }

    for (const Customer& customer : customers) {
        customerCBox->addItem(customer.getName());
    }
}

void BuyProductWindow::loadProducts() {
    Store& store = Store::getInstance();
    const QMap<Product,int>& products = store.getProducts();

    if (products.isEmpty()) {
        QMessageBox::warning(this, "No products", "No products are available. Please add an products first.");
        itemNameCBox->setEnabled(false);
        QTimer::singleShot(0, this, SLOT(close()));
        return;
    }

    for (const auto& product : products.keys()) {
        itemNameCBox->addItem(product.getName());
    }
}

void BuyProductWindow::updateProductType(int index) {
    if (index < 0)
        return;

    // Get product name from combo box at selected index
    QString selectedProductName = itemNameCBox->itemText(index);

    // Find product in Store by name
    Store& store = Store::getInstance();
    const QMap<Product,int>& products = store.getProducts();

    // Iterate products to find matching name and get its type
    for (const auto& product : products.keys()) {
        if (product.getName() == selectedProductName) {
            QString typeString;
            if(product.getType() == "B")    // assuming you have getType() that returns an enum or string
                typeString = "B";
            else if(product.getType() == "M")
                typeString = "Magazine";
            else
                typeString = "Unknown";
            itemType->setText(typeString);
        }
    }
}

