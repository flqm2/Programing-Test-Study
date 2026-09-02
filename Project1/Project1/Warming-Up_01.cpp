#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

struct Determinant
{
	int determinant[4][4];
};

Determinant det1;
Determinant det2;

void MadeBoard() {
	random_device rd1;
	random_device rd2;
	mt19937 gen1(rd1());
	mt19937 gen2(rd2());
	uniform_int_distribution<int> dist1(1, 9);
	uniform_int_distribution<int> dist2(1, 9);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			det1.determinant[i][j] = dist1(gen1);
			det2.determinant[i][j] = dist2(gen2);
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << setw(5) << det1.determinant[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 4; i++) {
		cout << endl;
		for (int j = 0; j < 4; j++) {
			cout << setw(5) << det2.determinant[i][j];
		}
	}
	cout << endl;
}

void DeMulti() {
	Determinant muldet;
	for (int t = 0; t < 4; t++) {
		for (int i = 0; i < 4; i++) {
			int multipul = 0;
			for (int j = 0; j < 4; j++) {
				multipul += det1.determinant[i][j] * det2.determinant[j][t];
			}
			muldet.determinant[t][i] = multipul;
		}
	}
	for (int i = 0; i < 4; i++) {
		cout << endl;
		for (int j = 0; j < 4; j++) {
			cout << setw(5) << muldet.determinant[i][j];
		}
	}
}

int main() {
	MadeBoard();
	int input = 0;
	cin >> input;
	if (input == 1) {
		DeMulti();
	}
}