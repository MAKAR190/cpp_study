#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>

// Struktura Książka
struct Ksiazka {
    std::string tytul;
    std::string isbn;

    Ksiazka(const std::string& tytul, const std::string& isbn)
        : tytul(tytul), isbn(isbn) {}

    bool operator<(const Ksiazka& other) const {
        return tytul < other.tytul;  // Sortowanie książek po tytule
    }
};

// Singleton: Biblioteka
class Biblioteka {
private:
    std::vector<Ksiazka> ksiazki;
    std::vector<std::string> oczekujacy;  // Lista oczekujących na książki
    std::mutex mtx;
    std::condition_variable cond_var;

    // Prywatny konstruktor, aby wymusić użycie Singletona
    Biblioteka() {}

public:
    static Biblioteka& getInstance() {
        static Biblioteka instance;
        return instance;
    }

    void dodajKsiazke(const Ksiazka& ksiazka) {
        std::lock_guard<std::mutex> lock(mtx);
        ksiazki.push_back(ksiazka);
        std::sort(ksiazki.begin(), ksiazki.end());  // Sortowanie książek po tytule
        cond_var.notify_all();
    }

    bool wypozyczKsiazke(const std::string& tytul) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto it = ksiazki.begin(); it != ksiazki.end(); ++it) {
            if (it->tytul == tytul) {
                ksiazki.erase(it);
                return true;
            }
        }
        return false;
    }

    void usunKsiazke(const std::string& tytul) {
        std::lock_guard<std::mutex> lock(mtx);
        ksiazki.erase(std::remove_if(ksiazki.begin(), ksiazki.end(),
                        [&tytul](const Ksiazka& ks) { return ks.tytul == tytul; }),
                        ksiazki.end());
    }

    void zapiszNaWypozyczenie(const std::string& tytul) {
        std::lock_guard<std::mutex> lock(mtx);
        oczekujacy.push_back(tytul);
    }

    void wyswietlKsiazki() {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& ks : ksiazki) {
            std::cout << "Tytul: " << ks.tytul << " ISBN: " << ks.isbn << std::endl;
        }
    }

    const std::vector<Ksiazka>& getKsiazki() const {
        return ksiazki;
    }

    const std::vector<std::string>& getOczekujacy() const {
        return oczekujacy;
    }
};

// Klasa Czytelnik
class Czytelnik {
public:
    void wypozycz(const std::string& tytul) {
        if (Biblioteka::getInstance().wypozyczKsiazke(tytul)) {
            std::cout << "Wypozyczono książkę: " << tytul << std::endl;
        } else {
            std::cout << "Książka niedostępna, zapisuję się na wypożyczenie: " << tytul << std::endl;
            Biblioteka::getInstance().zapiszNaWypozyczenie(tytul);
        }
    }
};

// Klasa Bibliotekarz
class Bibliotekarz {
public:
    void dodajKsiazke(const std::string& tytul, const std::string& isbn) {
        Ksiazka ks(tytul, isbn);
        Biblioteka::getInstance().dodajKsiazke(ks);
        std::cout << "Dodano książkę: " << tytul << std::endl;
    }

    void usunKsiazke(const std::string& tytul) {
        Biblioteka::getInstance().usunKsiazke(tytul);
        std::cout << "Usunięto książkę: " << tytul << std::endl;
    }
};

// Generator tytułów książek i ISBN
std::string generujTytul() {
    static const std::vector<std::string> tytuly = {
        "Wojna i pokój", "Zbrodnia i kara", "Mistrz i Małgorzata", "Lalka", "Pani Bovary"
    };
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(0, tytuly.size() - 1);
    return tytuly[distribution(generator)];
}

std::string generujISBN() {
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(1000000000, 9999999999);
    return std::to_string(distribution(generator));
}

// Funkcja główna
int main(int argc, char* argv[]) {
    // Parametry mogą być wczytywane z linii komend (np. czas dodawania książek, czas oczekiwania na wypożyczenie)
    if (argc < 2) {
        std::cerr << "Brak wymaganych parametrów!" << std::endl;
        return 1;
    }

    int czas_dodawania_ksiazek = std::stoi(argv[1]);  // np. czas między dodawaniem książek w sekundach
    int czas_oczekiwania_na_wypozyczenie = std::stoi(argv[2]);  // czas, po którym wypożyczenie jest możliwe

    std::vector<std::thread> czytelnicy;
    Bibliotekarz bibliotekarz;

    // Dodanie książek (symulacja)
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(czas_dodawania_ksiazek));
        std::string tytul = generujTytul();
        std::string isbn = generujISBN();
        bibliotekarz.dodajKsiazke(tytul, isbn);
    }

    // Zapisanie czytelników na wypożyczenia
    Czytelnik czytelnik1, czytelnik2;
    czytelnicy.emplace_back(&Czytelnik::wypozycz, &czytelnik1, "Wojna i pokój");
    czytelnicy.emplace_back(&Czytelnik::wypozycz, &czytelnik2, "Zbrodnia i kara");

    for (auto& t : czytelnicy) {
        t.join();
    }

    // Usuwanie książki
    bibliotekarz.usunKsiazke("Zbrodnia i kara");

    // Wyświetlanie dostępnych książek
    Biblioteka::getInstance().wyswietlKsiazki();

    return 0;
}
