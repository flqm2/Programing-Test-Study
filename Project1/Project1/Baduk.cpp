#include <iostream>

using namespace std;

const int BADUK_TABLE = 19;

char bTable[BADUK_TABLE][BADUK_TABLE] = {};
int input1 = 0, input2 = 0, white = 0, black = 0;
bool wbCompare = true;
bool progreamExit = false;

int TextTest(const char* str1, const char* str2) {
	while (*str1 != '\0' && *str1 == *str2){
		str1++;
		str2++;
	}
	return *(const char*)str1 - *(const char*)str2;
}

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

	wbCompare = !wbCompare;
}

void CaseZero() {
	bool zeroCompare = true;
	for (int i = 0; i < BADUK_TABLE; i++) {
		for (int j = 0; j < BADUK_TABLE; j++) {
			if (bTable[i][j] != '+') {
				zeroCompare = false;
				break;
			}
		}
	}
	if (zeroCompare == false) {
		char cinput[100];

		//cin.clear();
		//cin.ignore(1000, '\n');

		while (true) {
			cout << "기존에 사용한 바둑판이 존재합니다. 초기화 하시겠습니까? [Y/N] : ";
			//cin.getline(cinput, 100);
			cin >> cinput;
			if (TextTest(cinput, "Y") == 0 || TextTest(cinput, "y") == 0) {
				MadeTabel(bTable);
				black = 0;
				white = 0;
				wbCompare = true;
				input1 = 0;
				input2 = 0;
				break;
			}
			else if (TextTest(cinput, "N") == 0 || TextTest(cinput, "n") == 0) {
				break;
			}
			else {
				cout << "잘못 입력하셨습니다." << endl;
			}
		}
		
	}
	while (true)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		PriTable(bTable);
		cout << "흑돌 : " << black << " 백돌 : " << white << endl;
		InputTest(input1, input2, wbCompare, bTable);
		BadukPri();
		if (input1 == 19 && input2 == 19) {
			system("cls");
			cout << "프로그램 종료" << endl << endl;
			break;
		}
	}
}

void PrintAllBaDuk() {
	cout << "----------가로줄 돌 개수-----------" << endl;
	for (int i = 0; i < BADUK_TABLE; i++) {
		int bcount = 0, wcount = 0;
		for (int j = 0; j < BADUK_TABLE; j++) {
			if (bTable[i][j] == 'O') {
				bcount++;
			}
			else if (bTable[i][j] == '@') {
				wcount++;
			}
		}
		cout << i << "번째 줄 흑 : " << bcount << " 백 : " << wcount;
		if (i == 18) {
			cout << endl;
		}
		else if (i % 2 == 0) {
			cout << '\t' << '\t';
		}
		else {
			cout << endl;
		}
	}
	cout << "------------세로줄 돌 개수------------" << endl;
	for (int i = 0; i < BADUK_TABLE; i++) {
		int bcount = 0, wcount = 0;
		for (int j = 0; j < BADUK_TABLE; j++) {
			if (bTable[j][i] == 'O') {
				bcount++;
			}
			else if (bTable[j][i] == '@') {
				wcount++;
			}
		}
		cout << i << "번째 줄 흑 : " << bcount << " 백 : " << wcount;
		if (i == 18) {
			cout << endl;
		}
		else if (i % 2 == 0) {
			cout << '\t' << '\t';
		}
		else {
			cout << endl;
		}
	}
}

void FindConsecutive() {
	int r_max_las = 0, t_max_las = 0, i_max_las = 0;
	int wr_max_las = 0, wt_max_las = 0, wi_max_las = 0;
	cout << "------------가로줄-------------" << endl;
	for (int i = 0; i < BADUK_TABLE; i++) {
		int bcount = 0, wcount = 0;
		int bmax = 0, wmax = 0;
		for (int j = 0; j < BADUK_TABLE; j++) {
			if (bTable[i][j] == 'O') {
				bcount++;
				if (bmax < bcount) {
					bmax = bcount;
					if (bmax > r_max_las) {
						t_max_las = j;
						i_max_las = i;
						r_max_las = bmax;
					}
				}
			}
			else {
				bcount = 0;
			}
			if (bTable[i][j] == '@') {
				wcount++;
				if (wmax < wcount) {
					wmax = wcount;
					if (bmax > wr_max_las) {
						wt_max_las = j;
						wi_max_las = i;
						wr_max_las = wmax;
					}
				}
			}
			else {
				wcount = 0;
			}
		}
		if (bmax == 0 && wmax == 0) {
			cout << i + 1 << "번째 가로 줄에는 돌이 없습니다." << endl;
			continue;
		}
		if (bmax > wmax) {
			cout << i+1 << "번째 가로 줄 가장 많이 연속된 돌 : 흑돌 | 개수 : " << bmax << endl;
		}
		else if (bmax < wmax) {
			cout << i+1 << "번째 가로 줄 가장 많이 연속된 돌 : 백돌 | 개수 : " << wmax << endl;
		}
		else if (bmax == wmax) {
			cout << i + 1 << "번째 가로 줄의 돌의 갯수가 동일합니다. 개수 : " << bmax << endl;
		}
	}
	cout << "----------------세로줄---------------" << endl;
	for (int i = 0; i < BADUK_TABLE; i++) {
		int bcount = 0, wcount = 0;
		int bmax = 0, wmax = 0;
		for (int j = 0; j < BADUK_TABLE; j++) {
			if (bTable[j][i] == 'O') {
				bcount++;
				if (bmax < bcount) {
					bmax = bcount;
				}
			}
			else {
				bcount = 0;
			}
			if (bTable[j][i] == '@') {
				wcount++;
				if (wmax < wcount) {
					wmax = wcount;
				}
			}
			else {
				wcount = 0;
			}
		}
		if (bmax == 0 && wmax == 0) {
			cout << i + 1 << "번째 세로 줄에는 돌이 없습니다." << endl;
			continue;
		}
		if (bmax > wmax) {
			cout << i + 1 << "번째 세로 줄 가장 많이 연속된 돌 : 흑돌 | 개수 : " << bmax << endl;
		}
		else if (bmax < wmax) {
			cout << i + 1 << "번째 세로 줄 가장 많이 연속된 돌 : 백돌 | 개수 : " << wmax << endl;
		}
		else if (bmax == wmax) {
			cout << i + 1 << "번째 세로 줄의 돌의 갯수가 동일합니다. 개수 : " << bmax << endl;
		}
	}
	cout << "가로 줄 중 가장 많이 연속된 돌의 위치" << endl;
	if (r_max_las > wr_max_las) {
		cout << "종류 : 흑돌 위치 : ";
		for (int i = r_max_las; i > 0; i--) {
			cout << "[ " <<  i_max_las << " , " << t_max_las - i + 1 << " ]" << '\t';
		}
		cout << endl;
	}
	else if (r_max_las < wr_max_las) {
		cout << "종류 : 백돌 위치 : ";
		for (int i = wr_max_las; i > 0; i--) {
			cout << "[ " << wi_max_las << " , " << wt_max_las - i + 1 << " ]" << '\t';
		}
		cout << endl;
	}
	else if (r_max_las == wr_max_las && r_max_las > 0) {
		cout << "종류 : 동일 위치(흑돌) : ";
		for (int i = r_max_las; i > 0; i--) {
			cout << "[ " << i_max_las << " , " << t_max_las - i + 1 << " ]" << '\t';
		}
		cout << endl;
		cout << "위치(백돌) : ";
		for (int i = wr_max_las; i > 0; i--) {
			cout << "[ " << wi_max_las << " , " << wt_max_las - i + 1 << " ]" << '\t';
		}
		cout << endl;
	}
}

void Diagonal() {
	PriTable(bTable);

	// ==========================================
	// 1. ↗ (우상향) 방향 검사
	// ==========================================
	for (int i = 0; i <= 2 * (BADUK_TABLE - 1); i++) {
		int bcount = 0, wcount = 0;
		int bmax = 0, wmax = 0;

		// 🌟 대각선 줄의 '검사 시작점' 좌표
		int inspect_r = -1, inspect_c = -1;

		for (int j = i; j >= 0; j--) {
			int c = i - j;
			// 바둑판 범위 안쪽일 때
			if (j < BADUK_TABLE && c < BADUK_TABLE) {

				// 🌟 이 대각선 줄에서 가장 처음 검사하는 유효한 칸의 좌표를 저장
				if (inspect_r == -1) {
					inspect_r = j;
					inspect_c = c;
				}

				// ⬛ 흑돌 체크
				if (bTable[j][c] == 'O') {
					bcount++;
					if (bmax < bcount) {
						bmax = bcount;
					}
				}
				else bcount = 0;

				// ⬜ 백돌 체크
				if (bTable[j][c] == '@') {
					wcount++;
					if (wmax < wcount) {
						wmax = wcount;
					}
				}
				else wcount = 0;
			}
		}

		if (bmax != 0 || wmax != 0) {
			if ((inspect_r == 0 && inspect_c == 0) || (inspect_r == 18 && inspect_c == 18)) {
				if (bmax > wmax) {
					cout << "방향 : ↗ 검사 위치 : [ " << inspect_r << " , " << inspect_c << " ] 연속된 돌 : 흑돌 개수 : " << bmax << endl;
				}
				else if (bmax < wmax) {
					cout << "방향 : ↗ 검사 위치 : [ " << inspect_r << " , " << inspect_c << " ] 연속된 돌 : 백돌 개수 : " << wmax << endl;
				}
			}
			if (bmax > wmax && bmax > 1) {
				cout << "방향 : ↗ 검사 위치 : [ " << inspect_r << " , " << inspect_c << " ] 연속된 돌 : 흑돌 개수 : " << bmax << endl;
			}
			else if (bmax < wmax && wmax > 1) {
				cout << "방향 : ↗ 검사 위치 : [ " << inspect_r << " , " << inspect_c << " ] 연속된 돌 : 백돌 개수 : " << wmax << endl;
			}
			else if (bmax == wmax && (bmax > 1 && wmax > 1)){
				cout << "방향 : ↗ 검사 위치 : [ " << inspect_r << " , " << inspect_c << " ] 연속된 돌 : 동일 개수 : " << bmax << endl;
			}
		}
	}

	// ==========================================
	// 2. ↘ (우하향) 방향 검사
	// ==========================================
	for (int i = 0; i <= 2 * (BADUK_TABLE - 1); i++) {
		int bcount = 0, wcount = 0;
		int bmax = 0, wmax = 0;

		// 🌟 대각선 줄의 '검사 시작점' 좌표
		int inspect_r = -1, inspect_c = -1;

		for (int j = 0; j <= i; j++) {
			int y = i - j;
			// 바둑판 범위 안쪽일 때
			if (j < BADUK_TABLE && y < BADUK_TABLE) {
				int rev_y = (BADUK_TABLE - 1) - y;

				// 🌟 이 대각선 줄에서 가장 처음 검사하는 유효한 칸의 좌표를 저장
				if (inspect_r == -1) {
					inspect_r = j;
					inspect_c = rev_y;
				}

				// ⬛ 흑돌 체크
				if (bTable[j][rev_y] == 'O') {
					bcount++;
					if (bmax < bcount){
						bmax = bcount;
					}
				}
				else bcount = 0;

				// ⬜ 백돌 체크
				if (bTable[j][rev_y] == '@') {
					wcount++;
					if (wmax < wcount) {
						wmax = wcount;
					}
				}
				else wcount = 0;
			}
		}

		if (bmax != 0 || wmax != 0) {
			if (bmax > wmax) {
				cout << "방향 : ↘ 검사 위치 : [ " << inspect_r << " , " << inspect_c << " ] 연속된 돌 : 흑돌 개수 : " << bmax << endl;
			}
			else if (bmax < wmax) {
				cout << "방향 : ↘ 검사 위치 : [ " << inspect_r << " , " << inspect_c << " ] 연속된 돌 : 백돌 개수 : " << wmax << endl;
			}
			else {
				cout << "방향 : ↘ 검사 위치 : [ " << inspect_r << " , " << inspect_c << " ] 연속된 돌 : 동일 개수 : " << bmax << endl;
			}
		}
	}
}

void Pri(int &input) {
	cout << "사용할 명령어의 번호를 입력하세요." << endl;
	cout << "0. 오목 두기" << endl;
	cout << "1. 가로 or 세로줄 돌 개수 확인" << endl;
	cout << "2. 가로 or 세로줄 연속된 돌 확인" << endl;
	cout << "3. 대각선줄 역속된 돌 확인" << endl;
	cout << "4. 프로그램 종료" << endl;
	cin >> input;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		input = -1;
	}
	system("cls");
}

void QueSw(int &input) {
	switch (input) {
		case 0:
			CaseZero();
			break;
		case 1:
			PrintAllBaDuk();
			break;
		case 2:
			FindConsecutive();
			break;
		case 3:
			Diagonal();
			break;
		case 4:
			system("cls");
			cout << "프로그램을 종료합니다.";
			progreamExit = true;
			break;
		default:
			cout << "잘못 입력하셨습니다. 번호(0~4)만 입력하세요." << endl << endl;
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