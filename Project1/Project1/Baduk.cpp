#include <iostream>

using namespace std;

const int BADUK_TABLE = 19;

char bTable[BADUK_TABLE][BADUK_TABLE] = {};
int input1 = 0, input2 = 0, white = 0, black = 0;
bool wbCompare = true;
bool progreamExit = false;

void MadeTabel(char table[][BADUK_TABLE]) {
	for (int i = 0; i < BADUK_TABLE; i++) {
		for (int j = 0; j < BADUK_TABLE; j++) {
			table[i][j] = '+';
		}
	}
}

void PriTable(char table[][BADUK_TABLE]) {
	system("cls");
	for (int i = 0; i < BADUK_TABLE; i++) {
		for (int j = 0; j < BADUK_TABLE; j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}

void InputTest(int &h, int &w, bool &compare, char table[][BADUK_TABLE]) {
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
	if (h == 19 && w == 19) {
		return;
	}
	else if (h < 0 || h >= BADUK_TABLE || w < 0 || w >= BADUK_TABLE) {
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

void BadukPri(int &input1, int &input2, int &black, int &white, char Table[][BADUK_TABLE], bool &wbCompare) {
	if (input1 == 19 && input2 == 19) {
		return;
	}
	if (wbCompare == true) {
		Table[input1][input2] = 'O';
		black++;
	}
	else if (wbCompare == false) {
		Table[input1][input2] = '@';
		white++;
	}

	wbCompare = !wbCompare;
}

void Pri(int &input) {
	cout << "사용할 명령어의 번호를 입력하세요." << endl;
	cout << "0. 오목 두기" << endl;
	cout << "1. 가로 or 세로줄 돌 개수 확인" << endl;
	cout << "2. 가로 or 세로줄 연속된 돌 확인" << endl;
	cout << "3. 대각선줄 역속된 돌 확인" << endl;
	cout << "4. 가로줄 연속된 돌 좌표 표시" << endl;
	cout << "5. 프로그램 종료" << endl;
	cin >> input;
	system("cls");
}
void CaseZero() {
	while (true)
	{
		PriTable(bTable);
		cout << "흑돌 : " << black << " 백돌 : " << white << endl;
		InputTest(input1, input2, wbCompare, bTable);
		BadukPri(input1, input2, black, white, bTable, wbCompare);
		if (input1 == 19 && input2 == 19) {
			system("cls");
			cout << "프로그램 종료" << endl << endl;
			break;
		}
	}
}
void QueSw(int &input) {
	switch (input) {
		case 0:
			CaseZero();
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			system("cls");
			cout << "프로그램을 종료합니다.";
			progreamExit = true;
			break;
		default:
			break;
	}
}

int main() {
	int input = 0;
	MadeTabel(bTable);
	while (true) {
		if (progreamExit == true) {
			return 0;
		}
		Pri(input);
		QueSw(input);
	}
	return 0;
}