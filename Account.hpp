#pragma once
#include <atomic>
#include <string>
#include <utility>

class Account {
public:
    // Konstruktor
    Account(std::string accountNumber, std::string clientId, uint64_t balance);

    // Konstruktor kopiujący oraz klonowanie zabraniamy.
    Account(const Account& from) = delete;
    Account& operator=(const Account&) = delete;

    // Przenoszenie
    Account(Account&& from) noexcept;
    Account& operator=(Account&&) noexcept;

    // Operacje użytkownika na koncie
    bool withdraw(uint64_t amount);
    bool deposit(uint64_t amount);

    // zwraca saldo w groszach
    [[nodiscard]] uint64_t getBalanceAsGrosze() const {
        return balance;
    }
    [[nodiscard]] std::string getAccountNumber() const {
        return accountNumber;
    }
    [[nodiscard]] std::string getOwner() const {
        return owner;
    }

private:
    std::string accountNumber;
    std::string owner;
    std::atomic_uint64_t balance;
};
