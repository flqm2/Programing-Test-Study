#include <iostream>
#include <string>

using namespace std;

const int BADUK_TABLE = 19;

char bTable[BADUK_TABLE][BADUK_TABLE] = {};
int input1 = 0, input2 = 0, white = 0, black = 0;
bool wbCompare = true;
bool progreamExit = false;

struct Vector2 {
	int x;
	int y;
};

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
		string cinput;

		while (true) {
			cout << "기존에 사용한 바둑판이 존재합니다. 초기화 하시겠습니까? [Y/N] : ";
			getline(cin, cinput);
			if (cinput == "Y" || cinput == "y") {
				MadeTabel(bTable);
				black = 0;
				white = 0;
				wbCompare = true;
				input1 = 0;
				input2 = 0;
				break;
			}
			else if (cinput == "N" || cinput == "n") {
				break;
			}
			else {
				cout << "잘못 입력하셨습니다." << endl;
			}
		}

	}
	while (true) {
		PriTable(bTable);
		cout << "흑돌 : " << black << " 백돌 : " << white << endl;
		//InputTest(input1, input2, wbCompare, bTable);
		BadukPri();
		if (input1 == 19 && input2 == 19) {
			system("cls");
			cout << "프로그램 종료" << endl << endl;
			break;
		}
	}
}

Vector2 bstart_vec;
Vector2 blast_vec;
Vector2 wstart_vec;
Vector2 wlast_vec;

void FindConsecutive() {
	cout << "===============================가로 줄===============================" << endl;
	for (int i = 0; i < BADUK_TABLE; i++) {
		int bcount = 0, wcount = 0;
		int bmax = 0, wmax = 0;
		bool bjumpcount = false;
		bool wjumpcount = false;
		int b_current_start_y = -1;
		int w_current_start_y = -1;
		for (int j = 0; j < BADUK_TABLE; j++) {
			if (bTable[i][j] == 'O') {
				if (bcount == 0) {
					b_current_start_y = j;
				}
				bcount++;
				if (bmax < bcount) {
					bmax = bcount;
					bstart_vec.x = i;
					bstart_vec.y = b_current_start_y;
					blast_vec.x = i;
					blast_vec.y = j;
				}
				if (j + 1 < BADUK_TABLE) {
					if (bTable[i][j + 1] != 'O') {
						bjumpcount = true;
					}
				}
			}
			else {
				if (bjumpcount == true) {
					if (j+1 < BADUK_TABLE && bTable[i][j + 1] == 'O') bjumpcount = false;
					else {
						bcount = 0;
						bjumpcount = false;
					}
				}
				else {
					bcount = 0;
				}
			}
			if (bTable[i][j] == '@') {
				if (wcount == 0) {
					w_current_start_y = j;
				}
				wcount++;
				if (wmax < wcount) {
					wmax = wcount;
					wstart_vec.x = i;
					wstart_vec.y = w_current_start_y;
					wlast_vec.x = i;
					wlast_vec.y = j;
				}
				if (j + 1 < BADUK_TABLE) {
					if (bTable[i][j + 1] != '@') {
						wjumpcount = true;
					}
				}
			}
			else {
				if (wjumpcount == true) {
					if (j+1 < BADUK_TABLE && bTable[i][j + 1] == '@') wjumpcount = false;
					else {
						wcount = 0;
						wjumpcount = false;
					}
				}
				else {
					wcount = 0;
				}
			}
		}
		if (bmax == 0 && wmax == 0) {
			continue;
		}
		if (bmax > wmax) {
			cout << i + 1 << "번째 가로 줄 가장 많이 연속된 돌 : 흑돌 | 개수 : " << bmax << endl;
			cout << "좌표 : [ " << bstart_vec.x << " , " << bstart_vec.y << " ] ~ [ " << blast_vec.x << " , " << blast_vec.y << " ]" << endl;
		}
		else if (bmax < wmax) {
			cout << i + 1 << "번째 가로 줄 가장 많이 연속된 돌 : 백돌 | 개수 : " << wmax << endl;
			cout << "좌표 : [ " << wstart_vec.x << " , " << wstart_vec.y << " ] ~ [ " << wlast_vec.x << " , " << wlast_vec.y << " ]" << endl;
		}
		else if (bmax == wmax) {
			cout << i + 1 << "번째 가로 줄의 돌의 갯수가 동일합니다. 개수 : " << bmax << endl;
		}
	}
	cout << "=====================================================================" << endl;
	cout << "===============================세로 줄===============================" << endl;
	for (int i = 0; i < BADUK_TABLE; i++) {
		int bcount = 0, wcount = 0;
		int bmax = 0, wmax = 0;
		bool bjumpcount = false;
		bool wjumpcount = false;
		int b_current_start_x = -1;
		int w_current_start_x = -1;
		for (int j = 0; j < BADUK_TABLE; j++) {
			if (bTable[j][i] == 'O') {
				if (bcount == 0) {
					b_current_start_x = j;
				}
				bcount++;
				if (bmax < bcount) {
					bmax = bcount;
					bstart_vec.x = b_current_start_x;;
					bstart_vec.y = i;
					blast_vec.x = j;
					blast_vec.y = i;
				}
				if (j + 1 < BADUK_TABLE) {
					if (bTable[j + 1][i] != 'O') {
						bjumpcount = true;
					}
				}
			}
			else {
				if (bjumpcount == true) {
					if (j + 1 < BADUK_TABLE && bTable[j + 1][i] == 'O') bjumpcount = false;
					else {
						bcount = 0;
						bjumpcount = false;
					}
				}
				else {
					bcount = 0;
				}
			}
			if (bTable[j][i] == '@') {
				if (wcount == 0) {
					w_current_start_x = j;
				}
				wcount++;
				if (wmax < wcount) {
					wmax = wcount;
					wstart_vec.x = w_current_start_x;;
					wstart_vec.y = i;
					wlast_vec.x = j;
					wlast_vec.y = i;
				}
				if (j + 1 < BADUK_TABLE) {
					if (bTable[j + 1][i] != '@') {
						wjumpcount = true;
					}
				}
			}
			else {
				if (wjumpcount == true) {
					if (j + 1 < BADUK_TABLE && bTable[j + 1][i] == '@') wjumpcount = false;
					else {
						wcount = 0;
						wjumpcount = false;
					}
				}
				else {
					wcount = 0;
				}
			}
		}
		if (bmax == 0 && wmax == 0) {
			continue;
		}
		if (bmax > wmax) {
			cout << i + 1 << "번째 세로 줄 가장 많이 연속된 돌 : 흑돌 | 개수 : " << bmax << endl;
			cout << "좌표 : [ " << bstart_vec.x << " , " << bstart_vec.y << " ] ~ [ " << blast_vec.x << " , " << blast_vec.y << " ]" << endl;
		}
		else if (bmax < wmax) {
			cout << i + 1 << "번째 세로 줄 가장 많이 연속된 돌 : 백돌 | 개수 : " << wmax << endl;
			cout << "좌표 : [ " << wstart_vec.x << " , " << wstart_vec.y << " ] ~ [ " << wlast_vec.x << " , " << wlast_vec.y << " ]" << endl;
		}
		else if (bmax == wmax) {
			cout << i + 1 << "번째 세로 줄의 돌의 갯수가 동일합니다. 개수 : " << bmax << endl;
		}
	}
	cout << "=====================================================================" << endl;
}

void Diagonal() {
	// ==========================================
	// 1. ↗ (우상향) 방향 검사 (왼쪽 아래 -> 오른쪽 위)
	// ==========================================
	for (int i = 0; i <= 2 * (BADUK_TABLE - 1); i++) {
		int bcount = 0, wcount = 0;
		int bmax = 0, wmax = 0;
		bool bjumpcount = false, wjumpcount = false;

		// 흑/백 전용 좌표 변수
		int b_curr_start_r = -1, b_curr_start_c = -1;
		int b_start_r = -1, b_start_c = -1, b_last_r = -1, b_last_c = -1;

		int w_curr_start_r = -1, w_curr_start_c = -1;
		int w_start_r = -1, w_start_c = -1, w_last_r = -1, w_last_c = -1;

		for (int j = i; j >= 0; j--) {
			int c = i - j;
			if (j < BADUK_TABLE && c < BADUK_TABLE) {
				int r = j; // 행

				// 🌟 ↗ 방향의 다음 칸은 [행-1][열+1]
				int next_r = r - 1;
				int next_c = c + 1;
				bool has_next = (next_r >= 0 && next_c < BADUK_TABLE);

				// ⬛ 흑돌 검사 로직
				if (bTable[r][c] == 'O') {
					if (bcount == 0) { b_curr_start_r = r; b_curr_start_c = c; }
					bcount++;
					if (bmax < bcount) {
						bmax = bcount;
						b_start_r = b_curr_start_r; b_start_c = b_curr_start_c;
						b_last_r = r; b_last_c = c;
					}
					// 다음 칸이 빈칸이면 점프 장전
					if (has_next && bTable[next_r][next_c] == '+') bjumpcount = true;
				}
				else if (bTable[r][c] == '+') { // 빈칸일 때
					// 점프가 장전되어 있고, 그 다음 칸이 흑돌이면 무사 통과 (카운트 유지)
					if (bjumpcount == true && has_next && bTable[next_r][next_c] == 'O') {
						bjumpcount = false;
					}
					else { // 아니면 연속 끊김
						bcount = 0; bjumpcount = false;
					}
				}
				else { // 상대방 돌(@)을 만났을 때
					bcount = 0; bjumpcount = false;
				}

				// ⬜ 백돌 검사 로직
				if (bTable[r][c] == '@') {
					if (wcount == 0) { w_curr_start_r = r; w_curr_start_c = c; }
					wcount++;
					if (wmax < wcount) {
						wmax = wcount;
						w_start_r = w_curr_start_r; w_start_c = w_curr_start_c;
						w_last_r = r; w_last_c = c;
					}
					if (has_next && bTable[next_r][next_c] == '+') wjumpcount = true;
				}
				else if (bTable[r][c] == '+') {
					if (wjumpcount == true && has_next && bTable[next_r][next_c] == '@') {
						wjumpcount = false;
					}
					else {
						wcount = 0; wjumpcount = false;
					}
				}
				else { // 상대방 돌(O)을 만났을 때
					wcount = 0; wjumpcount = false;
				}
			}
		}

		// 출력
		if (bmax == 0 && wmax == 0) continue;

		if (bmax > wmax && bmax > 1) {
			cout << "방향 : ↗ 연속된 돌 : 흑돌 | 개수 : " << bmax << endl;
			cout << "좌표 : [ " << b_start_r << " , " << b_start_c << " ] ~ [ " << b_last_r << " , " << b_last_c << " ]" << endl;
		}
		else if (bmax < wmax && wmax > 1) {
			cout << "방향 : ↗ 연속된 돌 : 백돌 | 개수 : " << wmax << endl;
			cout << "좌표 : [ " << w_start_r << " , " << w_start_c << " ] ~ [ " << w_last_r << " , " << w_last_c << " ]" << endl;
		}
	}

	// ==========================================
	// 2. ↘ (우하향) 방향 검사 (왼쪽 위 -> 오른쪽 아래)
	// ==========================================
	for (int i = 0; i <= 2 * (BADUK_TABLE - 1); i++) {
		int bcount = 0, wcount = 0;
		int bmax = 0, wmax = 0;
		bool bjumpcount = false, wjumpcount = false;

		// 흑/백 전용 좌표 변수
		int b_curr_start_r = -1, b_curr_start_c = -1;
		int b_start_r = -1, b_start_c = -1, b_last_r = -1, b_last_c = -1;

		int w_curr_start_r = -1, w_curr_start_c = -1;
		int w_start_r = -1, w_start_c = -1, w_last_r = -1, w_last_c = -1;

		for (int j = 0; j <= i; j++) {
			int y = i - j;
			if (j < BADUK_TABLE && y < BADUK_TABLE) {
				int r = j;
				int c = (BADUK_TABLE - 1) - y;

				// 🌟 ↘ 방향의 다음 칸은 [행+1][열+1]
				int next_r = r + 1;
				int next_c = c + 1;
				bool has_next = (next_r < BADUK_TABLE && next_c < BADUK_TABLE);

				// ⬛ 흑돌 검사 로직
				if (bTable[r][c] == 'O') {
					if (bcount == 0) { b_curr_start_r = r; b_curr_start_c = c; }
					bcount++;
					if (bmax < bcount) {
						bmax = bcount;
						b_start_r = b_curr_start_r; b_start_c = b_curr_start_c;
						b_last_r = r; b_last_c = c;
					}
					if (has_next && bTable[next_r][next_c] == '+') bjumpcount = true;
				}
				else if (bTable[r][c] == '+') {
					if (bjumpcount == true && has_next && bTable[next_r][next_c] == 'O') {
						bjumpcount = false;
					}
					else {
						bcount = 0; bjumpcount = false;
					}
				}
				else {
					bcount = 0; bjumpcount = false;
				}

				// ⬜ 백돌 검사 로직
				if (bTable[r][c] == '@') {
					if (wcount == 0) { w_curr_start_r = r; w_curr_start_c = c; }
					wcount++;
					if (wmax < wcount) {
						wmax = wcount;
						w_start_r = w_curr_start_r; w_start_c = w_curr_start_c;
						w_last_r = r; w_last_c = c;
					}
					if (has_next && bTable[next_r][next_c] == '+') wjumpcount = true;
				}
				else if (bTable[r][c] == '+') {
					if (wjumpcount == true && has_next && bTable[next_r][next_c] == '@') {
						wjumpcount = false;
					}

					else {
						wcount = 0; wjumpcount = false;
					}
				}
				else {
					wcount = 0; wjumpcount = false;
				}
			}
		}

		// 출력
		if (bmax == 0 && wmax == 0) continue;

		if (bmax > wmax && bmax > 1) {
			cout << "방향 : ↘ 연속된 돌 : 흑돌 | 개수 : " << bmax << endl;
			cout << "좌표 : [ " << b_start_r << " , " << b_start_c << " ] ~ [ " << b_last_r << " , " << b_last_c << " ]" << endl;
		}
		else if (bmax < wmax && wmax > 1) {
			cout << "방향 : ↘ 연속된 돌 : 백돌 | 개수 : " << wmax << endl;
			cout << "좌표 : [ " << w_start_r << " , " << w_start_c << " ] ~ [ " << w_last_r << " , " << w_last_c << " ]" << endl;
		}
	}
}

Vector2 bcenter;
Vector2 wcenter;

void Defence() {
	bool defence_compare = false;
	if (wbCompare == true) {
		for (int i = 0; i < BADUK_TABLE; i++) {
			for (int j = 0; j < BADUK_TABLE; j++) {
				if (bTable[i][j] != '+') defence_compare = true;
			}
		}
		if (defence_compare) {
			cout << "=====================================================================" << endl;
			for (int i = 0; i < BADUK_TABLE; i++) {
				int wcount = 0;
				int wmax = 0;
				bool wjumpcount = false;
				int w_current_start_y = -1;

				bcenter.x = -1; bcenter.y = -1;
				wcenter.x = -1; wcenter.y = -1;

				for (int j = 0; j < BADUK_TABLE; j++) {
					int next_j = j + 1;
					bool has_next = (next_j < BADUK_TABLE);

					if (bTable[i][j] == '@') {
						if (wcount == 0) {
							w_current_start_y = j;
						}
						wcount++;
						if (wmax < wcount) {
							wmax = wcount;
							wstart_vec.x = i;
							wstart_vec.y = w_current_start_y;
							wlast_vec.x = i;
							wlast_vec.y = j;
						}
						if (has_next && bTable[i][next_j] == '+') {
							wjumpcount = true;
						}
					}
					else if (bTable[i][j] == '+') {
						if (wjumpcount == true && has_next && bTable[i][next_j] == '@') {
							wcenter.x = i;
							wcenter.y = j;
							wjumpcount = false;
						}
						else {
							wcount = 0;
							wjumpcount = false;
						}
					}
					else {
						wcount = 0;
						wjumpcount = false;
					}
				}
				if (wmax >= 3 && wmax <= 4) {
					cout << "백돌 공격! 돌 개수 : " << wmax << endl;
					cout << "방어 좌표 : ";

					bool isFirst = true;

					int left_y = wstart_vec.y - 1;
					if (left_y >= 0 && bTable[i][left_y] == '+') {
						if (!isFirst) cout << " , ";
						cout << "[ " << i << " , " << left_y << " ]";
						isFirst = false;
					}

					if (wcenter.x != -1 && wcenter.y != -1) {
						if (!isFirst) cout << " , ";
						cout << "[ " << wcenter.x << " , " << wcenter.y << " ]";
						isFirst = false;
					}

					int right_y = wlast_vec.y + 1;
					if (right_y < BADUK_TABLE && bTable[i][right_y] == '+') {
						if (!isFirst) cout << " , ";
						cout << "[ " << i << " , " << right_y << " ]";
						isFirst = false;
					}

					cout << endl;
				}
			}
			for (int i = 0; i < BADUK_TABLE; i++) {
				int wcount = 0;
				int wmax = 0;
				bool wjumpcount = false;
				int w_current_start_x = -1;

				bcenter.x = -1; bcenter.y = -1;
				wcenter.x = -1; wcenter.y = -1;

				for (int j = 0; j < BADUK_TABLE; j++) {
					int next_j = j + 1;
					bool has_next = (next_j < BADUK_TABLE);

					if (bTable[j][i] == '@') {
						if (wcount == 0) {
							w_current_start_x = j;
						}
						wcount++;
						if (wmax < wcount) {
							wmax = wcount;
							wstart_vec.x = w_current_start_x;
							wstart_vec.y = i;
							wlast_vec.x = j;
							wlast_vec.y = i;
						}
						if (has_next && bTable[next_j][i] == '+') {
							wjumpcount = true;
						}
					}
					else if (bTable[j][i] == '+') {
						if (wjumpcount == true && has_next && bTable[next_j][i] == '@') {
							wjumpcount = false;
							wcenter.x = j;
							wcenter.y = i;
						}
						else {
							wcount = 0;
							wjumpcount = false;
						}
					}
					else {
						wcount = 0;
						wjumpcount = false;
					}
				}
				if (wmax >= 3 && wmax <= 4) {
					cout << "백돌 공격! 돌 개수 : " << wmax << endl;
					cout << "방어 좌표 : ";

					bool isFirst = true;

					int top_x = wstart_vec.x - 1;
					if (top_x >= 0 && bTable[top_x][i] == '+') {
						if (!isFirst) cout << " , ";
						cout << "[ " << top_x << " , " << i << " ]";
						isFirst = false;
					}

					if (wcenter.x != -1 && wcenter.y != -1) {
						if (!isFirst) cout << " , ";
						cout << "[ " << wcenter.x << " , " << wcenter.y << " ]";
						isFirst = false;
					}

					int bottom_x = wlast_vec.x + 1;
					if (bottom_x < BADUK_TABLE && bTable[bottom_x][i] == '+') {
						if (!isFirst) cout << " , ";
						cout << "[ " << bottom_x << " , " << i << " ]";
						isFirst = false;
					}

					cout << endl;
				}
			}
		}
		for (int i = 0; i <= 2 * (BADUK_TABLE - 1); i++) {
			int wcount = 0, wmax = 0;
			bool wjumpcount = false;

			int w_curr_start_r = -1, w_curr_start_c = -1;
			int w_start_r = -1, w_start_c = -1, w_last_r = -1, w_last_c = -1;

			wcenter.x = -1; wcenter.y = -1;

			for (int j = i; j >= 0; j--) {
				int c = i - j;
				if (j < BADUK_TABLE && c < BADUK_TABLE) {
					int r = j;

					int next_r = r - 1;
					int next_c = c + 1;
					bool has_next = (next_r >= 0 && next_c < BADUK_TABLE);

					if (bTable[r][c] == '@') {
						if (wcount == 0) { w_curr_start_r = r; w_curr_start_c = c; }
						wcount++;
						if (wmax < wcount) {
							wmax = wcount;
							w_start_r = w_curr_start_r; w_start_c = w_curr_start_c;
							w_last_r = r; w_last_c = c;
						}
						if (has_next && bTable[next_r][next_c] == '+') wjumpcount = true;
					}
					else if (bTable[r][c] == '+') {
						if (wjumpcount == true && has_next && bTable[next_r][next_c] == '@') {
							wjumpcount = false;
							wcenter.x = r;
							wcenter.y = c;
						}
						else {
							wcount = 0; wjumpcount = false;
						}
					}
					else {
						wcount = 0; wjumpcount = false;
					}
				}
			}
			if (wmax >= 3 && wmax <= 4) {
				cout << "백돌 공격(↗)! 돌 개수 : " << wmax << endl;
				cout << "방어 좌표 : ";

				bool isFirst = true;

				int prev_r = w_start_r + 1;
				int prev_c = w_start_c - 1;
				if (prev_r < BADUK_TABLE && prev_c >= 0 && bTable[prev_r][prev_c] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << prev_r << " , " << prev_c << " ]";
					isFirst = false;
				}

				if (wcenter.x != -1 && wcenter.y != -1) {
					if (!isFirst) cout << " , ";
					cout << "[ " << wcenter.x << " , " << wcenter.y << " ]";
					isFirst = false;
				}

				int next_r = w_last_r - 1;
				int next_c = w_last_c + 1;
				if (next_r >= 0 && next_c < BADUK_TABLE && bTable[next_r][next_c] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << next_r << " , " << next_c << " ]";
					isFirst = false;
				}

				cout << endl;
			}
		}
		for (int i = 0; i <= 2 * (BADUK_TABLE - 1); i++) {
			int wcount = 0, wmax = 0;
			bool wjumpcount = false;

			int w_curr_start_r = -1, w_curr_start_c = -1;
			int w_start_r = -1, w_start_c = -1, w_last_r = -1, w_last_c = -1;

			wcenter.x = -1; wcenter.y = -1;

			for (int j = 0; j <= i; j++) {
				int y = i - j;
				if (j < BADUK_TABLE && y < BADUK_TABLE) {
					int r = j;
					int c = y;

					int next_r = r + 1;
					int next_c = c + 1;
					bool has_next = (next_r < BADUK_TABLE && next_c < BADUK_TABLE);

					if (bTable[r][c] == '@') {
						if (wcount == 0) { w_curr_start_r = r; w_curr_start_c = c; }
						wcount++;
						if (wmax < wcount) {
							wmax = wcount;
							w_start_r = w_curr_start_r; w_start_c = w_curr_start_c;
							w_last_r = r; w_last_c = c;
						}
						if (has_next && bTable[next_r][next_c] == '+') wjumpcount = true;
					}
					else if (bTable[r][c] == '+') {
						if (wjumpcount == true && has_next && bTable[next_r][next_c] == '@') {
							wjumpcount = false;
							wcenter.x = r;
							wcenter.y = c;
						}
						else {
							wcount = 0; wjumpcount = false;
						}
					}
					else {
						wcount = 0; wjumpcount = false;
					}
				}
			}
			if (wmax >= 3 && wmax <= 4) {
				cout << "백돌 공격(↘)! 돌 개수 : " << wmax << endl;
				cout << "방어 좌표 : ";

				bool isFirst = true;

				int prev_r = w_start_r - 1;
				int prev_c = w_start_c - 1;
				if (prev_r >= 0 && prev_c >= 0 && bTable[prev_r][prev_c] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << prev_r << " , " << prev_c << " ]";
					isFirst = false;
				}

				if (wcenter.x != -1 && wcenter.y != -1) {
					if (!isFirst) cout << " , ";
					cout << "[ " << wcenter.x << " , " << wcenter.y << " ]";
					isFirst = false;
				}

				int next_r = w_last_r + 1;
				int next_c = w_last_c + 1;
				if (next_r < BADUK_TABLE && next_c < BADUK_TABLE && bTable[next_r][next_c] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << next_r << " , " << next_c << " ]";
					isFirst = false;
				}

				cout << endl;
			}
		}
		cout << "=====================================================================" << endl;
	}
	else {
		cout << "=====================================================================" << endl;
		for (int i = 0; i < BADUK_TABLE; i++) {
			int bcount = 0;
			int bmax = 0;
			int b_current_start_y = -1;
			bool bjumpcount = false;

			bcenter.x = -1; bcenter.y = -1;
			wcenter.x = -1; wcenter.y = -1;

			for (int j = 0; j < BADUK_TABLE; j++) {
				int next_j = j + 1;
				bool has_next = (next_j < BADUK_TABLE);
				if (bTable[i][j] == 'O') {
					if (bcount == 0) {
						b_current_start_y = j;
					}
					bcount++;
					if (bmax < bcount) {
						bmax = bcount;
						bstart_vec.x = i;
						bstart_vec.y = b_current_start_y;
						blast_vec.x = i;
						blast_vec.y = j;
					}
					if (has_next && bTable[i][next_j] == '+') bjumpcount = true;
				}
				else if (bTable[i][j] == '+') {
					if (bjumpcount == true && has_next && bTable[i][next_j] == 'O') {
						bjumpcount = false;
						bcenter.x = i;
						bcenter.y = j;
					}
					else {
						bcount = 0;
						bjumpcount = false;
					}
				}
				else {
					bcount = 0;
					bjumpcount = false;
				}
			}
			if (bmax >= 3 && bmax <= 4) {
				cout << "흑돌 공격! 돌 개수 : " << bmax << endl;
				cout << "방어 좌표 : ";

				bool isFirst = true;

				int left_y = bstart_vec.y - 1;
				if (left_y >= 0 && bTable[i][left_y] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << i << " , " << left_y << " ]";
					isFirst = false;
				}

				if (bcenter.x != -1 && bcenter.y != -1) {
					if (!isFirst) cout << " , ";
					cout << "[ " << bcenter.x << " , " << bcenter.y << " ]";
					isFirst = false;
				}

				int right_y = blast_vec.y + 1;
				if (right_y < BADUK_TABLE && bTable[i][right_y] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << i << " , " << right_y << " ]";
					isFirst = false;
				}

				cout << endl;
			}
		}
		for (int i = 0; i < BADUK_TABLE; i++) {
			int bcount = 0;
			int bmax = 0;
			int b_current_start_x = -1;
			bool bjumpcount = false;

			bcenter.x = -1; bcenter.y = -1;
			wcenter.x = -1; wcenter.y = -1;

			for (int j = 0; j < BADUK_TABLE; j++) {
				int next_j = j + 1;
				bool has_next = (next_j < BADUK_TABLE);
				if (bTable[j][i] == 'O') {
					if (bcount == 0) {
						b_current_start_x = j;
					}
					bcount++;
					if (bmax < bcount) {
						bmax = bcount;
						bstart_vec.x = b_current_start_x;
						bstart_vec.y = i;
						blast_vec.x = j;
						blast_vec.y = i;
					}
					if (has_next && bTable[next_j][i] == '+') bjumpcount = true;
				}
				else if (bTable[j][i] == '+') {
					if (bjumpcount == true && has_next && bTable[next_j][i] == 'O') {
						bjumpcount = false;
						bcenter.x = j;
						bcenter.y = i;
					}
					else {
						bcount = 0;
						bjumpcount = false;
					}
				}
				else {
					bcount = 0;
					bjumpcount = false;
				}
			}
			if (bmax >= 3 && bmax <= 4) {
				cout << "흑돌 공격! 돌 개수 : " << bmax << endl;
				cout << "방어 좌표 : ";

				bool isFirst = true;

				int top_x = bstart_vec.x - 1;
				if (top_x >= 0 && bTable[top_x][i] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << top_x << " , " << i << " ]";
					isFirst = false;
				}

				if (bcenter.x != -1 && bcenter.y != -1) {
					if (!isFirst) cout << " , ";
					cout << "[ " << bcenter.x << " , " << bcenter.y << " ]";
					isFirst = false;
				}

				int bottom_x = blast_vec.x + 1;
				if (bottom_x < BADUK_TABLE && bTable[bottom_x][i] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << bottom_x << " , " << i << " ]";
					isFirst = false;
				}

				cout << endl;
			}
		}
		for (int i = 0; i <= 2 * (BADUK_TABLE - 1); i++) {
			int bcount = 0, bmax = 0;
			bool bjumpcount = false;

			int b_curr_start_r = -1, b_curr_start_c = -1;
			int b_start_r = -1, b_start_c = -1, b_last_r = -1, b_last_c = -1;

			bcenter.x = -1; bcenter.y = -1;

			for (int j = i; j >= 0; j--) {
				int c = i - j;
				if (j < BADUK_TABLE && c < BADUK_TABLE) {
					int r = j;

					int next_r = r - 1;
					int next_c = c + 1;
					bool has_next = (next_r >= 0 && next_c < BADUK_TABLE);

					if (bTable[r][c] == 'O') {
						if (bcount == 0) { b_curr_start_r = r; b_curr_start_c = c; }
						bcount++;
						if (bmax < bcount) {
							bmax = bcount;
							b_start_r = b_curr_start_r; b_start_c = b_curr_start_c;
							b_last_r = r; b_last_c = c;
						}
						if (has_next && bTable[next_r][next_c] == '+') bjumpcount = true;
					}
					else if (bTable[r][c] == '+') {
						if (bjumpcount == true && has_next && bTable[next_r][next_c] == 'O') {
							bjumpcount = false;
							bcenter.x = r;
							bcenter.y = c;
						}
						else {
							bcount = 0; bjumpcount = false;
						}
					}
					else {
						bcount = 0; bjumpcount = false;
					}
				}
			}

			if (bmax >= 3 && bmax <= 4) {
				cout << "흑돌 공격(↗)! 돌 개수 : " << bmax << endl;
				cout << "방어 좌표 : ";

				bool isFirst = true;

				int prev_r = b_start_r + 1;
				int prev_c = b_start_c - 1;
				if (prev_r < BADUK_TABLE && prev_c >= 0 && bTable[prev_r][prev_c] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << prev_r << " , " << prev_c << " ]";
					isFirst = false;
				}

				if (bcenter.x != -1 && bcenter.y != -1) {
					if (!isFirst) cout << " , ";
					cout << "[ " << bcenter.x << " , " << bcenter.y << " ]";
					isFirst = false;
				}

				int next_r = b_last_r - 1;
				int next_c = b_last_c + 1;
				if (next_r >= 0 && next_c < BADUK_TABLE && bTable[next_r][next_c] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << next_r << " , " << next_c << " ]";
					isFirst = false;
				}

				cout << endl;
			}
		}
		for (int i = 0; i <= 2 * (BADUK_TABLE - 1); i++) {
			int bcount = 0, bmax = 0;
			bool bjumpcount = false;

			int b_curr_start_r = -1, b_curr_start_c = -1;
			int b_start_r = -1, b_start_c = -1, b_last_r = -1, b_last_c = -1;

			bcenter.x = -1; bcenter.y = -1;

			for (int j = 0; j <= i; j++) {
				int y = i - j;
				if (j < BADUK_TABLE && y < BADUK_TABLE) {
					int r = j;
					int c = y;

					int next_r = r + 1;
					int next_c = c + 1;
					bool has_next = (next_r < BADUK_TABLE && next_c < BADUK_TABLE);

					if (bTable[r][c] == 'O') {
						if (bcount == 0) { b_curr_start_r = r; b_curr_start_c = c; }
						bcount++;
						if (bmax < bcount) {
							bmax = bcount;
							b_start_r = b_curr_start_r; b_start_c = b_curr_start_c;
							b_last_r = r; b_last_c = c;
						}
						if (has_next && bTable[next_r][next_c] == '+') bjumpcount = true;
					}
					else if (bTable[r][c] == '+') {
						if (bjumpcount == true && has_next && bTable[next_r][next_c] == 'O') {
							bjumpcount = false;
							bcenter.x = r;
							bcenter.y = c;
						}
						else {
							bcount = 0; bjumpcount = false;
						}
					}
					else {
						bcount = 0; bjumpcount = false;
					}
				}
			}

			if (bmax >= 3 && bmax <= 4) {
				cout << "흑돌 공격(↘)! 돌 개수 : " << bmax << endl;
				cout << "방어 좌표 : ";

				bool isFirst = true;

				int prev_r = b_start_r - 1;
				int prev_c = b_start_c - 1;
				if (prev_r >= 0 && prev_c >= 0 && bTable[prev_r][prev_c] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << prev_r << " , " << prev_c << " ]";
					isFirst = false;
				}

				if (bcenter.x != -1 && bcenter.y != -1) {
					if (!isFirst) cout << " , ";
					cout << "[ " << bcenter.x << " , " << bcenter.y << " ]";
					isFirst = false;
				}

				int next_r = b_last_r + 1;
				int next_c = b_last_c + 1;
				if (next_r < BADUK_TABLE && next_c < BADUK_TABLE && bTable[next_r][next_c] == '+') {
					if (!isFirst) cout << " , ";
					cout << "[ " << next_r << " , " << next_c << " ]";
					isFirst = false;
				}

				cout << endl;
			}
		}
		cout << "=====================================================================" << endl;
	}
}

void InputTest(int& h, int& w, bool& compare, char table[][BADUK_TABLE]) {
	PriTable(bTable);
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
		system("cls");
		progreamExit = true;
		cout << "프로그램 종료";
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
		FindConsecutive();
		Diagonal();
		Defence();
	}
	return;
}


int main() {
	int input = 0;
	MadeTabel(bTable);
	while (true) {
		if (progreamExit == true) return 0;
		InputTest(input1, input2, wbCompare, bTable);
	}
	return 0;
}