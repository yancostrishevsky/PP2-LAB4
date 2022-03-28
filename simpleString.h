#ifndef MATRIX_H
#define MATRIX_H

/** @file simpleString.h
@brief Klasa do operowania na tekscie SimpleString:
Proszę o napisanie klasy SimpleString opakowujacej dynamicznie allokowana tablice znakow.
Klasa ta powinna zawierac (jako protected):
- skladowa statyczna: `std::size_t instances_` liczaca aktualnie zyjace instancje
- sugerowana skladowa: `char* data_` wskazująca na dynamicznie zaalokowany obszar z tekstem
- sugerowana skladowa: `std::size_t size_` zawierajaca informacje ile znakow trzyma aktualny tekst
- sugerowana skladowa: `std::size_t capacity_` zawierajaca informacje ile znakow pomiesci aktualny bufor bez realokazji

### Poza skladowymi prosze o zaimplementowanie nastepujacych metod:
1. Metody stale `size()`, `capacity()`, `const char* data()` ktore zwroca powyzsze skladowe
    1. size() ma zwracac rozmiar bez znaku konca tekstu
    2. Prosze o napisanie metody stalej `const char* c_str()`, ktora zwroci zawartosc skladowej `data_`,
       ale zakonczona znakiem konca tekstu. W razie problemow mozna uzyc `mutable`.
2. Konstruktor bezargumentowy
    - wszystkie ustawienia na liście inicjalizacyjnej
    - standard dopuszcza `new char[0];`
3. Konstruktor przyjmujący tekst i dokonujący jego "głęboką" kopię
4. Konstruktor kopiujący, wykonujący "głęboką" kopię
5. Destruktor zwalniający pamięć
6. Metode statyczna `instances()`, ktora zwroci powyzsza skladowa statyczna
7. Proszę o napisanie metody `assign(const char* new_text)` ustawiajacej nowa zawartosc,
   dokonującej głębokiej kopii
    1. **Prosze pamietac aby zwolnic stara pamiec!**
8. Prosze o napisanie metody `equal_to`, ktora przyjmie drugi SimpleString
   i sprawdzi czy zawieraja to samo.
    1. Funkcja ta powinna przyjmowac jeszcze argument `bool case_sensitive=true`
       w oparciu o ktory porownanie bedzie ignorowac lub nie wielkosc znakow.
9. Prosze o napisanie metody `append`, ktora przyjmuje drugi SimpleString,
    a po jej zawolaniu jego zawartosc zostanie dodana do zawartosci `this`.

____________________________________________________________________________________
### Uwaga1: Nie wolno uzywac:
`std::string` ani `std::string_view` ani innych specjalizacji `std::basic_string<...>`!

### Uwaga2: Prosze upewnic sie, ze nie ma wyciekow pamieci.
____________________________________________________________________________________
### Prosze po zaimplementowaniu przypatrzyc sie dokumentacji
`std::string` i porownac metody z `SimpleString`.
Warto docenic, ze mamy `std::string` a wiec sami nie musimy sie bawic z pamiecia`
____________________________________________________________________________________

## Do rozwazenia dla zaawansowanych:
1. Zaimplementowac copy-on-write - wtedy mozna te sugerowane skladowe zastapic.
2. W ktorych sytuacjach wygodnie byloby przeciazyc operatory?
3. Do czego jest `std::string_view`?
4. `std::string` ma definicje typu `value_type` - co nam to daje?
5. Prosze o zdefiniowanie metody `void load(std::istream& is)` (lub operator>>),
   ktora wczyta tekst dowolnej dlugosci z klawiatury
6. Jak zrobic metode `assign` aby uniknac niepotrzebnych alokacji i deallokacji pamieci?
7. Jak zrobic metody `assign` i `append` aby byly odporne na wyrzucenie wyjatku?
8. Jak wszystko zadzialaMimo iz mozna uzyc `std::unique_ptr`
____________________________________________________________________________________
## Uwaga:
1. Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne
2. Metody większe niż 1-linijkowe powinny być zadeklarowane w klasie,
   zdefiniowane poza klasą w pliku zrodlowym
3. Obiekty typów klasowych powinny być w miarę możliwości przekazywane
   w argumentach funkcji przez referencję do stalej,
4. Proszę stosować słówko "const" w odpowiednich miejscach.
5. W pliku zrodlowym prosze nie wlaczac dodatkowych naglowkow typu:
   <iostream>, <algorithm> - takie rzeczy powinny byc w pliku zrodlowym
6. Prosze aby w pliku naglowkowym nie bylo `using namespace std;`, w zrodlowym moze.
7. Mozna korzystac z metod z `<cstring>`.
8. Jaka jest roznica miedzy `delete` a `delete []`?

Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.
____________________________________________________________________________________
## Punktacja:
Liczy sie przejście testów, aczkolwiek dobrze jakby tez nie bylo warningow i wyciekow pamieci
**/

#include <cstddef> // std::size_t


class SimpleString
{
protected:
    static std::size_t instances_;
    char* data_;
    std::size_t size_;
    std::size_t capacity_;

public:
    SimpleString();

    SimpleString(char * data);

    SimpleString(const SimpleString &data);

    bool equal_to(const SimpleString &array2, bool case_sensitive=true)const;

    void append(const SimpleString &string);

    void assign(const char* new_text);

    char* c_str()const{
        return ( char *) &data_[0];
    }

    std::size_t size() const{
        return size_;
    }

    std::size_t capacity() const{
        return capacity_;
    }

    const char * data(){
        return data_;
    }

    static std::size_t instances(){
        return instances_;
    }

    SimpleString(const char *const string);

    ~SimpleString(){
        instances_ -= 1;
        delete[] data_;
    }


};

#endif // MATRIX_H
