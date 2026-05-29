#pragma once
#include <atomic>
#include <string>
#include <utility>

class Account {
public:
    // Konstruktor
    Account(std::string accountNumber, std::string clientId, double balance);

    // Konstruktor kopiujący oraz klonowanie zabraniamy.
    Account(const Account& from) = delete;
    Account& operator=(const Account&) = delete;

    // Przenoszenie
    Account(Account&& from) noexcept;
    Account& operator=(Account&&) noexcept;

    // Operacje użytkownika na koncie
    bool withdraw(double amount);
    bool deposit(double amount);

    double getBalance() const {
        return balance;
    }
    std::string getAccountNumber() const {
        return accountNumber;
    }
    std::string getOwner() const {
        return owner;
    }

private:
    std::string accountNumber;
    std::string owner;
    std::atomic<double> balance;
};
