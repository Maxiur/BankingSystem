#include "Account.hpp"

Account::Account(std::string accountNumber, std::string clientId, double balance)
    : accountNumber(std::move(accountNumber)), owner(std::move(clientId)), balance(balance) {}

Account::Account(Account&& from) noexcept
    : accountNumber(std::move(from.accountNumber)), owner(std::move(from.owner)),
      balance(from.balance.load()) {}

Account& Account::operator=(Account&& from) noexcept {
    if (this != &from) {
        accountNumber = std::move(from.accountNumber);
        owner = std::move(from.owner);
        balance.store(from.balance.load());
    }
    return *this;
}

bool Account::withdraw(double amount) {
    if (amount <= 0)
        return false;

    // ładujemy wartość
    double current = balance.load();
    // sprawdza czy wartość jest taka sama jak zapamiętana, jeśli tak wykonuje current - amount, czekaj
    while (current >= amount && !balance.compare_exchange_weak(current, current - amount)) {
    }
    return (current >= amount);
}

bool Account::deposit(double amount) {
    if (amount <= 0)
        return false;

    // std::atomic posiada przeładowany operator +=
    // który wykonuje operacje atomowo
    balance += amount;
    return true;
}