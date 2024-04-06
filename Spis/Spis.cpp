#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Dziedziczenie: Klasa IEksponat jest klasą abstrakcyjną - dziedziczy klasy Eksponat i Obraz
class IEksponat {
public:
    virtual ~IEksponat() {}
    virtual void wyswietl() const = 0;
    virtual void zapiszDoPliku(ofstream& plik) const = 0;
};

// Dziedziczenie: Klasa Eksponat dziedziczy po IEksponat
class Eksponat : public IEksponat {
protected:
    int Nr;
    string Nazwa;
    string Tworca;
    int RokProdukcji;
    string Polozenie;
    string Opis;

public:
    // Konstruktor
    Eksponat(int nr, string nazwa, string tworca, int rokProdukcji, string polozenie, string opis)
        : Nr(nr), Nazwa(nazwa), Tworca(tworca), RokProdukcji(rokProdukcji), Polozenie(polozenie), Opis(opis) {}

    // Metoda wirtualna z IEksponat
    void wyswietl() const override {
        cout << "Nr: " << Nr << ", Nazwa: " << Nazwa << ", Tworca: " << Tworca << ", Rok produkcji: " << RokProdukcji
            << ", Polozenie: " << Polozenie << ", Opis: " << Opis << endl;
    }


    void zapiszDoPliku(ofstream& plik) const override {
        plik << Nr << " " << Nazwa << " " << Tworca << " " << RokProdukcji << " " << Polozenie << " " << Opis << endl;
    }
};

// Dziedziczenie: Klasa Obraz dziedziczy po klasie Eksponat
class Obraz : public Eksponat {
private:
    string Technika;

public:
    // Konstruktor
    Obraz(int nr, string nazwa, string tworca, int rokProdukcji, string polozenie, string opis, string technika)
        : Eksponat(nr, nazwa, tworca, rokProdukcji, polozenie, opis), Technika(technika) {}


    // Przeciążenie metody wyswietl
    void wyswietl() const override {
        cout << "Nr: " << Nr << ", Nazwa: " << Nazwa << ", Tworca: " << Tworca << ", Rok produkcji: " << RokProdukcji
            << ", Polozenie: " << Polozenie << ", Opis: " << Opis << ", Technika: " << Technika << endl;
    }

    // Przeciążenie metody zapiszDoPliku
    void zapiszDoPliku(ofstream& plik) const override {
        plik << Nr << " " << Nazwa << " " << Tworca << " " << RokProdukcji << " " << Polozenie << " " << Opis << " " << Technika << endl;
    }
};

// Agregacja: Klasa Muzeum zawiera wektor wskaźników do obiektów IEksponat
class Muzeum {
private:
    vector<IEksponat*> eksponaty;

public:
    // Destruktor
    ~Muzeum() {
        for (auto eksponat : eksponaty) {
            delete eksponat;
        }
    }

    // Dodaje nowy eksponat do muzeum
    void dodajEksponat(IEksponat* nowyEksponat) {
        eksponaty.push_back(nowyEksponat);
    }

    // Wyświetla wszystkie eksponaty w muzeum
    void wyswietlEksponaty() const {
        cout << "Lista eksponatow:" << endl;
        for (const auto& eksponat : eksponaty) {
            eksponat->wyswietl();
        }
    }

    // Zapisuje informacje o eksponatach do pliku tekstowego
    void zapiszDoPliku() const {
        ofstream plik("eksponaty.txt");
        if (plik.is_open()) {
            for (const auto& eksponat : eksponaty) {
                eksponat->zapiszDoPliku(plik);
            }
            cout << "Zapisano do pliku eksponaty.txt" << endl;
        }
        else {
            cout << "Blad podczas zapisu do pliku." << endl;
        }
    }

    // Wczytuje informacje o eksponatach z pliku tekstowego
    void wczytajZPliku() {
        eksponaty.clear();
        ifstream plik("eksponaty.txt");
        if (plik.is_open()) {
            int nr, rokProdukcji;
            string nazwa, tworca, polozenie, opis, technika;
            while (plik >> nr >> nazwa >> tworca >> rokProdukcji >> polozenie >> opis >> technika) {
                if (technika.empty()) {
                    Eksponat* nowyEksponat = new Eksponat(nr, nazwa, tworca, rokProdukcji, polozenie, opis);
                    eksponaty.push_back(nowyEksponat);
                }
                else {
                    Obraz* nowyObraz = new Obraz(nr, nazwa, tworca, rokProdukcji, polozenie, opis, technika);
                    eksponaty.push_back(nowyObraz);
                }
            }
            cout << "Wczytano z pliku eksponaty.txt" << endl;
        }
        else {
            cout << "Blad podczas wczytywania z pliku." << endl;
        }
    }

    // Usuwa wszystkie eksponaty z muzeum
    void usunEksponaty() {
        for (auto eksponat : eksponaty) {
            delete eksponat;
        }
        eksponaty.clear();
        cout << "Usunieto wszystkie eksponaty." << endl;
    }
};

int main() {
    Muzeum muzeum;

    int wybor;
    do {
        // Menu 
        cout << "SPIS EKSPONATOW" << endl << endl;
        cout << "1. Dodaj eksponat" << endl;
        cout << "2. Wyswietl liste eksponatow" << endl;
        cout << "3. Zapisz do pliku" << endl;
        cout << "4. Wczytaj z pliku" << endl;
        cout << "5. Usun wszystkie eksponaty" << endl;
        cout << "6. Zakoncz program" << endl;
        cin >> wybor;

        switch (wybor) {
        case 1: {
            int nr;
            string nazwa, tworca, polozenie, opis, technika;
            int rokProdukcji;

            cout << "Podaj Nr: ";
            cin >> nr;
            cout << "Podaj nazwe eksponatu: ";
            cin >> nazwa;
            cout << "Podaj tworce eksponatu: ";
            cin >> tworca;
            cout << "Podaj rok produkcji eksponatu: ";
            cin >> rokProdukcji;
            cout << "Podaj polozenie eksponatu: ";
            cin >> polozenie;
            cout << "Podaj opis eksponatu: ";
            cin >> opis;
            cout << "Podaj technike (opcja dla obrazow): ";
            cin >> technika;

            if (technika.empty()) {
                Eksponat* nowyEksponat = new Eksponat(nr, nazwa, tworca, rokProdukcji, polozenie, opis);
                muzeum.dodajEksponat(nowyEksponat);
            }
            else {
                Obraz* nowyObraz = new Obraz(nr, nazwa, tworca, rokProdukcji, polozenie, opis, technika);
                muzeum.dodajEksponat(nowyObraz);
            }
            break;
        }
        case 2:
            muzeum.wyswietlEksponaty();
            break;
        case 3:
            muzeum.zapiszDoPliku();
            break;
        case 4:
            muzeum.wczytajZPliku();
            break;
        case 5:
            muzeum.usunEksponaty();
            break;
        case 6:
            cout << "Zakonczono program." << endl;
            break;
        default:
            cout << "Niepoprawny wybor. Sprobuj ponownie." << endl;
        }
    } while (wybor != 6);

    return 0;
}
