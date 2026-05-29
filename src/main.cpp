#include "Bank.hpp"
#include <iostream>
#include <limits>
#include <string>

void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showMenu() {
    std::cout << "\n=== SYSTEM BANKOWY ===\n"
              << "1. Utwórz konto\n"
              << "2. Wpłata\n"
              << "3. Wypłata\n"
              << "4. Informacje o koncie\n"
              << "5. Wyjście\n"
              << "Wybierz: ";
}

int main() {
    Bank bank;

    // hajs podzielony / 100
    bank.createAccount("0049", "Mateusz", 1025);
    bank.printAccountInfo("0049");

    bank.createAccount("0048", "Janek", 1005);
    bank.printAccountInfo("0048");
}
