# Mini System Bankowy 

Aplikacja okienkowa symulująca prosty system bankowy, napisana w C++ z wykorzystaniem frameworka Qt 6. 

## Technologie
* **Język:** C++23
* **Framework UI:** Qt 6 (Widgets)
* **System budowania:** CMake
* **Kompilator:** MinGW 64-bit
---

## Automatyzacja (CI/CD — GitHub Actions)

Projekt ma w pełni zautomatyzowany proces budowania.

Każdy `git push` uruchamia maszynę wirtualną z systemem Windows w chmurze GitHub, która:
1. Pobiera kod źródłowy.
2. Instaluje odpowiednią wersję frameworka Qt 6.
3. Kompiluje projekt za pomocą CMake w trybie `Release`.
4. Wykonuje deployment aplikacji (automatycznie dociąga wszystkie wymagane pliki `.dll` i wtyczki).
5. Pakuje całość do gotowego archiwum ZIP.

### Jak pobrać gotowy program (Artifact):
1. Przejdź do zakładki **Actions** na górze tego repozytorium.
2. Kliknij w najnowszy, pomyślnie zakończony proces (oznaczony zielonym ptaszkiem).
3. Na samym dole strony, w sekcji **Artifacts**, znajdziesz plik `BankApp-Windows-Zbudowana-Wersja.zip`.
4. Pobierz go, wypakuj w dowolne miejsce i uruchom `BankApp.exe`.

## Jak uruchomić projekt (Środowisko deweloperskie)

Najprostszy sposób na uruchomienie kodu do weryfikacji:
1. Klonujemy repozytorium: `git clone https://github.com/Maxiur/BankingSystem.git`
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
