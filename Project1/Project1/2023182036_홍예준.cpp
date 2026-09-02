#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

const int BADUK_TABLE = 19;
const int MAX_STONE = BADUK_TABLE * BADUK_TABLE;

char bTable[BADUK_TABLE][BADUK_TABLE] = {};
int input1 = 0, input2 = 0, white = 0, black = 0;
bool wbCompare = true;
bool progreamExit = false;
bool fileLoad = false;

int undoStackX[MAX_STONE];
int undoStackY[MAX_STONE];
int undoTop = -1;

int redoStackX[MAX_STONE];
int redoStackY[MAX_STONE];
int redoTop = -1;

bool LoadFile(const string& filename) {
	fstream file(filename);
	if (!file.is_open()) {
		return true;
	}
	return file.peek() == ifstream::traits_type::eof();
}

void FileLoadTable() {
	string c;
	if (LoadFile("Baduk.txt") == false) {
		cout << "파일 존재 리로드 ?";
		getline(cin, c);
		if (c == "Y" || c == "y") {
			black = 0;
			white = 0;
			fileLoad = true;

			ifstream file("Baduk.txt");
			if (file.is_open()) {
				for (int i = 0; i < BADUK_TABLE; i++) {
					for (int j = 0; j < BADUK_TABLE; j++) {
						file >> bTable[i][j];

						if (bTable[i][j] == 'O') black++;
						else if (bTable[i][j] == '@') white++;
					}
				}
				if (black > white) wbCompare = false;
				else wbCompare = true;
			}
			file.close();
			cout << "파일 로드 완료" << endl;
			return;
		}
		else if (c == "N" || c == "n") {
			fileLoad = false;
			return;
		}
		else {
			cout << "잘못 입력 파일 초기화" << endl;
			fileLoad = false;
			return;
		}
	}
	else {
		fileLoad = false;
		return;
	}
}

void SaveFile() {
	ofstream outfile("Baduk.txt");
	if (!outfile.is_open()) {
		cout << "파일 로드 실패 저장 하지 않고 프로그램을 종료합니다." << endl;
	}
	for (int i = 0; i < BADUK_TABLE; i++) {
		for (int j = 0; j < BADUK_TABLE; j++) {
			outfile << bTable[i][j];
		}
		outfile << endl;
	}
	outfile.close();
	cout << "게임 내용을 저장합니다." << endl;
}

void Undo() {
	if (undoTop < 0) {
		cout << "스택에 돌이 저장되어 있지 않습니다.";
		return;
	}

	int x = undoStackX[undoTop];
	int y = undoStackY[undoTop];
	undoTop--;

	redoTop++;
	redoStackX[redoTop] = x;
	redoStackY[redoTop] = y;

	char undotable = bTable[x][y];
	bTable[x][y] = '+';
	if (undotable == 'O') black--;
	else if (undotable == '@') white--;

	wbCompare = !wbCompare;

	cout << "무르기 사용" << endl;
}

void Redo() {
	if (redoTop < 0) {
		cout << "무르기를 한적이 없습니다.";
		return;
	}

	int x = redoStackX[redoTop];
	int y = redoStackY[redoTop];
	redoTop--;

	undoTop++;
	undoStackX[undoTop] = x;
	undoStackY[undoTop] = y;
	
	if (wbCompare == false) {
		bTable[x][y] = 'O';
	}
	else {
		bTable[x][y] = '@';
	}
	cout << "무르기 취소" << endl;
}

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

void BadukPri() {
	if (input1 == 19 && input2 == 19) {
		return;
	}
	if (wbCompare == true) {
		bTable[input1][input2] = 'O';
		black++;
	}
	else if (wbCompare == false) {
		bTable[input1][input2] = '@';
		white++;
	}

	undoTop++;
	undoStackX[undoTop] = input1;
	undoStackY[undoTop] = input2;

	redoTop = -1;

	wbCompare = !wbCompare;
}

void InputTest(int& h, int& w, bool& compare, char table[][BADUK_TABLE]) {
	PriTable(bTable);
	if (compare == true) {
		cout << "흑돌을 놓을 위치를 입력하세요 [ex 13 10] 종료는 19 19 입력 : ";
	}
	else if (compare == false) {
		cout << "백돌을 놓을 위치를 입력하세요 [ex 13 10] 종료는 19 19 입력 : ";
	}

	string c;
	cin >> c;

	if (c == "U" || c == "u") {
		Undo();
		return;
	}
	else if (c == "R" || c == "r") {
		Redo();
		return;
	}

	h = atoi(c.c_str());
	cin >> w;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "잘못 입력하셨습니다." << endl;
		InputTest(h, w, compare, table);
		return;
	}

	if (h == 19 && w == 19) {
		system("cls");
		progreamExit = true;
		cout << "프로그램 종료 판을 저장하겠습니까? [Y/N] ";
		string c;
		cin.ignore(1000, '\n');
		getline(cin, c);
		if (c == "Y" || c == "y") {
			SaveFile();
			return;
		}
		else if (c == "N" || c == "n") {
			cout << "게임 상황을 저장하지 않고 종료합니다." << endl;
			return;
		}
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
	else {
		BadukPri();
	}
	return;
}


int main() {
	FileLoadTable();
	if (fileLoad == false) {
		MadeTabel(bTable);
	}
	int input = 0;
	while (true) {
		if (progreamExit == true) return 0;
		InputTest(input1, input2, wbCompare, bTable);
	}
	return 0;
}