#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        // Przyspawanie okna do aktualnego rozmiaru (żeby użytkownik nic nie rozciągał)
        this->setFixedSize(this->width(), this->height());
        // Tylko cyfry
        QRegularExpression rxAcc("^[0-9]+$");
        ui->accountNumber->setValidator(new QRegularExpressionValidator(rxAcc, this));

        // Tylko litery i spacje
        QRegularExpression rxOwner("^[a-zA-ZąęćłńóśźżĄĘĆŁŃÓŚŹŻ ]+$");
        ui->owner->setValidator(new QRegularExpressionValidator(rxOwner, this));

        // Cyfry i opcjonalnie jedna kropka, przecinek
        QRegularExpression rxMoney("^[0-9]+[.,]?[0-9]{0,2}$");
        QValidator* moneyValidator = new QRegularExpressionValidator(rxMoney, this);
        ui->balance->setValidator(moneyValidator);
        ui->amountInput->setValidator(moneyValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createAccount_clicked()
{
    std::string accountNumber;
    std::string owner;
    uint64_t balance;

    // Ucinamy zbędne spacje
    QString rawAccountNumber = ui->accountNumber->text().trimmed();
    QString rawOwner = ui->owner->text().trimmed();
    QString rawBalance = ui->balance->text().trimmed();

    // Walidacja czy pola nie są puste
    if (rawAccountNumber.isEmpty() || rawOwner.isEmpty() || rawBalance.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Wypełnij wszystkie pola!");
        return;
    }

    accountNumber = rawAccountNumber.toStdString();
    owner = rawOwner.toStdString();

    // Zamieniamy przecinki na kropki
    rawBalance.replace(",", ".");

    QStringList parts = rawBalance.split('.');
    uint64_t totalGrosze = 0;

    if (parts.size() == 1) {
        // Wpisana cała kwota, np. "150"
        totalGrosze = parts[0].toULongLong() * 100;
    }
    else if (parts.size() == 2) {
        uint64_t zlote = parts[0].toULongLong();
        QString groszeStr = parts[1];

        // Formatowanie groszy
        if (groszeStr.length() == 1) {
            // "150.5" -> "5" to 50 groszy
            groszeStr += "0";
        } else if (groszeStr.length() > 2) {
            // "150.555" -> ucinamy na "55" groszy
            groszeStr = groszeStr.left(2);
        }

        uint64_t grosze = groszeStr.toULongLong();
        totalGrosze = (zlote * 100) + grosze;
    }

    balance = totalGrosze;

    // Tworzenie konta
    if (bank.createAccount(accountNumber, owner, balance)) {
        QMessageBox::information(this, "Sukces", "Konto zostało pomyślnie utworzone!");

        QString itemText = rawAccountNumber + " - " + rawOwner;
        ui->accountList->addItem(itemText);

        // Czyszczenie UI
        ui->accountNumber->clear();
        ui->owner->clear();
        ui->balance->clear();

        ui->accountNumber->setFocus();


    }
    else {
        QMessageBox::warning(this, "Ostrzeżenie", "Konto o podanym numerze już istnieje!");
    }
}

void MainWindow::on_depositButton_clicked()
{
    QString accountNumber = ui->accountNumberOutput->text();
    if (accountNumber.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Najpierw wybierz konto z listy żeby wpłacić pieniądze!");
        return;
    }

    QString rawAmount = ui->amountInput->text().trimmed();
    if (rawAmount.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Wpisz kwotę pieniędzy na której chcesz wykonać operację!");
        return;
    }

    rawAmount.replace(",", ".");
    QStringList parts = rawAmount.split('.');
    uint64_t kwotaGrosze = 0;

    if (parts.size() == 1) {
        kwotaGrosze = parts[0].toULongLong() * 100;
    } else if (parts.size() == 2) {
        uint64_t zlote = parts[0].toULongLong();
        QString groszeStr = parts[1];
        if (groszeStr.length() == 1) groszeStr += "0";
        else if (groszeStr.length() > 2) groszeStr = groszeStr.left(2);
        kwotaGrosze = (zlote * 100) + groszeStr.toULongLong();
    }

    auto account = bank.getAccount(accountNumber.toStdString());
    if (account->deposit(kwotaGrosze)) {
        uint64_t newBalance = account->getBalanceAsGrosze();
        QString formatted = QString::number(newBalance / 100) + "." +
                            (newBalance % 100 < 10 ? "0" : "") +
                            QString::number(newBalance % 100) + " PLN";
        ui->balanceOutput->setText(formatted);

        ui->amountInput->clear();
        QMessageBox::information(this, "Sukces", "Pieniądze wpłacone!");
    }
    else {
        QMessageBox::warning(this, "Błąd", "Nie można wpłacić mniej niż jeden grosz!");
        return;
    }
}


void MainWindow::on_withdrawButton_clicked()
{
    QString accountNumber = ui->accountNumberOutput->text();
    if (accountNumber.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Najpierw wybierz konto z listy żeby wpłacić pieniądze!");
        return;
    }

    QString rawAmount = ui->amountInput->text().trimmed();
    if (rawAmount.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Wpisz kwotę pieniędzy na której chcesz wykonać operację!");
        return;
    }

    rawAmount.replace(",", ".");
    QStringList parts = rawAmount.split('.');
    uint64_t kwotaGrosze = 0;

    if (parts.size() == 1) {
        kwotaGrosze = parts[0].toULongLong() * 100;
    } else if (parts.size() == 2) {
        uint64_t zlote = parts[0].toULongLong();
        QString groszeStr = parts[1];
        if (groszeStr.length() == 1) groszeStr += "0";
        else if (groszeStr.length() > 2) groszeStr = groszeStr.left(2);
        kwotaGrosze = (zlote * 100) + groszeStr.toULongLong();
    }

    auto account = bank.getAccount(accountNumber.toStdString());
    if (account->withdraw(kwotaGrosze)) {
        uint64_t newBalance = account->getBalanceAsGrosze();
        QString formatted = QString::number(newBalance / 100) + "." +
                            (newBalance % 100 < 10 ? "0" : "") +
                            QString::number(newBalance % 100) + " PLN";
        ui->balanceOutput->setText(formatted);

        ui->amountInput->clear();
        QMessageBox::information(this, "Sukces", "Pieniądze wypłacone!");
    }
    else {
        QMessageBox::warning(this, "Błąd", "Nie można wypłacić takiej kwoty!");
        return;
    }
}


void MainWindow::on_accountList_itemSelectionChanged()
{
    QListWidgetItem* currentItem = ui->accountList->currentItem();
    if (!currentItem) return;

    QString itemText = currentItem->text();

    QString accountNumber = itemText.split(" - ").first();

    auto account = bank.getAccount(accountNumber.toStdString());

    if (account) {
        ui->accountNumberOutput->setText(QString::fromStdString(account->getAccountNumber()));
        ui->ownerOutput->setText(QString::fromStdString(account->getOwner()));

        uint64_t balanceAsGrosze = account->getBalanceAsGrosze();

        uint64_t zlote = balanceAsGrosze / 100;
        uint64_t grosze = balanceAsGrosze % 100;

        // Jeśli grosze < 10 (np. 5), to dopisujemy zero z przodu, żeby wyszło .05, a nie .5
        QString groszeStr = (grosze < 10 ? "0" : "") + QString::number(grosze);
        QString formattedBalance = QString::number(zlote) + "." + groszeStr + " PLN";

        ui->balanceOutput->setText(formattedBalance);
    }

}

