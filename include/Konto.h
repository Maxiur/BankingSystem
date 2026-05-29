#pragma once
#include <mutex>
#include <string>

class Konto {
public:
    // Konstruktor
    Konto(std::string accountNumber, std::string clientId, std::string pin_hash, std::string password_hash, double balance);

    // Konstruktor kopiujący oraz klonowanie zabraniamy.
    Konto(const Konto& konto) = delete;
    Konto& operator=(const Konto&) = delete;

    // Przenoszenie
    Konto(Konto&&) noexcept;
    Konto& operator=(Konto&&) noexcept;

    // Operacje użytkownika na koncie
    bool withdraw(double amount);
    bool deposit(double amount);

    // Autoryzacja konkretnego konta
    bool checkPassword(std::string& password) const;
    bool checkPin(std::string& pin) const;

    double getBalance() const;
    std::string getAccountNumber() const { return accountNumber; }
    std::string getClientId() const { return clientId; }

private:
    std::string accountNumber;
    std::string clientId; // Powiązanie z bazą użytkowników
    std::string pin_hash; // Pin dedykowany dla jednego konta
    std::string password_hash; // Hasło dedykowane dla jednego konta
    double balance;

    mutable std::mutex mtx;
};
