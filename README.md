# Mini System Bankowy 

Aplikacja okienkowa symulująca prosty system bankowy, napisana w C++ z wykorzystaniem frameworka Qt 6. 

## Technologie
* **Język:** C++23
* **Framework UI:** Qt 6 (Widgets)
* **System budowania:** CMake
* **Kompilator:** MinGW 64-bit

## Zrealizowane założenia
- [x] Tworzenie nowego konta (wymaga podania numeru, danych właściciela i salda startowego).
- [x] Wpłata i wypłata środków.
- [x] Wyświetlanie szczegółowych informacji o koncie.
- [x] Zabezpieczenie przed ujemnym saldem podczas wypłaty (i wpłaty).
- [x] Blokady wprowadzania błędnych danych (QRegularExpressionValidator).
- [x] Trzymanie danych w pamięci RAM na czas działania programu.
- [x] **[Bonus]** Interfejs graficzny w Qt.
- [x] **[Bonus]** Operacje na walutach realizowane na liczbach całkowitych (`uint64_t` w groszach) dla uniknięcia błędów zmiennoprzecinkowych.
- [x] **[Bonus]** Operacje atomiczne dla wpłat i wypłat, w celu uniknięcia sytuacji np. wypłacenia podwójnej ilości pieniędzy przez dwa różne procesy


---

## Jak uruchomić projekt (Środowisko deweloperskie)

Najprostszy sposób na uruchomienie kodu do weryfikacji:
1. Klonujemy repozytorium: `git clone https://github.com/Maxiur/BankingSystem`
2. Otwieramy plik `CMakeLists.txt` w **Qt Creator**.
3. Skompiluj i uruchom (przycisk Run).

## Budowanie gotowej paczki (Deployment)

Jeśli chcesz wygenerować samodzielny plik `.exe` gotowy do uruchomienia na systemie Windows bez zainstalowanego Qt:

1. W Qt Creatorze zmieniamy tryb budowania z `Debug` na **`Release`**.
2. Budujemy projekt (`Ctrl+B`).
3. Otwieramy konsolę Qt (np. *Qt 6.11.1 (MinGW 64-bit)*).
4. Użyj narzędzia `windeployqt`, aby automatycznie dociągnąć brakujące biblioteki `.dll`:
   ```cmd
   windeployqt C:\Sciezka\Do\Twojego\Folderu\Build\Release\BankApp.exe