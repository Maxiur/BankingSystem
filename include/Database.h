#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Konto.h"

class Database {
public:
    // Połączenie z bazą danych
    static bool init(const std::string& dbPath);

    // Zamknięcie połączenia z db
    static void close();

    // Ładuje wszystko z dysku do mapy w banku przy starcie programu
    static std::shared_ptr<Konto> getAccount(const std::string& accountNumber);

    // Wykonuje UPDATE na jednym konkretnym koncie po udanej transakcji
    static bool updateAccount(const std::shared_ptr<Konto>& account);

    static bool createAccount(const std::shared_ptr<Konto>& account);
};
