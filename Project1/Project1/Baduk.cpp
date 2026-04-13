#include <iostream>

using namespace std;

const int BADUK_TABLE = 19;

void MadeTabel(char table[][BADUK_TABLE]) {
	for (int i = 0; i < BADUK_TABLE; i++) {
		for (int j = 0; j < BADUK_TABLE; j++) {
			table[i][j] = '+';
		}
	}
}

void PriTable(char table[][BADUK_TABLE]) {
	for (int i = 0; i < BADUK_TABLE; i++) {
		for (int j = 0; j < BADUK_TABLE; j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}

void InputTest(int &h, int &w, bool compare, char table[][BADUK_TABLE]) {
	if (compare == true) {
		cout << "흑돌을 놓을 위치를 입력하세요 [ex 13 10] 종료는 19 19 입력 : ";
	}
	else if (compare == false) {
		cout << "백돌을 놓을 위치를 입력하세요 [ex 13 10] 종료는 19 19 입력 : ";
	}
	cin >> h >> w;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "잘못 입력하셨습니다." << endl;
		InputTest(h, w, compare, table);
		return;
	}
	else if (h > BADUK_TABLE || w > BADUK_TABLE) {
		cout << "값이 테이블(바둑판)의 크기를 넘겼습니다. 다시 입력하세요." << endl;
		InputTest(h, w, compare, table);
		return;
	}
	else if (table[h][w] != '+') {
		cout << "판 위에 이미 돌이 놓여있습니다." << endl;
		InputTest(h, w, compare, table);
		return;
	}
	return;
}

int main() {
	char bTable[BADUK_TABLE][BADUK_TABLE] = {};
	int input1 = 0, input2 = 0, white = 0, black = 0;
	bool wbCompare = true;
	int a = 0;
	MadeTabel(bTable);
	while (true) {
		system("cls");
		PriTable(bTable);
		cout << a << endl;
		cout << "흑돌 : " << black << " 백돌 : " << white << endl;
		InputTest(input1, input2, wbCompare, bTable);
		if (input1 == 19 && input2 == 19) {
			cout << "프로그램 종료" << endl;
			break;
		}
		if (wbCompare == true) {
			bTable[input1][input2] = 'O';
			black++;
		}
		else if(wbCompare == false) {
			bTable[input1][input2] = '@';
			white++;
		}
		
		wbCompare = !wbCompare;

	}
	return 0;
}