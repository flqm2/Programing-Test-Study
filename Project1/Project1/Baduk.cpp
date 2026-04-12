#include <iostream>

using namespace std;

const int BADUK_TABLE = 19;

void MadeTable(char table[][BADUK_TABLE]) {
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

void Test(int a, int b) {
	cout << "2놓을 돌의 위치를 입력하세요. [ex 12 12] 종료는 19 19 입력";
	cin >> a >> b;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "잘못 입력하셨습니다2.";
	}
}

void Test2(int a, int b) {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "잘못 입력하셨습니다3.";
	}
}

int main() {
	char bTabel[BADUK_TABLE][BADUK_TABLE] = { 0 };
	int input1 = 0, input2 = 0;
	MadeTable(bTabel);
	PriTable(bTabel);
	while (true) {
		cout << "1놓을 돌의 위치를 입력하세요. [ex 12 12] 종료는 19 19 입력";
		cin >> input1 >> input2;
		Test2(input1, input2);
	}
	return 0;
}