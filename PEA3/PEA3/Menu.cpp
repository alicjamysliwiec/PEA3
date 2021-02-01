#include "Menu.h"

Menu::Menu() {
	string nazwa_pliku;													//zmienna przechowujaca nazwe pliku
	char option;														//zmienna odpowiedzialna za dokonany wybor w menu
	char znak;															//zmienna potrzebna do mozliwosci wyswietlenia grafu
	float kryterium_stopu = 360;										//zmienna przechowujaca kryterium stopu
	int wielkosc_populacji = 5000;										//zmienna przechowujaca wielkosc populacji
	float wspolczynnik_mutacji = 0.01;									//zmienna przechowujaca wspolczynnik mutacji	
	float wspolczynnik_krzyzowania = 0.8;								//zmienna przechowujaca wspolczynnik krzyzowania		
	bool metodaMutacji= false, metodaKrzyzowania = false;				//zmienne potrzebne do wyboru metody mutacji i krzyzowania
	int tmp;
	do {
		cout << endl;
		cout << "1. Wczytaj z pliku i wyswietl dane" << endl;
		cout << "2. Wprowadz kryterium stopu" << endl;
		cout << "3. Ustaw wielkosc populacji poczatkowej" << endl;
		cout << "4. Ustaw wspolczynnik mutacji" << endl;				//menu programu
		cout << "5. Ustaw wspolczynnik krzyzowania" << endl;
		cout << "6. Wybierz metode krzyzowania" << endl;
		cout << "7. Wybierz metode mutacji" << endl;
		cout << "8. Uruchom algorytm" << endl;
		cout << "0. Wyjscie" << endl;
		cout << "Podaj opcje: ";
		option = _getche();												//pobranie znaku z klawiatury
		cout << endl;

		switch (option) {
		case '1':
			do {
				cout << "Podaj nazwe pliku: ";
				cin >> nazwa_pliku;										//wczytanie nazwy pliku
			} while (!graf.wczytajPlik(nazwa_pliku));					//powtorzenie jesli nie uda sie wczytac

			cout << "Jesli chcesz wyswietlic wprowadzone dane wcisnij klawisz t"; //mozliwosc wyswietlenia grafu
			znak = _getche();
			if (znak == 'T' || znak=='t') {
				graf.wyswietl();
			}
			NacisnijKlawiszByKontynuwoac();
			break;
		case '2':
			cout << "Wprowadz kryterium stopu: ";
			cin >> kryterium_stopu;										//wczytanie kryterium stopu
			cout << "Twoje kryterium stopu to: " << kryterium_stopu;	//wyswietlenie ustawionego kryterium
			NacisnijKlawiszByKontynuwoac();
			break;
		case '3':
			cout << "Wprowadz wielkosc populacji poczatkowej: ";
			cin >> wielkosc_populacji;												//wczytanie wielkosci populacji
			cout << "Twoja wielkosc populacji poczatkowej: " << wielkosc_populacji;	//wyswietlenie wielkosci populacji
			NacisnijKlawiszByKontynuwoac();
			break;
		case '4':
			cout << "Wprowadz wspolczynnik mutacji: ";
			cin >> wspolczynnik_mutacji;										//wczytanie wspolczynnika mutacji
			cout << "Twoj wspolczynnik mutacji to: " << wspolczynnik_mutacji;	//wyswietlenie wspolczynnika mutacji
			NacisnijKlawiszByKontynuwoac();
			break;
		case '5':
			cout << "Wprowadz wspolczynnik krzyzowania: ";
			cin >> wspolczynnik_krzyzowania;											//wczytanie wspolczynnika krzyzowania
			cout << "Twoj wspolczynnik krzyzowania to: " << wspolczynnik_krzyzowania;	//wyswietlenie wspolczynnika krzyzowania
			NacisnijKlawiszByKontynuwoac();
			break;
		case '6':	//wybranie krzyzowania
			cout << "0. Krzyzowanie OX" << endl;
			cout << "1. Krzyzowanie PMX" << endl;
			cout << "Twoj wybor: ";
			cin >> tmp;
			if (tmp == 0) {
				cout << "Twoj wybor: Krzyzowanie OX" << endl;
				metodaKrzyzowania = false;
			}
			else if (tmp == 1) {
				cout << "Twoj wybor: Krzyzowanie PMX" << endl;
				metodaKrzyzowania = true;
			}
			else if (tmp!= 1 && tmp != 0) {
				cout << "Wprowadz poprawne dane!";
			}
			break;
		case '7':	//wybranie mutacji
			cout << "0. Mutacja Scramble" << endl;
			cout << "1. Mutacja Inversion" << endl;
			cin >> tmp;
			if (tmp == 0) {
				cout << "Twoj wybor: Mutacja Scramble" << endl;
				metodaMutacji = false;
			}
			else if (tmp == 1) {
				cout << "Twoj wybor Mutacja Inversion" << endl;
				metodaMutacji = true;
			}
			else if (tmp != 1 && tmp != 0) {
				cout << "Wprowadz poprawne dane!";
			}
			break;
		case '8':
			if (!graf.wczytajPlik(nazwa_pliku)) {						//sprawdzenie czy graf zostal wczytany
				cout << "Nie wczytano grafu" << endl;
			}
			else {
				algorytm_genetyczny = new Genetyczny(graf, kryterium_stopu, wielkosc_populacji, wspolczynnik_krzyzowania, wspolczynnik_mutacji, metodaKrzyzowania, metodaMutacji);	//utworzenie algorytmu
				algorytm_genetyczny->start();							//wystartowanie algorytmu
			}
			NacisnijKlawiszByKontynuwoac();
			break;
		case '0':
			break;
		default:
			cout << "Cos poszlo nie tak, sprobuj ponownie :)" << endl;
		};
	} while (option != '0');
}


void Menu::NacisnijKlawiszByKontynuwoac() {
	cout << "\nNacisnij dowolny klawisz by kontynuowac" << endl;
	_getche();
}


Menu::~Menu() {

}