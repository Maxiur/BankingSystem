#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Bank.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_createAccount_clicked(); // Utwórz konto

    // void on_depositButton_clicked(); // Wpłać
    // void on_withdrawButton_clicked(); // Wypłać
    // void on_accountList_itemSelectionChanged(); // Kliknięcie konta na liście

    void on_depositButton_clicked();

    void on_withdrawButton_clicked();

    void on_accountList_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    Bank bank;
};
#endif // MAINWINDOW_H
