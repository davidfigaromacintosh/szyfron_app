#ifndef __H_SZYFRON
#define __H_SZYFRON

#define _CRT_SECURE_NO_WARNINGS

//Do��czamy podstawowe pliki nag��wkowe takie jak "iostream" oraz "windows.h"...
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>

//Do��czamy bibliotek� DLL z funkcjami natywnymi systemu Windows...
#pragma comment(lib, "user32")

//Przestrze� nazw "Szyfron" dla �atwiejszego manewrowania kodem �r�d�owym...
namespace Szyfron {

	byte* file_data = nullptr;
	size_t file_size = 0;

	class Szyfr {

		const char* name;
		const char* mode;
		byte(*func)(int, int) = nullptr;

	public:

		Szyfr(const char* nazwa, const char* tryb, byte(*funkcja)(int index, int element) = nullptr) {
			name = nazwa;
			mode = tryb;
			func = funkcja;
		}

		const char* GetNazwa() { return name; }
		const char* GetTryb() { return mode; }
		byte Szyfruj(int index, int element) { return func(index, element); }

	};

	std::vector<Szyfr*> MojeSzyfry;

	void DodajSzyfr(const char* nazwa, const char* tryb, byte(*funkcja)(int, int)) {
	
		Szyfr* mycipher = new Szyfr(nazwa, tryb, funkcja);
		MojeSzyfry.push_back(mycipher);

	}

	//Ta funkcja prze��cza okno konsoli na pe�ny ekran...
	void PelnyEkran() {
		::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	}

	//Ta funkcja czy�ci wszystko co widoczne na ekranie...
	void Wyczysc() {
		system("cls");
	}

	//Ta funkcja rysuje ramk� dooko�a okienka na podstawie podanego znaku...
	void RysujRamke(const char znak) {
		int w = 160;
		int h = 40;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

		for (int i = 0; i < w; i++) {
			putchar(znak);
		}
		putchar('\n');

		for (int j = 0; j < h - 2; j++) {
			for (int i = 0; i < w; i++) {
				if (i == 0 || i == w - 1) putchar(znak);
				else putchar(0);
			}
			putchar('\n');

		}

		for (int i = 0; i < w; i++) {
			putchar(znak);
		}
		putchar('\n');
	
	}

	void Napisz(SHORT x, SHORT y, const char* text) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
		printf(text);
	}

}


#endif