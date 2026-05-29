#pragma once
#include "Account.hpp"

#include <memory>
#include <string>
#include <unordered_map>

class Bank {
public:
    // Wyciąga konto
    std::shared_ptr<Account> getAccount(const std::string& accountNumber);

    // Czy konto istnieje
    bool accountExists(const std::string& accountNumber) const;

    double getAccountBalance(const std::string& accountNumber) const;

    // Tworzy konto i wstawia do bazy danych
    bool createAccount(const std::string& accNum, const std::string& owner, double balance);

    // Wypisanie informacji o koncie
    void printAccountInfo(const std::string& accountNumber) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Account>> accounts;
};
