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

string board[30][30] = {};
vector <int> diagram1;
vector <int> diagram2;

void PrintBoard() {
	for (int i = 0; i < 30; i++) {		//출력
		for (int j = 0; j < 30; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void MadeBoard() {
	for (int i = 0; i < 30; i++) {		//입력
		for (int j = 0; j < 30; j++) {
			board[i][j] = ".";
		}
	}

	PrintBoard();
}

void PrintToBoardSquare() {
	shape1.symbol = 'O';
	shape2.symbol = '@';
	cout << "첫번째 좌표 값 x, y를 입력하세요 (ex : 3 5) : ";
	cin >> shape1.x1 >> shape1.y1;
	cout << "두번째 좌표 값 x, y를 입력하세요 (ex : 8 10) : ";
	cin >> shape1.x2 >> shape1.y2;

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			
		}
	}
	system("cls");
	PrintBoard();
}

int main() {
	int count = 0;
	MadeBoard();
	count = PrintToBoardSquare();
	count = PrintToBoardSquare();
	cout << "겹치는 개수 : " << count << endl;
	return 0;

}