#pragma once
#include <string>

class User {
public:
    User(std::string id, std::string pass_hash): clientId(id), password_hash(pass_hash) {}

    std::string getClientId() const { return clientId; }

    // Porównanie z klasy Crypto
    bool checkPassword(std::string password) const;

private:
    std::string clientId;
    std::string password_hash;
};
