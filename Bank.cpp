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
        return it->second->getBalanceAsGrosze();
    }
    return 0;
}

bool Bank::createAccount(const std::string& accountNumber, const std::string& owner,
                         uint64_t balance) {
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
        uint64_t balance = acc->getBalanceAsGrosze();
        uint64_t zlote = balance / 100;
        uint64_t grosze = balance % 100;

        std::cout << "--- KONTO: " << acc->getAccountNumber() << " ---\n"
                  << "Wlasciciel: " << acc->getOwner() << "\n"
                  << "Saldo: " << zlote << "." << (grosze < 10 ? "0" : "") << grosze << " PLN\n"
                  << "---------------------------\n";
    } else {
        std::cout << "Konto: " << accountNumber << " nie istnieje!\n";
    }
}