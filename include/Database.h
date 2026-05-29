#pragma once
#include "Konto.h"
#include <memory>
#include <string>
#include <unordered_map>

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

    // Tworzy konto i wstawia do bazy danych
    static bool createAccount(const std::shared_ptr<Konto>& account);

private:
    // static sqlite3* db;
};
