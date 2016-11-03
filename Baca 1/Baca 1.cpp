#include "stdafx.h"
#include <iostream>
#include <cstdio>

void wypisywanie();

using namespace std;

struct slistEl {
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

void wypisywanie(int m, int n, slistEl *graf) {//  Sprawdzenie wypisywania elementow w tablicy
	slistEl *pw;
	for (int i = 0; i < m*n; i++) {
		cout << graf[i].roomNumber << " ";
		pw = graf[i].next;
		while (pw != NULL) {
			cout << pw->roomNumber << " ";
			pw = pw->next;
		}
		cout << endl;
	}
}
int main() {
	slistEl *pw;
	unsigned int numberOfBargains;
	int numberOfSets, m, n, k, l;
	int roomsToVisit[18];
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
		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < n; ++k) {
				slistEl *pokoj1;
				slistEl *pokoj2;
				if (j * n + k == 0) { // Left down
					pokoj1 = &graf[j * n + 1];
					//	pokoj1->roomNumber;
					pokoj2 = &graf[(j + 1) * n];
				} else if (j * n + k == n - 1) { // Right down
					pokoj1 = &graf[j * n + k - 1];
					pokoj2 = &graf[(j + 1) * n + k];
				} else if (j * n + k == n * (m - 1)) { // Left up
					pokoj1 = &graf[(j - 1) * n + k];
					pokoj2 = &graf[j * n + k + 1];
				} else if (j * n + k == m * n - 1) { // Right Up
					pokoj1 = &graf[j * n + k - 1];
					pokoj2 = &graf[(j - 1) * n + k];
				} else {
					slistEl *pokoj3;
					graf[j*n + k].numberOfNeighbours = 3;
					if ((j == 0 || j == m - 1) && (k > 0 && k < n - 1)) { // Top / Bottom edge
						pokoj1 = &graf[j * n + k - 1];
						pokoj2 = &graf[j * n + k + 1];
						if (j == 0) { // Bottom edge
							pokoj3 = &graf[(j + 1)*n + k];
						} else { // Top edge
							pokoj3 = &graf[(j - 1) * n + k];
						}
					} else if ((k == 0 || k == n - 1) && (j > 0 && j < m - 1)) { // Left / Right edge
						pokoj1 = &graf[(j + 1) * n + k];
						pokoj2 = &graf[(j - 1) * n + k];
						if (k == 0) { // Left Edge
							pokoj3 = &graf[j * n + k + 1];
						} else { // Right Edge
							pokoj3 = &graf[j * n + k - 1];
						}
					} else {
						slistEl *pokoj4;
						graf[j*n + k].numberOfNeighbours = 4;
						pokoj1 = &graf[j * n + k - 1];
						pokoj2 = &graf[j * n + k + 1];
						pokoj3 = &graf[(j - 1) * n + k];
						pokoj4 = &graf[(j + 1) * n + k];
						pokoj3->next = pokoj4;
					}
					pokoj2->next = pokoj3;
				}
				pokoj1->next = pokoj2;
				graf[j * n + k].next = pokoj1;
			}
		}
		for (int j = 0; j < 2 * numberOfBargains; j += 2) {
			cin >> roomsToVisit[j] >> roomsToVisit[j + 1];
			cout << roomsToVisit[j] << " " << roomsToVisit[j + 1] << " " << (m - roomsToVisit[j])*n + roomsToVisit[j + 1] - 1 << endl;
			graf[(m - roomsToVisit[j]) * n + roomsToVisit[j + 1] - 1].priceOfEntrance *= -1;
		}

		for (int j = 0; j < m * n; j++) {
			cout << " FIRST LOOP:  j: " << j << endl;
			for (k = j; graf[k].QS; k++);
			cout << " SECOND LOOP:  k: " << k << endl;
			graf[k].QS = true;
			pw = &graf[k];
			for (int z = 0; z < graf[k].numberOfNeighbours; z++, pw = pw->next) {
				cout << "iteracja, graf[k].numberOfN: " << graf[k].numberOfNeighbours << endl;
				if (!graf[pw->roomNumber].QS &&
					(graf[pw->roomNumber].distance > graf[k].distance + graf[pw->roomNumber].priceOfEntrance)) {
					graf[pw->roomNumber].distance = graf[k].distance + graf[pw->roomNumber].priceOfEntrance;
				}
			}
		}
		cout << graf[8].priceOfEntrance;
		delete[] graf;
	}
	return 0;
}



