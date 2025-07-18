#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void initializeDummyCustomers();

    void setupMenu();
    void setupToolbar();
    void setupCentralWidget();
    void addProduct();
    void setUpProductWindow();
    void buyProduct();
    void setUpBuyProductWindow();

    void showAbout();
    void showHelp();

private:

    QTableWidget* productTable;
    QLabel* statusLabel;
};
#endif // MAINWINDOW_H
