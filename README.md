### Proszę o napisanie klasy SimpleString opakowujacej dynamicznie allokowana tablice znakow.
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
