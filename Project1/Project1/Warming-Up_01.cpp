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
Determinant originalDet1, originalDet2;

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

void Print() {
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
			muldet.determinant[i][t] = multipul;
		}
	}
	for (int i = 0; i < 4; i++) {
		cout << endl;
		for (int j = 0; j < 4; j++) {
			cout << setw(5) << muldet.determinant[i][j];
		}
	}
}

void DeAdd() {
	Determinant addet;
	for (int i = 0; i < 4; i++) {
		int adder = 0;
		for (int j = 0; j < 4; j++) {
			addet.determinant[i][j] = det1.determinant[i][j] + det2.determinant[i][j];
		}
	}
	for (int i = 0; i < 4; i++) {
		cout << endl;
		for (int j = 0; j < 4; j++) {
			cout << setw(5) << addet.determinant[i][j];
		}
	}
}

void DeMinus() {
	Determinant mindet;
	for (int i = 0; i < 4; i++) {
		int adder = 0;
		for (int j = 0; j < 4; j++) {
			mindet.determinant[i][j] = det1.determinant[i][j] - det2.determinant[i][j];
		}
	}
	for (int i = 0; i < 4; i++) {
		cout << endl;
		for (int j = 0; j < 4; j++) {
			cout << setw(5) << mindet.determinant[i][j];
		}
	}
}

int getDeterminant(int mat[4][4], int n) {
	if (n == 2) {
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	}
	int result = 0;
	for (int col = 0; col < n; col++) {
		int sub[4][4];
		int subRow = 0;
		for (int i = 1; i < n; i++) {
			int subCol = 0;
			for (int j = 0; j < n; j++) {
				if (j == col) continue;
				sub[subRow][subCol] = mat[i][j];
				subCol++;
			}
			subRow++;
		}
		int sign = (col % 2 == 0) ? 1 : -1;
		result += sign * mat[0][col] * getDeterminant(sub, n - 1);
	}
	return result;
}

void TransPosed() {
	Determinant temp1 = det1;
	Determinant temp2 = det2;
	Determinant result1, result2;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result1.determinant[i][j] = temp1.determinant[j][i];
			result2.determinant[i][j] = temp2.determinant[j][i];
		}
	}
	det1 = result1;
	det2 = result2;

	int a = getDeterminant(det1.determinant, 4);
	int b = getDeterminant(det2.determinant, 4);
	Print();
	cout << endl;
	cout << a << setw(5) << b << endl;
}

void RowMin(bool rowCompare) {
	if (rowCompare) {
		originalDet1 = det1;
		originalDet2 = det2;
		int a = 10;
		int b = 10;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (det1.determinant[i][j] < a) {
					a = det1.determinant[i][j];
				}
			}
			for (int t = 0; t < 4; t++) {
				det1.determinant[i][t] -= a;
			}
			a = 10;
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (det2.determinant[i][j] < b) {
					b = det2.determinant[i][j];
				}
			}
			for (int t = 0; t < 4; t++) {
				det2.determinant[i][t] -= b;
			}
			b = 10;
		}
	}
	else {
		det1 = originalDet1;
		det2 = originalDet2;
	}
	system("cls");
	Print();
}

void ColMax(bool colCompare) {
	if (colCompare) {
		originalDet1 = det1;
		originalDet2 = det2;
		int a = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (det1.determinant[j][i] > a) {
					a = det1.determinant[j][i];
				}
			}
			for (int t = 0; t < 4; t++) {
				det1.determinant[t][i] += a;
			}
			a = 0;
		}
		a = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (det2.determinant[j][i] > a) {
					a = det2.determinant[j][i];
				}
			}
			for (int t = 0; t < 4; t++) {
				det2.determinant[t][i] += a;
			}
			a = 0;
		}
	}
	else {
		det1 = originalDet1;
		det2 = originalDet2;
	}
	system("cls");
	Print();
}

void Plus() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			det1.determinant[i][j] += 1;
			if (det1.determinant[i][j] == 10) {
				det1.determinant[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			det2.determinant[i][j] += 1;
			if (det2.determinant[i][j] == 10) {
				det2.determinant[i][j] = 0;
			}
		}
	}
	Print();
}

void Minus() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			det1.determinant[i][j] -= 1;
			if (det1.determinant[i][j] == -1) {
				det1.determinant[i][j] = 9;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			det2.determinant[i][j] -= 1;
			if (det2.determinant[i][j] == -1) {
				det2.determinant[i][j] = 9;
			}
		}
	}
	Print();
}


int main() {
	MadeBoard();
	string input;
	bool compare1 = false;
	bool compare2 = false;
	while (true) {

		cin >> input;
		if (input == "m") {
			DeMulti();
		}
		else if (input == "a") {
			DeAdd();
		}
		else if (input == "d") {
			DeMinus();
		}
		else if (input == "r") {
			int result1 = getDeterminant(det1.determinant, 4);
			int result2 = getDeterminant(det2.determinant, 4);
			cout << result1 << setw(5) << result2;
		}
		else if (input == "t") {
			TransPosed();
		}
		else if (input == "e") {
			compare1 = !compare1;
			RowMin(compare1);
		}
		else if (input == "f") {
			compare2 = !compare2;
			ColMax(compare2);
		}
		else if (input == "+") {
			Plus();
		}
		else if (input == "-") {
			Minus();
		}
		else if (input == "s") {
			system("cls");
			MadeBoard();
		}
		else if (input == "q") {
			break;
		}
		else {
			cout << "잘못 입력" << endl;
			continue;

		}
	}
	return 0;
}