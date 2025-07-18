#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QSplashScreen>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    QMenu* helpMenu = menuBar()->addMenu("Help");

    QAction* exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    fileMenu->addAction(exitAction);

    QAction* aboutAction = new QAction("About", this);
    QAction* helpAction = new QAction("Help", this);
    connect(aboutAction, &QAction::triggered, this, &StoreWindow::showAbout);
    connect(helpAction, &QAction::triggered, this, &StoreWindow::showHelp);

    helpMenu->addAction(aboutAction);
    helpMenu->addAction(helpAction);
}

void MainWindow::setupCentralWidget() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    productTable = new QTableWidget(0, 3);
    productTable->setHorizontalHeaderLabels({"Product", "Type", "Stock"});
    layout->addWidget(productTable);

    setCentralWidget(centralWidget);
}

void MainWindow::showAbout() {
    QMessageBox::about(this, "About Store App", "A Qt-based Store Tracking System");
}

void MainWindow::showHelp() {
    QMessageBox::information(this, "Help", "This app tracks purchases and customers in a store.");
}

MainWindow::~MainWindow()
{
    delete ui;
}
