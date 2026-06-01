#include "Account.hpp"

Account::Account(std::string accountNumber, std::string clientId, uint64_t balance)
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

// Operacje atomiczne
bool Account::withdraw(uint64_t amount) {
    if (amount == 0) return false;
    // ładujemy wartość
    uint64_t current = balance.load();
    // sprawdza czy wartość jest taka sama jak zapamiętana, jeśli tak wykonuje current - amount, otherwise spróbuj ponownie
    while (current >= amount && !balance.compare_exchange_strong(current, current - amount)) {}
    return (current >= amount);
}

bool Account::deposit(uint64_t amount) {
    if (amount == 0) return false;
    // std::atomic posiada przeładowany operator +=
    // który wykonuje operacje atomowo
    balance += amount;
    return true;
}