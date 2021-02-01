#include"Graf.h"
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <ctime>

class Genetyczny
{
private:

	int** tab;
	int ilosc_wierzcholkow;
	float stop;
	int rozmiarPopulacji = 10;
	float wspKrzyzowania;
	float wspMutacji;
	bool algorytmKrzyzowania;
	bool algorytmMutacji;
	vector<int> najlepsza;
	int koszt = INT_MAX;

public:

	Genetyczny(Graf graf, float stop, int rozmiarPopulacji, float wspKrzyzowania, float wspMutacji, bool algorytmKrzyzowania, bool algorytmMutacji);
	int liczSciezke(vector<int> sciezka);
	void start();
	void KrzyzowanieOX(vector<int> &rodzic1, vector<int> &rodzic2); //0
	void KrzyzowaniePMX(vector<int> &rodzic1, vector<int> &rodzic2); //1
	void MutacjaScramble(vector<int> &dziecko); //0
	void MutacjaInversion(vector<int> &dziecko); //1
	void KrzyzowanieAlgorytm(vector<vector<int>> &populacja, vector<vector<int>> &nowaPopulacja);
	void MutacjaAlgorytm(vector<vector<int>> &populacja);
	void Selekcja(vector<vector<int>> &populacja, int RozmiarTurnieju);
	void wypisz(vector < vector<int>> &populacja);
	void wypiszDroge(vector <int> droga);
	void zapiszNajlepsza(vector < vector<int>> &populacja);
	void przypisaniePMX(vector <int> &dziecko, vector<int> &rodzic1, vector <int> &rodzic2, int poczatek, int koniec, int tmp, int pozycja);
};