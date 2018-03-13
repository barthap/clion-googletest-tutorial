# Konfiguracja CLion i Google Tests

Spis treści:
1. [Struktura projektu CLion](#struktura-projektu-clion)
2. [Konfiguracja istniejącego projektu](#konfiguracja-obecnego-projektu-w-clion)
3. [Konfiguracja projektu od zera](#konfiguracja-nowego-projektu-clion-od-zera)

> Wszystko, co zostało tutaj opisane zostało przetestowane na MacOS X. Na Windowsie teoretycznie też powinno działać (MinGW jest automatycznie instalowane wraz z CLion'em), w razie problemów proszę o kontakt. 

## Struktura projektu CLion

Katalog główny projektu `matlab-2_clion` zawiera następujące pliki i podkatalogi:

- `/.idea` - pliki konfiguracyjne stworzone przez CLion
- `/cmake-build-debug` - pliki utworzone przez cmake, odpowiednik katalogów `bin` i `obj`. Pliki te generowane są automatycznie podczas kompilacji/linkowania i nie powinno się ich przesyłać np. do oceny
- `/googletest-master` - sklonowane repozytorium Google Test (ze względu na rozmiar, zawartość nie została dołączona, należy ją pobrać własnoręcznie - patrz niżej)
- `/include` - pliki nagłówkowe `.h` i `.hpp` projektu
- `/src` - pliki źródłowe projektu `.cpp`
- `/test` - pliki z testami jednostkowymi projektu
- `CMakeLists.txt` - plik konfiguracyjny cmake, jest to tak jakby główny plik projektu
- `matlab-2.cpp` - plik zawierający funkcję `main()` nie uruchamianą w testach, tylko tą "zwykłą"

## Konfiguracja obecnego projektu w CLion

Dotyczy załączonego tutaj projektu `matlab-2_clion`.

1. Pobierz repozytorium Google Test stąd: https://github.com/google/googletest i rozpakuj w katalogu projektu tak, aby katalog `googletest-master` był wewnątrz katalogu głównego projektu
2. Otwórz projekt w CLion Open Project -> matlab-2_clion
3. Przyjrzyj się plikowi `CMakeLists.txt` - to w nim zawarta jest konfiguracja struktury projektu
4. Przyrzyj się konfiguracjom w prawym górnym rogu IDE lub menu Run -> Edit Configurations
- `matlab2_test` - stworzona automatycznie przez IDE podczas analizy instrukcji `add_executable()` w pliku `CMakeLists.txt` - tworzy ona plik wykonywalny uruchamiający testy jednostkowe
- `matlab_2_run` - j.w. ale tworzy plik wykonywalny z funkcji `main()` z pliku `matlab-2.cpp` - zgodnie z konfiguracją CMakeLists
- `Tests` - konfiguracja stworzona ręcznie w IDE - pozwala zintegrować testy jednostkowe z IDE (w oknie Edit Configurations jako `target` została podana konfiguracja `matlab2_test`).
5. Wybierz konfigurację `Tests` (prawy górny róg IDE) i kliknij `Run` albo `Debug` - zielony trójkąt/robak obok
6. Testy powinny uruchomić się pomyślnie w okienku IDE

## Konfiguracja nowego projektu CLion od zera

1. Uruchom CLion i wybierz New Project...
2. Wybierz jako typ C++ Executable i standard C++14
3. IDE utworzy projekt zawierający plik `main.cpp` i `CMakeLists.txt`
4. Utwórz w głównym katalogu projektu 3 katalogi: `src`, `include`, `test`. Można to zrobić za pomocą IDE: w oknie Project po lewej stronie PPM -> New -> Directory
5. Pobierz Google Test (patrz punkt 1. wyżej), rozpakuj i skopiuj katalog `googletest-master` do katalogu głównego projektu
6. Utwórz w katalogu `test` nowy plik o nazwie `main_test.cpp` (katalog test: PPM -> New -> File). Będzie on zawierał funkcję `main()` do testów:
```cpp
#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

```
7. Otwórz plik `CMakeLists.txt` w CLion i spróbuj go zrozumieć
8. Zamień całą jego zawartość na następującą:

```cmake
# Wersja CMake - zostawić jak jest
cmake_minimum_required(VERSION 3.8)

# Nazwa projektu
project(nazwaprojektu)

# Wersja C++ 14
set(CMAKE_CXX_STANDARD 14)

# Miejsca w których kompilator ma szukać plików nagłówkowych .h i .hpp
include_directories(include                     #nasz folder include
        googletest-master/googlemock/include    #foldery google test
        googletest-master/googletest/include)

# Tu będą wszystkie pliki .cpp projektu (na razie nie mamy żadnych)
set(SOURCE_FILES
        )

# Tu będą pliki .cpp używane tylko podczas testów jednostkowych
set(TEST_SOURCES
        test/main_test.cpp) #plik z funkcją main() do testów

#dodaje bibliotekę Google Test, kompiluje ją z użyciem CMakeLists.txt z folderu googletest-master
add_subdirectory(googletest-master)
link_libraries(gmock)

#Tworzy konfigurację o nazwie konfig_run (nazwę możemy dowolnie zmienić)
# do której dołącza plik main.cpp z funkcją main()
add_executable(konfig_run ${SOURCE_FILES} main.cpp)

#Tworzy konfigurację o nazwie konfig_test służącą do uruchamiania testów jednostkowych
add_executable(konfig_test ${SOURCE_FILES} ${TEST_SOURCES})
```

9. Nad edytorem pojawi się żółty komunikat - klikamy Reload Changes... W tym momencie IDE powinno dostosować się do naszego CMake
10. W prawym górnym rogu IDE jeśli rozwiniemy białe pole, powinniśmy zobaczyć listę konfiguracji, w tym 2 nasze i kilka od Google o nazwach gmock, gtest_main itp.
11. Wybieramy Edit Configurations (menu Run lub prawy górny róg).
12. Możemy śmiało usunąć (klikając minusa w lewym rogu okna) 4 konfiguracje `gmock`, `gmock_main`, `gtest` i `gtest_main`. Zostają nasze `konfig_run` i `konfig_test`, których nazwę możemy zmienić wg uznania.
13. Klikamy plusa w rogu i wybieramy Google Test. W polu Name wpisujemy dowolną nazwę, a w polu target wybieramy `konfig_test`. Jest to dokładnie ta sama nazwa z ostatniej linijki CMakeLists.txt
14. Klikamy OK. W prawym górnym rogu IDE powinniśmy móc wybrać naszą nową konfigurację testów. Wybieramy ją i klikamy zielony trójkąt obok. Projekt powinien się skompilować i przejść wszystkie 0 testów pomyślnie ;)
15. Wybierając konfigurację `konfig_run` (o ile nie zmieniliśmy wcześniej jej nazwy) - po kliknięciu Run (i skompilowaniu się) powinien pojawić nam się piękny Hello World w okienku konsoli na dole. To jest ten z `main.cpp`

Spróbujmy dodać jakąś funkcjonalność. 

16. Klikając PPM na katalog `src` wybieramy New -> C++ Source File. W polu name wpisujemy nazwę pliku, np. `kalkulator`, zaznaczamy Add Targets i na liście zaznaczamy pozycję zawierającą `${SOURCE_FILES}` - sprawi to, że nasz nowy plik automatycznie zostanie dodany do CMakeLists.txt w odpowiednie miejsce. Można też zaznaczyć 'Create associated header', aby utworzyć plik .h/.hpp, jednak zostanie on utworzony w folderze src, a nie include.
Po utworzeniu nowego pliku .cpp, w CMakeLists.txt powinien się on pojawić tutaj:
```cmake
# Tu będą wszystkie pliki .cpp projektu (na razie nie mamy żadnych)
set(SOURCE_FILES
        src/kalkulator.cpp)
```
W przypadku tworzenia plików .cpp w inny sposób, należy ręcznie dodać je w tym miejscu oddzielając ich nazwy spacjami.
17. Jeśli nie stworzyliśmy go wcześniej, tworzymy (lub przenosimy) plik `kalkulator.hpp` (lub .h) w folderze 'include'.
Czasami może pojawić się komunikat IDE o tym, że plik nie jest przypisany do żadnego projektu / jest nieużywany. Klikamy wtedy PPM na folder 'include', Mark a
Directory as -> Project Sources and Headers
18. W pliku nagłówkowym `include/kalkulator.hpp` dodajemy kod:
```cpp
int dodaj(int a, int b);
```
A w pliku `kalkulator.cpp` definicję tej funkcji:
```cpp
#include "kalkulator.hpp"

int dodaj(int a, int b) {
    return a + b;
}
```
18. Tworzymy plik `test_kalkulatora.cpp` w katalogu 'test'. Dodajemy go do `TEST_SOURCES` w CMake (albo ręcznie, albo jak wyżej przez okienko New C++ source).
Dodajemy test naszej funkcji dodawania:
```cpp
#include "gtest/gtest.h"
#include "kalkulator.hpp"

TEST(TestyKalkulatora, testDodawania) {

    EXPECT_EQ(dodaj(2, 3), 5);
}
```
19. Wybierz z rogu konfigurację testów i kliknij Run (zielony trójkąt). Po kompilacji w oknie na dole powinien być komunikat o pozytywnym wykonaniu testu. Możesz spróbować zmienić wartości tak, aby test się nie wykonał pomyślnie (obecny sprawdza czy 2+3=5) i sprawdzić zachowanie.