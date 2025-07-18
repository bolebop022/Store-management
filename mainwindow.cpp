#include "mainwindow.h"

#include <QSplashScreen>
#include <QTimer>
#include <QLabel>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resources/splash.png"));
    splash->show();
    QTimer::singleShot(2000, splash, SLOT(close()));

    setWindowTitle("Store Management");
    setWindowIcon(QIcon(":/resources/app_icon.png"));

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

    QAction* aboutAction = new QAction("About", this);
    QAction* helpAction = new QAction("Help", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    connect(helpAction, &QAction::triggered, this, &MainWindow::showHelp);

    helpMenu->addAction(aboutAction);
    helpMenu->addAction(helpAction);
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

    productTable = new QTableWidget(0, 3);
    productTable->setHorizontalHeaderLabels({"Product", "Type", "Stock"});
    layout->addWidget(productTable);

    setCentralWidget(centralWidget);
}

void MainWindow::addProduct(){

}

void MainWindow::showAbout() {
    QMessageBox::about(this, "About Store App", "A Qt-based Store Tracking System");
}

void MainWindow::showHelp() {
    QMessageBox::information(this, "Help", "This app tracks purchases and customers in a store.");
}
