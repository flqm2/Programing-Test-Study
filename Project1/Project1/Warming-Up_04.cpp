#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <Windows.h>

using namespace std;

int rows, cols;
char board[6][6];
bool revealed[6][6];
int score = 0;
int tries = 0;

void PrintBoard(int tr1 = -1, int tc1 = -1, int tr2 = -1, int tc2 = -1, bool showAll = false) {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD original = consoleInfo.wAttributes;

    cout << endl << "    ";
    for (int c = 0; c < cols; c++) {
        cout << (char)('a' + c) << " ";
    }
    cout << endl << endl;

    for (int r = 0; r < rows; r++) {
        cout << r + 1 << "   ";
        for (int c = 0; c < cols; c++) {
            bool isTarget = (r == tr1 && c == tc1) || (r == tr2 && c == tc2);

            if (showAll || revealed[r][c] || isTarget) {
                char disp = board[r][c];

                if ((disp >= 'A' && disp <= 'Z') || disp == '@') {
                    SetConsoleTextAttribute(hConsole, 6);
                }

                cout << disp << " ";
                SetConsoleTextAttribute(hConsole, original);
            }
            else {
                cout << "* ";
            }
        }
        cout << endl;
    }
    cout << endl << "진행 횟수: " << tries << " | 점수: " << score << endl;
    cout << "입력 방식 : a1 b3" << endl;
}

void InitGame() {
    bool validInput = false;
    while (!validInput) {
        cin >> rows >> cols;
        if (rows >= 3 && rows <= 6 && cols >= 3 && cols <= 6) {
            validInput = true;
        }
    }

    vector<char> cards;
    int total = rows * cols;
    int pairs = total / 2;
    char current = 'a';

    for (int i = 0; i < pairs; i++) {
        cards.push_back(current);
        cards.push_back(current);
        current++;
    }
    if (total % 2 != 0) {
        cards.push_back('@');
    }

    random_device rd;
    mt19937 gen(rd());
    for (int i = cards.size() - 1; i > 0; i--) {
        uniform_int_distribution<int> dist(0, i);
        int j = dist(gen);
        char temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }

    int k = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            board[r][c] = cards[k++];
            revealed[r][c] = false;
        }
    }
    score = 0;
    tries = 0;
}

int main() {
    cout << "보드의 크기를 정해주세요 (ex : 3 3, 2 4) : ";
    InitGame();
    PrintBoard();
    string input;

    while (true) {
        cin >> input;

        if (input == "q") {
            break;
        }
        else if (input == "r") {
            InitGame();
            PrintBoard();
        }
        else if (input == "h") {
            PrintBoard(-1, -1, -1, -1, true);
            Sleep(2000);
            PrintBoard();
        }
        else {
            string input2;
            cin >> input2;

            int c1 = input[0] - 'a';
            int r1 = input[1] - '1';
            int c2 = input2[0] - 'a';
            int r2 = input2[1] - '1';

            if (r1 < 0 || r1 >= rows || c1 < 0 || c1 >= cols ||
                r2 < 0 || r2 >= rows || c2 < 0 || c2 >= cols ||
                (r1 == r2 && c1 == c2) ||
                revealed[r1][c1] || revealed[r2][c2]) {
                continue;
            }

            tries++;
            PrintBoard(r1, c1, r2, c2);
            Sleep(1500);

            char char1 = board[r1][c1];
            char char2 = board[r2][c2];

            bool hasJoker = (char1 == '@' || char2 == '@');

            if (hasJoker) {
                // 조커가 아닌 선택 카드의 문양
                char target = (char1 == '@') ? char2 : char1;

                // 보드 안의 같은 문양 카드 2장을 모두 활성화
                for (int r = 0; r < rows; r++) {
                    for (int c = 0; c < cols; c++) {
                        if (board[r][c] == target) {
                            revealed[r][c] = true;

                            if (board[r][c] >= 'a' && board[r][c] <= 'z') {
                                board[r][c] -= 32;
                            }
                        }
                    }
                }

                // 조커도 활성화
                if (char1 == '@') {
                    revealed[r1][c1] = true;
                }
                else {
                    revealed[r2][c2] = true;
                }

                score += 10;
            }
            else if (char1 == char2) {
                revealed[r1][c1] = true;
                revealed[r2][c2] = true;

                if (board[r1][c1] >= 'a' && board[r1][c1] <= 'z')
                    board[r1][c1] -= 32;

                if (board[r2][c2] >= 'a' && board[r2][c2] <= 'z')
                    board[r2][c2] -= 32;

                score += 10;
            }
            else {
                score -= 2;
                if (score < 0) score = 0;
            }
            PrintBoard();
        }
    }
    return 0;
}