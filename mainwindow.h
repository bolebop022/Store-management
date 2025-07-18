#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QStatusBar>
#include <QVBoxLayout>

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
    ~MainWindow();
    void setupMenu();
    void setupToolbar();
    void setupCentralWidget();
    void showAbout();
    void showHelp();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
