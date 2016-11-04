#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <queue>
#include <functional>
void wypisywanie();

using namespace std;

class slistEl {
public:
	slistEl *next;
	int roomNumber, distance, predecessor, priceOfEntrance, numberOfNeighbours;
	bool QS;

	slistEl() {
		this->next = NULL;
		this->distance = INT32_MAX;
		this->predecessor = -1;
		this->priceOfEntrance = 0;
		this->numberOfNeighbours = 2;
		this->QS = false;
	}// numer wêz³a docelowego i waga krawêdzi
};
class kartezjan {
public:
	int dystans, numerPokoju;

	kartezjan(int dystans, int numerPokoju) {
		this->dystans = dystans;
		this->numerPokoju = numerPokoju;
	}
	/*bool operator >(const kartezjan &v) {
		if (this->dystans > v.dystans) {
			return true;
		} else {
			return false;
		}
	}
	bool operator ==(const kartezjan &v) {
		if (this->dystans == v.dystans) {
			return true;
		} else {
			return false;
		}
	}*/
};
struct MoreThanMethod {
	bool operator()(const kartezjan &u, const kartezjan &v) {
		return u.dystans > v.dystans;
	}
};
void wypisywanie(int m, int n, slistEl *graf) {//  Sprawdzenie wypisywania elementow w tablicy
	slistEl *pw;
	pw = graf[0].next;
	//cout << "graf[0]: " << graf[0].roomNumber << " " << pw->roomNumber << " " << pw->next->roomNumber;
	for (int z = 0; z < m*n; z++) {
		cout << graf[z].roomNumber << " ";
		pw = graf[z].next;
		for (int j = 0; j < graf[z].numberOfNeighbours; j++) {
			cout << pw->roomNumber << " ";
			pw = pw->next;
		}
		cout << endl;
	}
}
int main() {
	slistEl *pw;
	unsigned int numberOfBargains;
	int numberOfSets, m, n;
	int roomsToVisit[18];
	priority_queue <kartezjan, vector <kartezjan>, MoreThanMethod> kolejkaliczb;
	queue <int> roomNumbersQueue;
	cin >> numberOfSets;
	for (int i = 0; i < numberOfSets; ++i) {
		cin >> m >> n;
		slistEl *graf = new slistEl[m * n]();
		for (int j = m - 1; j >= 0; --j) { // wpisujemy ceny wejscia do poszczegolnych pokojow
			for (int k = 0; k < n; ++k) {
				cin >> graf[j * n + k].priceOfEntrance;
				graf[j * n + k].roomNumber = j * n + k;
			}
		}
		cin >> numberOfBargains;
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < n; k++) {
				slistEl *pokoj1 = new slistEl();
				slistEl *pokoj2 = new slistEl();
				if (j * n + k == 0) { // Left down
					*pokoj1 = graf[1];
					cout << "j*n+1: " << j*n + 1 << "graf[j*n+1].roomnumber: " << pokoj1->roomNumber << endl;
					*pokoj2 = graf[n];
				} else if (j * n + k == n - 1) { // Right down
					*pokoj1 = graf[n-2];
					*pokoj2 = graf[2*n-1];
				} else if (j * n + k == n * (m - 1)) { // Left up
					*pokoj1 = graf[(j - 1) * n + k];
					*pokoj2 = graf[j * n + k + 1];
				} else if (j * n + k == m * n - 1) { // Right Up
					*pokoj1 = graf[j * n + k - 1];
					*pokoj2 = graf[(j - 1) * n + k];
				} else {
					slistEl *pokoj3 = new slistEl();
					graf[j*n + k].numberOfNeighbours = 3;
					if ((j == 0 || j == m - 1) && (k > 0 && k < n - 1)) { // Top / Bottom edge
						*pokoj1 = graf[j * n + k - 1];
						*pokoj2 = graf[j * n + k + 1];
						if (j == 0) { // Bottom edge
							*pokoj3 = graf[(j + 1)*n + k];
						} else { // Top edge
							*pokoj3 = graf[(j - 1) * n + k];
						}
					} else if ((k == 0 || k == n - 1) && (j > 0 && j < m - 1)) { // Left / Right edge
						*pokoj1 = graf[(j + 1) * n + k];
						*pokoj2 = graf[(j - 1) * n + k];
						if (k == 0) { // Left Edge
							*pokoj3 = graf[j * n + k + 1];
						} else { // Right Edge
							*pokoj3 = graf[j * n + k - 1];
						}
					} else {
						slistEl *pokoj4 = new slistEl();
						graf[j*n + k].numberOfNeighbours = 4;
						*pokoj1 = graf[j * n + k - 1];
						*pokoj2 = graf[j * n + k + 1];
						*pokoj3 = graf[(j - 1) * n + k];
						*pokoj4 = graf[(j + 1) * n + k];
						pokoj3->next = pokoj4;
					}
					pokoj2->next = pokoj3;
				}
				graf[j * n + k].next = pokoj1;
				pokoj1->next = pokoj2;
				/*pw = graf[0].next;
				cout << "graf[0]: " << graf[0].roomNumber << " graf[0].next: " << pw->roomNumber << " graf[0].next.next: " << pw->next->roomNumber << endl;*/
			}
		}		
		for (int f = 0; f < 2 * numberOfBargains; f += 2) {
			cin >> roomsToVisit[f] >> roomsToVisit[f + 1];
			graf[(m - roomsToVisit[f]) * n + roomsToVisit[f + 1] - 1].priceOfEntrance *= -1;
			graf[0].distance = graf[0].priceOfEntrance;
			kartezjan *k = new kartezjan(graf[0].distance, 0);
			kolejkaliczb.push(*k);
			cout << kolejkaliczb.top().dystans;
			for (int j = 0; j < m * n; j++) {
				cout << " FIRST LOOP:  j: " << j << endl;
				while (graf[kolejkaliczb.top().numerPokoju].QS) {
					kolejkaliczb.pop();
				}
				kartezjan *k = new kartezjan(kolejkaliczb.top().dystans, kolejkaliczb.top().numerPokoju);
				cout << "k room number = " << k->numerPokoju << "  k distance: " << k->dystans << endl;
				kolejkaliczb.pop();
				//for (k = j; graf[k].QS; k++);
				cout << " SECOND LOOP:  k: " << k->numerPokoju << endl;
				pw = &graf[k->numerPokoju];
				graf[k->numerPokoju].QS = true;
				cout << "Room number: " << pw->roomNumber << "  distance: " << pw->distance << endl;
				pw = pw->next;
				for (int z = 0; z < graf[k->numerPokoju].numberOfNeighbours; z++, pw = pw->next) {
					cout << "Sasiad: pw->roomNumber: " << pw->roomNumber << endl;
					if (!graf[pw->roomNumber].QS &&
						(graf[pw->roomNumber].distance > graf[k->numerPokoju].distance + graf[pw->roomNumber].priceOfEntrance)) {
						cout << "graf[pw->roomNumber].distance: " << graf[pw->roomNumber].distance << " graf[k->numerPokoju].distance: " << graf[k->numerPokoju].distance << " graf[pw->roomNumber].priceOfEntrance: " << graf[pw->roomNumber].priceOfEntrance << endl;
						graf[pw->roomNumber].distance = graf[k->numerPokoju].distance + graf[pw->roomNumber].priceOfEntrance;
						cout << "weszlo " << endl;
					}
					kartezjan *temp = new kartezjan(graf[pw->roomNumber].distance, pw->roomNumber);
					kolejkaliczb.push(*temp);
					roomNumbersQueue.push(pw->roomNumber);
					cout << "iteracja, graf[k].sasiedzi: " << graf[k->numerPokoju].numberOfNeighbours << " Room number: " << kolejkaliczb.top().numerPokoju << "  distance: " << kolejkaliczb.top().dystans << endl;
				}
				cout << "Room number: " << graf[k->numerPokoju].roomNumber << "  distance: " << graf[k->numerPokoju].distance << endl;
			}
			cout << graf[3].distance << endl;
		}
		delete[] graf;
	}
	return 0;
}



