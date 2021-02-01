#include "Genetyczny.h"

//konstruktor
Genetyczny::Genetyczny(Graf graf, float stop, int rozmiarPopulacji, float wspKrzyzowania, float wspMutacji, bool algorytmKrzyzowania, bool algorytmMutacji)
{
	ilosc_wierzcholkow = graf.getW();
	tab = graf.getTab();
	this->stop = stop;
	this->wspKrzyzowania = wspKrzyzowania;
	this->wspMutacji = wspMutacji;
	this->rozmiarPopulacji = rozmiarPopulacji;
	this->algorytmKrzyzowania = algorytmKrzyzowania;
	this->algorytmMutacji = algorytmMutacji;
}

//wystartowanie algorytmu
void Genetyczny::start()
{
	vector<vector<int>> populacja, nowaPopulacja;			//tworzymy dwie populacje
	vector<int> osobnik;									//tworzymy osobnika
	int rozmiarTurnieju = 5;								//ustawiamy rozmiar turnieju
	clock_t start;											//czas rozpoczecia algorytmu
	double czas = 0;										//czas od rozpoczecia algorytmu

	for (int i = 0;i < ilosc_wierzcholkow;i++)
	{
		osobnik.push_back(i);								//tworzymy osobnika
	}

	for (int i = 0; i < rozmiarPopulacji;i++)
	{
		random_shuffle(osobnik.begin(), osobnik.end());		//mieszamy kolejnosc wierzcholkow
		populacja.push_back(osobnik);						//tworzymy populacje

	}

	start = clock();										//czas rozpoczecia algorytmu
	
	while (czas < stop)										//wykonujemy dopoki czas nie przekroczy kryterium stopu
	{

		Selekcja(populacja, rozmiarTurnieju);				//wykonujemy selekcje populacji
		nowaPopulacja = populacja;							//zapisujemy osobniki po selekcji do nowej populacji
		KrzyzowanieAlgorytm(populacja, nowaPopulacja);		//krzyzowanie osobnikow
		MutacjaAlgorytm(nowaPopulacja);						//mutowanie osobnikow
		populacja = nowaPopulacja;							//zapisujemy nowa populacje jako stara			
		nowaPopulacja.clear();								//usuwamy populacje
		zapiszNajlepsza(populacja);							//szukamy najlepszego osobnika
		czas = (clock() - start) / (double)CLOCKS_PER_SEC;	//zapisujemy czas wykonania algorytmu
	}
	wypiszDroge(najlepsza);									//wypisujemy wyniki
}

//selekcja osobnikow
void Genetyczny::Selekcja(vector<vector<int>> &populacja, int rozmiarTurnieju)
{
	vector<vector<int>> nowaPopulacja;							//tworzymy nowa populacje
	for (int i = 0;i < rozmiarPopulacji;i++)
	{
		int najlepszy = INT_MAX, najlepszyNumer, tmp, tmpWynik;	
		for (int j = 0;j < rozmiarTurnieju;j++)					//wybieramy tyle osobnikow, ile wynosi rozmiar turnieju
		{
			tmp = rand() % populacja.size();					//losujemy osobnika
			tmpWynik = liczSciezke(populacja.at(tmp));			//sprawdzamy stopien przystosowania
			if (tmpWynik < najlepszy)							//jesli jest lepszy od aktualnie najlepszego
			{
				najlepszyNumer = tmp;							//zapisujemy jego indeks
				najlepszy = tmpWynik;							//i wartosc funkcji oceny - dlugosc drogi
			}
		}
		nowaPopulacja.push_back(populacja.at(najlepszyNumer));	//dodajemy tego osobnika do populacji
	}
	populacja = nowaPopulacja;									//nadpisujemy stara populacje nowa
}

//krzyzowanie
void Genetyczny::KrzyzowanieAlgorytm(vector<vector<int>> &populacja, vector<vector<int>> &nowaPopulacja)
{
	vector<int> rodzic1, rodzic2;							//rodzice
	for (int i = 0;i < populacja.size()*wspKrzyzowania;i++)	//wybieramy taki procent osobnikow, ile wynosi wspolczynnik krzyzowania
	{
		int pierwszy, drugi;
		do {
			pierwszy = rand() % populacja.size();			//losujemy pozycje pierwszego rodzica
			drugi = rand() % populacja.size();				//losujemy pozcyje drugiego rodzica
		} while (pierwszy == drugi);						//nie moga byc takie same
		rodzic1 = populacja.at(pierwszy);					//wybieramy pierwszego osobnika
		rodzic2 = populacja.at(drugi);						//wybieramy drugiego osobnika
		if (algorytmKrzyzowania == true) {					//wybieramy rodzaj krzyzowania
			KrzyzowaniePMX(rodzic1, rodzic2);				
		}
		else {
			KrzyzowanieOX(rodzic1, rodzic2);
		}
		nowaPopulacja.push_back(rodzic1);					//dodajemy nowego osobnika do populacji
		nowaPopulacja.push_back(rodzic2);					//dodajemy nowego osobnika do populacji
	}
}

//mutacja
void Genetyczny::MutacjaAlgorytm(vector<vector<int>> &populacja)
{
	for (int i = 0;i < populacja.size();i++)
	{
		double p = (double)rand() / RAND_MAX;		//dla kazdego osobnika losujemy liczbe
		if (p < wspMutacji)							//sprawdzamy czy bedziemy go mutowac
			if (algorytmMutacji == true) {			//wybieramy mutacje
				MutacjaInversion(populacja.at(i));
			}
			else {
				MutacjaScramble(populacja.at(i));
			}
	}
}

//algorytm Ordered Crossing
void Genetyczny::KrzyzowanieOX(vector<int>& rodzic1, vector<int>& rodzic2) //0
{

	vector <int> dziecko1(ilosc_wierzcholkow), dziecko2(ilosc_wierzcholkow);				//utworzenie wektorow przechwoujacych nastepne sciezki
	int poczatek, koniec;																	//zmienne pomocniczne do znalezienia czesci wspolnej
	do
	{
		poczatek = rand() % ilosc_wierzcholkow;												//wylosowanie poczatku
		koniec = rand() % ilosc_wierzcholkow;												//wylosowanie konca
	} while (poczatek == koniec);															//tak, zeby nie byly to te same liczby
	if (koniec < poczatek)																	//jezeli liczba odpowiadajaca za koniec jest mniejsza od poczatku
		swap(poczatek, koniec);																//to je zamieniamy, zeby poczatek < koniec

	move(rodzic1.begin() + poczatek, rodzic1.begin() + koniec, dziecko1.begin() + poczatek);//przenosimy wylosowana czesc z rodzica pierwszego do pierwszego ptoomka
	move(rodzic2.begin() + poczatek, rodzic2.begin() + koniec, dziecko2.begin() + poczatek);//przenosimy wylosowana czesc z rodzica drugiego do drugiego potomka

	int wskaznik[2] = { koniec, koniec };													//wskazujemy, w ktore miejsce wpisac nastepna wartosc
	for (int z = koniec; z < ilosc_wierzcholkow + koniec; z++)								//przechodzimy po chromosomie
	{
		bool przypisz[2] = { true, true };													//informacja, czy mamy przypisac wartosc
		for (int k = poczatek; k < koniec; k++)												//sprawdzamy czy wierzcholek zastal przepisany z poprzedniego rodzica
		{
			if (rodzic1.at(k) == rodzic2.at(z % ilosc_wierzcholkow)) przypisz[0] = false;		//sprawdzamy, czy dziecko1 juz posiada ten gen
			if (rodzic2.at(k) == rodzic1.at(z % ilosc_wierzcholkow)) przypisz[1] = false;		//sprawdzamy, czy dziecko2 juz posiada ten gen
		}

		if (przypisz[0])																	//jezeli nie posiada
		{
			dziecko1.at(wskaznik[0]) = rodzic2.at(z % ilosc_wierzcholkow);					//przypisujemy gen z rodzica
			wskaznik[0]++;																	//zwiekszamy wskaznik na miejsce
			wskaznik[0] %= ilosc_wierzcholkow;												//tak zeby nie wyszlo poza zakres
		}
		if (przypisz[1])																	//to samo dla drugiego dziecka
		{
			dziecko2.at(wskaznik[1]) = rodzic1.at(z % ilosc_wierzcholkow);
			wskaznik[1]++;
			wskaznik[1] %= ilosc_wierzcholkow;
		}
	}
	rodzic1 = dziecko1;																		//zastepujemy rodzica pierwszego pierwszym potomkiem
	rodzic2 = dziecko2;																		//zastepujemy rodzica drugiego drugim potomkiem
}

//algorytm partially mapped crossing
void Genetyczny::KrzyzowaniePMX(vector<int>& rodzic1, vector<int>& rodzic2) //1
{
	vector <int> dziecko1(ilosc_wierzcholkow), dziecko2(ilosc_wierzcholkow);				//utworzenie wektorow przechwoujacych nastepne sciezki
	int poczatek, koniec;																	//zmienne pomocniczne do znalezienia czesci wspolnej
	do
	{
		poczatek = rand() % ilosc_wierzcholkow;												//wylosowanie poczatku
		koniec = rand() % ilosc_wierzcholkow;												//wylosowanie konca
	} while (poczatek == koniec);															//tak, zeby nie byly to te same liczby
	if (koniec < poczatek)																	//jezeli liczba odpowiadajaca za koniec jest mniejsza od poczatku
		swap(poczatek, koniec);																//to je zamieniamy, zeby poczatek < koniec

	move(rodzic1.begin() + poczatek, rodzic1.begin() + koniec, dziecko1.begin() + poczatek);//przenosimy wylosowana czesc z rodzica pierwszego do pierwszego ptoomka
	move(rodzic2.begin() + poczatek, rodzic2.begin() + koniec, dziecko2.begin() + poczatek);//przenosimy wylosowana czesc z rodzica drugiego do drugiego potomka

	for (int z = 0; z < poczatek; z++) {													//uzupelniamy pierwsza czesc
		przypisaniePMX(dziecko1, rodzic1, rodzic2, poczatek, koniec, z, z);
		przypisaniePMX(dziecko2, rodzic2, rodzic1, poczatek, koniec, z, z);
	}
	for (int z = koniec; z < ilosc_wierzcholkow; z++) {										//uzpelniamy druga czesc
		przypisaniePMX(dziecko1, rodzic1, rodzic2, poczatek, koniec, z, z);
		przypisaniePMX(dziecko2, rodzic2, rodzic1, poczatek, koniec, z, z);
	}
	rodzic1 = dziecko1;																		//zastepujemy rodzica pierwszego pierwszym potomkiem
	rodzic2 = dziecko2;																		//zastepujemy rodzica drugiego drugim potomkiem
}

//algorytm mutacji scramble
void Genetyczny::MutacjaScramble(vector<int>& dziecko) //0
{
	int i, j;								//zmienne przechwoujace pozycje do zamiany
	do
	{
		i = rand() % ilosc_wierzcholkow;	//wylosowanie pierwszej pozycji
		j = rand() % ilosc_wierzcholkow;	//wylosowanie drugiej pozycji
	} while (i == j);						//nie moga byc takie same
	if (j < i)								//pierwsza pozycja musi byc mniejsza od drugiej
		swap(j, i);							//jesli tak nie jest zamieniamy
	swap(dziecko.at(i), dziecko.at(j));		//zamieniamy dwa wierzcholki o wylosowanych pozycjach
}

//algorytm mutacji inversion
void Genetyczny::MutacjaInversion(vector<int>& dziecko) //1
{
	int i, j;										//zmienne przechwoujace pozycje do zamiany
	do
	{
		i = rand() % ilosc_wierzcholkow;			//wylosowanie pierwszej pozycji
		j = rand() % ilosc_wierzcholkow;			//wylosowanie drugiej pozycji
	} while (i == j);								//nie moga byc takie same
	if (j < i)										//pierwsza pozycja musi byc mniejsza od drugiej
		swap(j, i);									//jesli tak nie jest zamieniamy
	for (int k = 0; k < (j - i) / 2; k++)
	{
		swap(dziecko.at(i + k), dziecko.at(j - k)); //zamieniamy kolejnoscia wierzcholki z wylosowanego zakresu
	}
}

//metoda uzupelniania chromosomu w krzyzowaniu PMX
void Genetyczny::przypisaniePMX(vector <int> &dziecko, vector<int> &rodzic1, vector <int> &rodzic2, int poczatek, int koniec, int tmp, int pozycja)
{
	bool spr = true;
	for (int k = poczatek; k < koniec; k++)				//sprawdzamy czy wierzcholek zastal przepisany z poprzedniego rodzica
	{
		if (rodzic1[k] == rodzic2[tmp])					//sprawdzamy czy dziecko posiada gen
		{
			spr = false;								//ustawiamy zmienna przypisania na false
			przypisaniePMX(dziecko, rodzic1, rodzic2, poczatek, koniec, k, pozycja); //sprawdzamy, czy mozemy przepisac nastepny gen
			break;
		}
	}
	if (spr)											//jezeli dziecko nie ma genu
		dziecko.at(pozycja) = rodzic2.at(tmp);			//przepisujemy ten gen
}

//wyszkuanie najlepszego osobnika
void Genetyczny::zapiszNajlepsza(vector < vector<int>>& populacja)
{
	int minKoszt = INT_MAX, tmp;
	vector<int> najlepszaPopulacji;
	for (int j = 0; j < populacja.size(); j++)
	{
		tmp = liczSciezke(populacja.at(j));
		if (minKoszt > tmp)
		{
			minKoszt = tmp;
			najlepszaPopulacji = populacja.at(j);
		}
	}
	if (koszt > minKoszt)
	{
		najlepsza = najlepszaPopulacji;
		koszt = minKoszt;
	}
}

//wypisanie populacji
void Genetyczny::wypisz(vector < vector<int>>& populacja)
{
	for (int j = 0; j < populacja.size(); j++)
	{
		cout << "Rozwiazanie " << j << endl;
		wypiszDroge(populacja.at(j));
	}
}

//wypisanie drogi
void Genetyczny::wypiszDroge(vector <int> droga)
{
	int koszt = 0;
	cout << "Droga: ";
	for (int i = 0; i < ilosc_wierzcholkow - 1; i++)
	{
		koszt += tab[droga[i]][droga[i + 1]];
		cout << droga[i];
		cout << " - ";
	}
	cout << droga[ilosc_wierzcholkow - 1];
	koszt += tab[droga[ilosc_wierzcholkow - 1]][droga[0]];
	cout << "\nKoszt: " << koszt << endl;

}

//obliczenie sciezki
int Genetyczny::liczSciezke(vector<int> sciezka) {
	int droga = 0;
	for (int i = 0; i < sciezka.size() - 1; ++i) {
		droga += tab[sciezka[i]][sciezka[i + 1]];
	}
	droga += tab[sciezka[ilosc_wierzcholkow - 1]][sciezka[0]];
	return droga;
}



