#pragma once
#include <string>
#include <utility>

class User {
public:
    User(std::string id, std::string name)
        : clientId(std::move(id)), name(std::move(name)) {}

    [[nodiscard]] std::string getClientId() const {
        return clientId;
    }

private:
    std::string clientId;
    std::string name;
};
