cmake_minimum_required(VERSION 3.8)
project(matlab_2)   #nazwa projektu

#standard C++ 14
set(CMAKE_CXX_STANDARD 14)

#foldery, w których kompilator ma szukać plików nagłówkowych
include_directories(include
        googletest-master/googletest/include
        googletest-master/googlemock/include)

#współdzielone pliki .cpp
set(SOURCE_FILES
        src/matlab.cpp)

#pliki .cpp dla testów
set(TEST_SOURCES
        test/main_test.cpp      #plik z main() dla testów
        test/test_vector.cpp)

#dodaje bibliotekę Google Test, kompiluje ją z użyciem CMakeLists.txt z folderu googletest-master
add_subdirectory(googletest-master)
link_libraries(gmock)

#konfiguracja do uruchomienia - matlab-2.cpp to plik z main()
add_executable(matlab_2_run ${SOURCE_FILES} matlab-2.cpp)

#konfiguracja do testów
add_executable(matlab2_test ${SOURCE_FILES} ${TEST_SOURCES})