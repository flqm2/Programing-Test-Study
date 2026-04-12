#include <iostream>

using namespace std;

int main() {
	int x, y, count = 0, black = 0, white = 0;
	char baduk[19][19] = { 0 };
	const char* c;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			baduk[i][j] = '+';
		}
	}
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			cout << baduk[i][j] << " ";
		}
		cout << endl;
	}
	if (count % 2 == 0) {
		c = "흑돌";
	}
	else {
		c = "백돌";
	}
	cout << c << "을 놓을 위치를 입력하세요 (예 1 2) 종료는 20 20 입력 : ";
	cin >> x >> y;
	if (x == 20 && y == 20) {
		cout << "종료 되었습니다.";
		return 0;
	}
	system("cls");
	while (true)
	{
		if ((x == 20 && y == 20) || (x > 20 || y > 20)) {
			cout << "종료 되었습니다.";
			break;
		}
		if (baduk[x][y] != '+') {
			cout << "이미 돌이 놓여 있습니다." << endl;
		}
		else {
			if (count % 2 == 0) {
				baduk[x][y] = 'o';
				count++;
				black++;
			}
			else {
				baduk[x][y] = '@';
				count++;
				white++;
			}

		}
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				cout << baduk[i][j] << " ";
			}
			cout << endl;
		}
		cout << "흑돌 : " << black << " 백돌 : " << white;
		cout << c << "을 놓을 위치를 입력하세요 (예 1 2) 종료는 20 20 입력 : ";
		cin >> x >> y;
		system("cls");
	}
}