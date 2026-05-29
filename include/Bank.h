#pragma once
#include "Account.h"
#include "User.h"

#include <memory>
#include <string>
#include <unordered_map>

class Bank {
public:
    // Wyciąga konto
    std::shared_ptr<Account> getAccount(const std::string& accountNumber);

    // Tworzy konto i wstawia do bazy danych
    bool createAccount(const std::shared_ptr<Account>& account);

    // Wypisanie informacji o koncie
    void printAccountInfo(const std::string& accountNumber) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Account>> accounts;
    std::unordered_map<std::string, std::shared_ptr<User>> users;
};

