#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class Graf
{
private:
	int ilosc_wierzcholkow = 0;				//zmienna przechowuj�ca ilosc wierzcholkow
	int** tab = nullptr;					//zmienna przechowuj�ca reprezentacje macierzow� grafu

public:
	Graf();									//konstruktor
	~Graf();								//destruktor
	bool wczytajPlik(string nazwa_pliku);	//wczytanie grafu z pliku
	int** getTab() {
		return tab;							//funkcja zwracjaca macierz
	}
	int getW() {
		return ilosc_wierzcholkow;			//funckja zwracajaca ilosc wierzcholkow
	}
	void wyswietl();						//funkcja wyswietlajaca wczytany graf
};

