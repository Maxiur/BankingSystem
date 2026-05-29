#include "Bank.hpp"
#include <iostream>

std::shared_ptr<Account> Bank::getAccount(const std::string& accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        return it->second;
    }
    // Konto nie istnieje
    return nullptr;
}

bool Bank::accountExists(const std::string& accountNumber) const {
    return accounts.contains(accountNumber);
}

double Bank::getAccountBalance(const std::string& accountNumber) const {
    if (const auto it = accounts.find(accountNumber); it != accounts.end()) {
        return it->second->getBalance();
    }
    return 0;
}

bool Bank::createAccount(const std::string& accountNumber, const std::string& owner,
                         double balance) {
    if (accountExists(accountNumber))
        return false;

    const auto newAccount = std::make_shared<Account>(accountNumber, owner, balance);
    accounts[accountNumber] = newAccount;
    return true;
}

void Bank::printAccountInfo(const std::string& accountNumber) const {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        const auto& acc = it->second;
        std::cout << "--- KONTO: " << acc->getAccountNumber() << " ---\n"
                  << "Wlasciciel: " << acc->getOwner()
                  << "\n" // Zakładając, że masz getter getOwner()
                  << "Saldo: " << acc->getBalance() << " PLN\n"
                  << "---------------------------\n";
    } else {
        std::cout << "Blad: Konto " << accountNumber << " nie istnieje!\n";
    }
}