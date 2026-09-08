#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Diagram {
	int x1, x2, y1, y2;
	char symbol;
};

Diagram shape1;
Diagram shape2;

string board[50][50] = {};
vector <int> diagram1;
vector <int> diagram2;

int boardSize = 30;
int increaseCount = 0;
int decreaseCount = 0;

int Mod(int value) {
	return ((value % boardSize) + boardSize) % boardSize;
}

void PrintBoard() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD originalAttributes = consoleInfo.wAttributes;
	for (int i = 0; i < boardSize; i++) {		//출력
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] == "#") {
				SetConsoleTextAttribute(hConsole, 4);
				cout << board[i][j];
				SetConsoleTextAttribute(hConsole, originalAttributes);
			}
			else {
				cout << board[i][j];
			}
			cout << " ";
		}
		cout << endl;
	}
}

void MadeBoard() {
	for (int i = 0; i < boardSize; i++) {		//입력
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = ".";
		}
	}
	PrintBoard();
}

void UpdateBoard() {
	MadeBoard();
	system("cls");
	for (int i = shape1.y1; i <= shape1.y2; i++) {
		for (int j = shape1.x1; j <= shape1.x2; j++) {
			board[Mod(i)][Mod(j)] = shape1.symbol;
		}
	}
	for (int i = shape2.y1; i <= shape2.y2; i++) {
		for (int j = shape2.x1; j <= shape2.x2; j++) {
			if (board[Mod(i)][Mod(j)] != ".") {
				board[Mod(i)][Mod(j)] = "#";
			}
			else {
				board[Mod(i)][Mod(j)] = shape2.symbol;
			}
		}
	}
	PrintBoard();
}

void PrintToBoardSquare() {
	shape1.symbol = 'O';
	shape2.symbol = '@';
	cout << "첫 번째 도형" << endl;
	cout << "첫번째 좌표 값 x, y를 입력하세요 (ex : 3 5) : ";
	cin >> shape1.x1 >> shape1.y1;
	cout << "두번째 좌표 값 x, y를 입력하세요 (ex : 8 10) : ";
	cin >> shape1.x2 >> shape1.y2;

	if (shape1.x1 > shape1.x2) swap(shape1.x1, shape1.x2);
	if (shape1.y1 > shape1.y2) swap(shape1.y1, shape1.y2);

	cout << endl << "두 번째 도형" << endl;
	cout << "첫번째 좌표 값 x, y를 입력하세요 (ex : 3 5) : ";
	cin >> shape2.x1 >> shape2.y1;
	cout << "두번째 좌표 값 x, y를 입력하세요 (ex : 8 10) : ";
	cin >> shape2.x2 >> shape2.y2;

	if (shape2.x1 > shape2.x2) swap(shape2.x1, shape2.x2);
	if (shape2.y1 > shape2.y2) swap(shape2.y1, shape2.y2);

	UpdateBoard();
}

void MoveX(Diagram& shape, int direction) {
	shape.x1 += direction;
	shape.x2 += direction;
	UpdateBoard();
}

void MoveY(Diagram& shape, int direction) {
	shape.y1 += direction;
	shape.y2 += direction;
	UpdateBoard();
}

void ScaleBoth(Diagram& shape, int direction) {
	if (direction > 0) {
		if (shape.x2 + 1 < boardSize) shape.x2++;
		if (shape.y2 + 1 < boardSize) shape.y2++;
	}
	else {
		if (shape.x2 - 1 >= shape.x1) shape.x2--;
		if (shape.y2 - 1 >= shape.y1) shape.y2--;
	}
	UpdateBoard();
}

void ScaleX(Diagram& shape, int direction) {
	if (direction > 0) {
		if (shape.x2 + 1 < boardSize) shape.x2++;
	}
	else {
		if (shape.x2 - 1 >= shape.x1) shape.x2--;
	}
	UpdateBoard();
}

void ScaleY(Diagram& shape, int direction) {
	if (direction > 0) {
		if (shape.y2 + 1 < boardSize) shape.y2++;
	}
	else {
		if (shape.y2 - 1 >= shape.y1) shape.y2--;
	}
	UpdateBoard();
}

void ScaleDiagonal(Diagram& shape, int xDirection, int yDirection) {
	if (xDirection > 0) {
		if (shape.x2 + 1 < boardSize) shape.x2++;
	}
	else {
		if (shape.x2 - 1 >= shape.x1) shape.x2--;
	}
	if (yDirection > 0) {
		if (shape.y2 + 1 < boardSize) shape.y2++;
	}
	else {
		if (shape.y2 - 1 >= shape.y1) shape.y2--;
	}
	UpdateBoard();
}

void PrintArea(Diagram& shape) {
	int width = shape.x2 - shape.x1 + 1;
	int height = shape.y2 - shape.y1 + 1;
	cout << "면적: " << width << " x " << height << " = " << width * height << endl;
}

void IncreaseBoard() {
	if (increaseCount >= 10) {
		cout << "더 이상 보드를 늘릴 수 없습니다." << endl;
		return;
	}
	boardSize++;
	increaseCount++;
	UpdateBoard();
}

void DecreaseBoard() {
	if (decreaseCount >= 20) {
		cout << "더 이상 보드를 줄일 수 없습니다." << endl;
		return;
	}
	int newSize = boardSize - 1;
	if (Mod(shape1.x2) >= newSize || Mod(shape1.y2) >= newSize ||
		Mod(shape2.x2) >= newSize || Mod(shape2.y2) >= newSize) {
		cout << "도형이 보드 밖으로 나가서 줄일 수 없습니다." << endl;
		return;
	}
	boardSize = newSize;
	decreaseCount++;
	UpdateBoard();
}

void ResetAll() {
	boardSize = 30;
	increaseCount = 0;
	decreaseCount = 0;
	PrintToBoardSquare();
}

int main() {
	MadeBoard();
	PrintToBoardSquare();
	string input1, input2;
	while (true) {
		cout << "명령을 입력할 도형을 선택하세요 (a , b) : ";
		cin >> input1;
		if (input1 != "a" && input1 != "b") {
			cout << "잘못 입력하셨습니다. 첫 글자는 a, b 둘중 하나만 선택할 수 있습니다." << endl;
			continue;
		}

		Diagram& shape = (input1 == "a") ? shape1 : shape2;

		cout << "명령어를 입력하세요 : ";
		cin >> input2;

		if (input2 == "x") {
			MoveX(shape, 1);
		}
		else if (input2 == "X") {
			MoveX(shape, -1);
		}
		else if (input2 == "y") {
			MoveY(shape, 1);
		}
		else if (input2 == "Y") {
			MoveY(shape, -1);
		}
		else if (input2 == "s") {
			ScaleBoth(shape, -1);
		}
		else if (input2 == "S") {
			ScaleBoth(shape, 1);
		}
		else if (input2 == "i") {
			ScaleX(shape, 1);
		}
		else if (input2 == "I") {
			ScaleX(shape, -1);
		}
		else if (input2 == "j") {
			ScaleY(shape, 1);
		}
		else if (input2 == "J") {
			ScaleY(shape, -1);
		}
		else if (input2 == "a") {
			ScaleDiagonal(shape, 1, -1);
		}
		else if (input2 == "A") {
			ScaleDiagonal(shape, -1, 1);
		}
		else if (input2 == "b") {
			PrintArea(shape);
		}
		else if (input2 == "c") {
			IncreaseBoard();
		}
		else if (input2 == "d") {
			DecreaseBoard();
		}
		else if (input2 == "r") {
			ResetAll();
		}
		else if (input2 == "q") {
			break;
		}
		else {
			cout << "잘못 입력하셨습니다." << endl;
			continue;
		}
	}
	return 0;
}