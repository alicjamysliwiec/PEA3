#include <string>
#include <conio.h>
#include<iostream>
#include "Graf.h"
#include "Genetyczny.h"

using namespace std;
class Menu
{
private:
	Graf graf;								//zmienna przechowuj¹ca reprezentacjê grafu
	Genetyczny* algorytm_genetyczny;		//zmienna odpowiedzialna za algorytm genetyczny


public:
	Menu();									//konstruktor
	~Menu();								//destruktor
	void NacisnijKlawiszByKontynuwoac();	//funkcja pomocnicza obslugujaca klawisze
};

