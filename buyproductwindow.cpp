#include "buyproductwindow.h"
#include "store.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QTimer>
#include <QPushButton>
#include <QListView>

BuyProductWindow::BuyProductWindow(QWidget* parent): QDialog(parent) {
    setWindowTitle("Store");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* info = new QLabel("Complete the required data");

    QHBoxLayout* customerLayout = new QHBoxLayout();
    QHBoxLayout* itemNameLayout = new QHBoxLayout();
    QHBoxLayout* itemTypeLayout = new QHBoxLayout();
    QHBoxLayout* itemQuantityLayout = new QHBoxLayout();

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

    // Change product type dynamically
    connect(itemNameCBox, QOverload<int>::of(&QComboBox::currentIndexChanged)
            ,this, &BuyProductWindow::updateProductType);

    itemTypeLayout->addWidget(itemTypeLabel);
    itemTypeLayout->addWidget(itemType);

    QLabel* itemQuantityLabel = new QLabel("Item Quantity:");
    itemQuantitySBox = new QDoubleSpinBox(this);
    QPushButton* addItemButton =  new QPushButton("Add item", this);
    itemQuantityLayout->addWidget(itemQuantityLabel);
    itemQuantityLayout->addWidget(itemQuantitySBox);
    itemQuantityLayout->addWidget(addItemButton);

    transactionModel = new QStringListModel(this);
    transactionView = new QListView(this);
    connect(addItemButton, &QPushButton::clicked, this, &BuyProductWindow::addItem);
    connect(customerCBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &BuyProductWindow::onCustomerSelectionChanged);

    if (customerCBox->count() > 0) {
        onCustomerSelectionChanged(0);
    }
    if(itemNameCBox->count() > 0)
        updateProductType(itemNameCBox->currentIndex());

    layout->addWidget(info);
    layout->addLayout(customerLayout);
    layout->addLayout(itemNameLayout);
    layout->addLayout(itemTypeLayout);
    layout->addLayout(itemQuantityLayout);
    layout->addWidget(transactionView);
}

void BuyProductWindow::addItem(){
    QString customerName = customerCBox->currentText();
    QString itemName = itemNameCBox->currentText();

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
        Customer* selectedCustomer = store.findCustomerByName(customerName);

        if (!selectedCustomer) {
            QMessageBox::warning(this, "Error", "Selected customer not found.");
            return;
        }

        // Find the product
        const Product* selectedProduct = store.accessProductByName(itemName);

        if (!selectedProduct) {
            QMessageBox::warning(this, "Error", "Selected product not found.");
            return;
        }

        const QMap<Product, int>& products = store.getProducts();

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

            loadCustomerTransaction(*selectedCustomer);
            emit transactionCompleted();
        } else {
            QMessageBox::warning(this, "Purchase Failed", "Failed to complete the purchase transaction.");
        }

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to process purchase: %1").arg(e.what()));
    }
}

void BuyProductWindow::onCustomerSelectionChanged(int index) {

    if (index < 0 || index >= customerCBox->count()) {
        return;
    }

    transactionModel->setStringList(QStringList()); // or clear model

    QString selectedCustomerName = customerCBox->itemText(index);
    Store& store = Store::getInstance();
    const Customer* selectedCustomer = store.accessCustomerByName(selectedCustomerName);

    if (selectedCustomer) {
        loadCustomerTransaction(*selectedCustomer);
    } else {
        transactionModel->setStringList(QStringList()); // or clear model
    }
}

void BuyProductWindow::loadCustomerTransaction(const Customer& customer){
    if(!customer.getProductsPurchased().empty())
    {
        for(const auto& purchasedProduct : customer.getProductsPurchased()){
        QString item = QString("%1 (Qty: %2)").arg(purchasedProduct.first.getName()).arg(itemQuantitySBox->value());

        int row = transactionModel->rowCount(); // Get the position to add at the end
        if (transactionModel->insertRows(row, 1)) { // Insert one row at the end
            QModelIndex index = transactionModel->index(row, 0); // Get the model index for the new row
            transactionModel->setData(index, item); // Set the data for the new item
        }
    }
        }
    else
        transactionModel->setStringList(QStringList());
    transactionView->setModel(transactionModel);
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
    if (index < 0 || index >= itemNameCBox->count()) {
        itemType->setText("");
        return;
    }

    // Get product name from combo box at selected index
    QString selectedProductName = itemNameCBox->itemText(index);

    if (selectedProductName.isEmpty()) {
        itemType->setText("");
        return;
    }

    Store& store = Store::getInstance();
    const Product* product = store.accessProductByName(selectedProductName);

    if (product) {
        itemType->setText(product->getType());
    } else {
        itemType->setText("");
    }

}

const Customer& BuyProductWindow::loadCurrentSBoxCustomer(){
    QString selectedCustomerName = customerCBox->currentText();
    Store& store = Store::getInstance();
    const Customer* selectedCustomer = store.accessCustomerByName(selectedCustomerName);
    return *selectedCustomer;
}
