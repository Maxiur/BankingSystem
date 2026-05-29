#pragma once
#include <string>
#include <utility>

class User {
public:
    User(std::string id, std::string pass_hash)
        : clientId(std::move(id)), password_hash(std::move(pass_hash)) {}

    [[nodiscard]] std::string getClientId() const {
        return clientId;
    }

    // Porównanie z klasy Crypto
    bool checkPassword(std::string password) const;

private:
    std::string clientId;
    std::string password_hash;
};
