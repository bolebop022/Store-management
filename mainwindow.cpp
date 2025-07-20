#include "mainwindow.h"
#include "buyproductwindow.h"
#include "customer.h"
#include "productwindow.h"
#include "store.h"
#include "transaction.h"
#include "bookfactory.h"

#include <QSplashScreen>
#include <QTimer>
#include <QLabel>
#include <QMenuBar>
#include <QStandardItemModel>
#include <QTreeView>
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resources/splash.png"));
    splash->show();
    QTimer::singleShot(2000, splash, SLOT(close()));

    setWindowTitle("Store Management");
    setWindowIcon(QIcon(":/resources/app_icon.png"));

    initializeDummyCustomers();
    setupMenu();
    setupToolbar();
    setupCentralWidget();

    statusLabel = new QLabel("Ready");
    statusBar()->addWidget(statusLabel);

}

void MainWindow::setupMenu() {
    QMenu* fileMenu = menuBar()->addMenu("File");
    QMenu* addMenu = menuBar()->addMenu("Add");
    QMenu* helpMenu = menuBar()->addMenu("Help");

    QAction* exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    fileMenu->addAction(exitAction);

    QAction* addProductAction = new QAction("Add Product");
    connect(addProductAction, &QAction::triggered, this, &MainWindow::addProduct);
    addMenu->addAction(addProductAction);

    QAction* buyProductAction = new QAction("Buy Product");
    connect(buyProductAction, &QAction::triggered, this, &MainWindow::buyProduct);
    addMenu->addAction(buyProductAction);

    QAction* aboutAction = new QAction("About", this);
    QAction* helpAction = new QAction("Help", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    connect(helpAction, &QAction::triggered, this, &MainWindow::showHelp);

    helpMenu->addAction(aboutAction);
    helpMenu->addAction(helpAction);
}

void MainWindow::initializeDummyCustomers() {
    Store& store = Store::getInstance();
    store.addCustomer(Customer("Alice"));
    store.addCustomer(Customer("Bob"));
    store.addCustomer(Customer("Charlie"));
}

void MainWindow::setupToolbar(){
    QToolBar* toolbar = addToolBar("Main Toolbar");

    QAction* refreshAction = new QAction("Refresh", this);
    QAction* buyAction = new QAction("Buy", this) ;

    addAction(refreshAction);
    addAction(buyAction);
}

void MainWindow::setupCentralWidget() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    treeView = new QTreeView();

    // Model with 3 columns
    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList() << "Transaction" << "Type" << "Quantity");

    // Simulate data
    // Store& store = Store::getInstance();
    // std::unique_ptr<IProductFactory> factory;
    // factory = std::make_unique<BookFactory>();
    // std::unique_ptr<Product> firstProd = factory->createProduct("Great Gatsby");
    // int firstQty = 3;
    // store.addProduct(std::move(firstProd), firstQty);
    // const Product* prodPtr = store.accessProductByName("Great Gatsby");
    // Customer firstCus("John");
    // store.addCustomer(firstCus);
    // store.buyProduct(firstCus, *prodPtr , 2);

    refreshTreeView();

    treeView->setModel(model);
    layout->addWidget(treeView);

    setCentralWidget(centralWidget);
}

void MainWindow::refreshTreeView(){
    model->clear();
    model->setHorizontalHeaderLabels(QStringList() << "Transaction" << "Type" << "Quantity");

    Store& store = Store::getInstance();
    // Group the transactions
    QMap<QString, QMap<QDateTime, QVector<QPair<QString,int>>>> transactionViewModel;

    const auto& transactions = store.getTransactions();
    for (const Transaction& t : transactions) {
        const QString& name = t.getCustomerName();
        const QDateTime& time = t.getTimestamp();
        const QString& item = t.getItemPurchased();
        int qty = t.getQuantity();

        transactionViewModel[name][time].append(qMakePair(item, qty));
    }
    // Populate QTreeView
    buildTreeView(transactionViewModel);


}

void MainWindow::buildTreeView(QMap<QString, QMap<QDateTime, QVector<QPair<QString,int>>>>& transactionViewModel){
    // Display the transactions
    for (auto customerIt = transactionViewModel.begin(); customerIt != transactionViewModel.end(); ++customerIt) {
        QStandardItem* customerName = new QStandardItem(customerIt.key());


        QList<QStandardItem*> customerRow;
        customerRow << customerName;
        model->appendRow(customerRow);

        // Add the child row
        const auto& timestampMap = customerIt.value();
        for (auto timeIt = timestampMap.begin(); timeIt != timestampMap.end(); ++timeIt) {
            QString timestampStr = timeIt.key().toString("yyyy-MM-dd HH:mm");
            QStandardItem* timestamp = new QStandardItem(timestampStr);


            QList<QStandardItem*> timestampRow;
            timestampRow << timestamp;
            customerRow[0]->appendRow(timestampRow);

            // Add the subchild
            const QVector<QPair<QString, int>>& items = timeIt.value();
            for (const auto& itemPair : items) {
                QString itemName = itemPair.first;
                int quantity = itemPair.second;
                QStandardItem* item = new QStandardItem(itemName);
                QStandardItem* qty = new QStandardItem(QString::number(quantity));

                QList<QStandardItem*> itemRow;
                itemRow << item << qty;
                timestampRow[0]->appendRow(itemRow);
            }
        }
    }
    treeView->setModel(model);
}

void MainWindow::addProduct(){
    setUpProductWindow();
}

void MainWindow::buyProduct(){
    setUpBuyProductWindow();
}

void MainWindow::showAbout() {
    QMessageBox::about(this, "About Store App", "A Qt-based Store Tracking System");
}

void MainWindow::showHelp() {
    QMessageBox::information(this, "Help", "This app tracks purchases and customers in a store.");
}

void MainWindow::setUpProductWindow(){
    ProductWindow* productWindow = new ProductWindow(this);
    productWindow->show();
}

void MainWindow::setUpBuyProductWindow(){
    BuyProductWindow* buyProductWindow = new BuyProductWindow(this);
    connect(buyProductWindow, &BuyProductWindow::transactionCompleted, this, &MainWindow::refreshTreeView);
    buyProductWindow->show();
}
