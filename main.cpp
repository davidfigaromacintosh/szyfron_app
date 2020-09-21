//Plik nag³ówkowy aplikacji Szyfron...
#include "szyfron.hpp"

//G³ówna pêtla...
FILE* f;
std::string fname;
int DaneLiczba[20];
std::string DaneNapis[20];

void OpcjeEkran(int opcja) {

    Szyfron::Szyfr* mojszyfr = Szyfron::MojeSzyfry[opcja - 1];
    Szyfron::RysujRamke('/');
    Szyfron::Napisz(2, 2, (std::string("Wybrales opcje: ") + mojszyfr->GetNazwa()).c_str());

    int i = 0;
    if (strlen(mojszyfr->GetTryb()) == 0) {
        Szyfron::Napisz(2, 3, "Ten szyfr nie wymaga parametrow. Nacisnij dowolny klawisz...");
        _getch();
    }

    else {

        int s_d = 0;
        int i_d = 0;
        for (i = 0; i < strlen(mojszyfr->GetTryb()); i++) {

            if (mojszyfr->GetTryb()[i] == 'i') {
                Szyfron::Napisz(2, i + 4, (std::string("Podaj parametr #") + std::to_string(i + 1) + " (Integer): ").c_str());
                try {
                    std::cin >> DaneLiczba[i_d];
                }
                catch (std::exception e) {
                    DaneLiczba[i_d] = 0;
                }
                i_d++;
            }
            if (mojszyfr->GetTryb()[i] == 's') {
                Szyfron::Napisz(2, i + 4, (std::string("Podaj parametr #") + std::to_string(i + 1) + " (Lancuch znakow): ").c_str());
                try {
                    std::cin >> DaneNapis[s_d];
                }
                catch (std::exception e) {
                    DaneNapis[s_d] = "";
                }
                s_d++;
            }

        }

    }

    Szyfron::Napisz(2, i + 6, "Trwa szyfrowanie, prosze czekac...");
    for (int a = 0; a < Szyfron::file_size; a++) {
        Szyfron::file_data[a] = mojszyfr->Szyfruj(a, Szyfron::file_data[a]);
    }

    f = fopen((".\\files\\o-" + fname).c_str(), "wb");
    if (f != NULL) {
        fwrite(Szyfron::file_data, 1, Szyfron::file_size, f);
        fclose(f);
        Szyfron::Napisz(2, i + 7, (std::string("Szyfrowanie zakonczone! Output: \"o-") + fname + "\"").c_str());
    }
    else {
        Szyfron::Napisz(2, i + 7, "Wystapil blad podczas otwierania pliku!");
    }

    Szyfron::Napisz(2, i + 8, "Nacisnij dowolny klawisz...");
    _getch();
    return;
}

int main()
{



///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                      TUTAJ DEFINIUJEMY WLASNE SZYFRY                      //
//                                                                           //

Szyfron::DodajSzyfr("Negacja bitowa", "", [](int index, int element)->byte {

    return ~element;

});

Szyfron::DodajSzyfr("XOR (Bez hasla, stala wartosc)", "i", [](int index, int element)->byte {

    return element ^ DaneLiczba[0];

});

Szyfron::DodajSzyfr("XOR (Z haslem)", "s", [](int index, int element)->byte {

    return element ^ (DaneNapis[0].c_str()[index % DaneNapis[0].size()]);

});

Szyfron::DodajSzyfr("Szyfr Cezara (ASCII)", "i", [](int index, int element)->byte {

    return element + DaneLiczba[0];

});

//                                                                           //
//                                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////



    Szyfron::PelnyEkran();
    while (1) {

        Szyfron::RysujRamke('#');

        int i;
        for (i = 0; i < Szyfron::MojeSzyfry.size(); i++) {
            Szyfron::Napisz(2, i + 2, (std::to_string(i+1) + ". " + Szyfron::MojeSzyfry[i]->GetNazwa()).c_str());
        }

        Szyfron::Napisz(2, i + 3, "Wpisz numer operacji i wcisnij ENTER (0 aby wyjsc): ");
        //std::cout << "Hello world from full screen app!" << std::endl;

        int opcja = 0;

        try {
            std::cin >> opcja;
        }
        catch (std::exception e) {}
        if (opcja == 0) break;

        Szyfron::Napisz(2, i + 5, "Wprowadz sciezke do pliku z danymi: ");

        try {
            std::cin >> fname;
        }
        catch (std::exception e) { break; }

        f = fopen((".\\files\\" + fname).c_str(), "rb");
        if (f == NULL) {
            Szyfron::Napisz(2, i + 6, "Nie mozna otworzyc pliku!");
            Szyfron::Napisz(2, i + 7, "Sprawdz czy sciezka jest poprawna i czy plik nie jest uzywany przez inny proces!");
            break;
        }

        if (Szyfron::file_data != nullptr) delete[] Szyfron::file_data;
        fseek(f, 0, SEEK_END);
        Szyfron::file_size = ftell(f);
        fseek(f, 0, SEEK_SET);
        Szyfron::file_data = new byte[Szyfron::file_size + 1]();

        fread(Szyfron::file_data, 1, Szyfron::file_size, f);

        fclose(f);
        OpcjeEkran(opcja);

    }

    if (Szyfron::file_data != nullptr) delete[] Szyfron::file_data;
    Szyfron::Napisz(2, 34, "Nacisnij dowolny klawisz...");
    _getch();
    Szyfron::RysujRamke('\0');
    return 0;
}