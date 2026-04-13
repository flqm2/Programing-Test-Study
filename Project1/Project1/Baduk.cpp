#include <iostream>

/* 1. 좌표를 입력 받아 돌을 놓는다.
   2. 입력된 좌표 위치에는 다른 돌을 못 놓는다.
   3. 검은돌과 흰돌을 번갈아 놓는다.
   4. 검은돌의 갯수와 흰돌의 갯수가 출력되게 한다.*/

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

void InputTest(int &a, int &b, bool compare) {
	if (compare == true) {
		cout << "흑돌을 놓을 위치를 입력하세요 [ex 13 10] 종료는 19 19 입력 : ";
	}
	else if (compare == false) {
		cout << "백돌을 놓을 위치를 입력하세요 [ex 13 10] 종료는 19 19 입력 : ";
	}
	cin >> a >> b;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "잘못 입력하셨습니다." << endl;
		InputTest(a, b, compare);
		return;
	}
	else if (a >= BADUK_TABLE || b >= BADUK_TABLE) {
		cout << "값이 테이블(바둑판)의 크기를 넘겼습니다. 다시 입력하세요." << endl;
		InputTest(a, b, compare);
		return;
	}
	return;
}

int main() {
	char bTable[BADUK_TABLE][BADUK_TABLE] = {};
	int input1 = 0, input2 = 0;
	bool wbCompare = true;
	MadeTabel(bTable);
	while (true) {
		system("cls");
		PriTable(bTable);
		InputTest(input1, input2, wbCompare);
		if (input1 == 19 && input2 == 19) {
			cout << "프로그램 종료" << endl;
			break;
		}
		if (wbCompare == true) {
			bTable[input1][input2] = 'O';
		}
		else if(wbCompare == false) {
			bTable[input1][input2] = '@';
		}
		wbCompare != wbCompare;

	}
	return 0;
}