#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <cctype>
#include <algorithm>

using namespace std;

vector<string> fullData;
vector<string> originalDataH;

bool colorOn = false;
bool backwardOn = false;
bool starOn = false;
bool reverseWordOn = false;
bool compareH = false;

void UnifiedPrint() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD originalAttributes = consoleInfo.wAttributes;

	for (int i = 0; i < fullData.size(); i++) {
		stringstream ss(fullData[i]);
		vector<string> words;
		string word;
		while (ss >> word) {
			words.push_back(word);
		}

		if (reverseWordOn) {
			vector<string> reversed;
			for (int j = words.size() - 1; j >= 0; j--) {
				reversed.push_back(words[j]);
			}
			words = reversed;
		}

		int colorCount = 0;
		for (int j = 0; j < words.size(); j++) {
			if (j != 0) {
				cout << (starOn ? "*" : " ");
			}

			string outputWord = words[j];
			if (backwardOn) {
				reverse(outputWord.begin(), outputWord.end());
			}
			bool isUpperStart = outputWord[0] >= 'A' && outputWord[0] <= 'Z';
			if (colorOn && isUpperStart) {
				SetConsoleTextAttribute(hConsole, 6);
				colorCount++;
			}
			
			cout << outputWord;
			SetConsoleTextAttribute(hConsole, originalAttributes);
		}

		if (colorOn) {
			cout << setw(5) << "단어 개수 : " << colorCount;
		}
		cout << endl;
	}
}

void FileOpen() {
	string filename;
	cout << "불러올 파일 이름을 입력하세요 (ex : data.txt) : ";
	cin >> filename;
	fstream file(filename);
	if (!file.is_open()) {
		cout << "존재하지 않는 파일이거나 파일을 불러올 수 없습니다." << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		fullData.push_back(line);
	}
	cout << fullData.size() << "개의 문장 저장" << endl;
	UnifiedPrint();
}

void TurnLoRo() {
	for (int i = 0; i < fullData.size(); i++) {
		for (int j = 0; j < fullData[i].size(); j++) {
			if (fullData[i][j] >= 65 && fullData[i][j] <= 90) {
				fullData[i][j] += 32;
			}
			else if (fullData[i][j] >= 97 && fullData[i][j] <= 122) {
				fullData[i][j] -= 32;
			}
		}
	}
}

void PrintWord() {
	int wordCount = 0;
	for (int i = 0; i < fullData.size(); i++) {
		stringstream ss(fullData[i]);
		string word;
		bool frist = true;
		while (ss >> word) {
			if (!frist) cout << " ";
			cout << word;
			wordCount++;
			frist = false;
		}
		cout << setw(5) << "단어 개수 : " << wordCount << endl;
		wordCount = 0;
	}
}

void ReplaceChar() {
	char from, to;
	cout << "바꿀 문자를 입력하세요: ";
	cin >> from;
	cout << "새로 입력할 문자를 입력하세요: ";
	cin >> to;

	for (int i = 0; i < fullData.size(); i++) {
		for (int j = 0; j < fullData[i].size(); j++) {
			if (fullData[i][j] == from) {
				fullData[i][j] = to;
			}
		}
	}
	UnifiedPrint();
}

void SplitAtDigit(bool apply) {
	if (apply) {
		originalDataH = fullData;
		vector<string> newData;
		for (int i = 0; i < fullData.size(); i++) {
			string current = "";
			for (int j = 0; j < fullData[i].size(); j++) {
				current += fullData[i][j];
				if (isdigit(fullData[i][j])) {
					newData.push_back(current);
					current = "";
				}
			}
			if (!current.empty()) {
				newData.push_back(current);
			}
		}
		fullData = newData;
	}
	else {
		fullData = originalDataH;
	}
	UnifiedPrint();
}

void SearchWord() {
	string target;
	cout << "찾을 단어를 입력하세요: ";
	cin >> target;

	string lowerTarget = target;
	for (int k = 0; k < lowerTarget.size(); k++) {
		lowerTarget[k] = tolower(lowerTarget[k]);
	}

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD originalAttributes = consoleInfo.wAttributes;

	int count = 0;
	for (int i = 0; i < fullData.size(); i++) {
		stringstream ss(fullData[i]);
		string word;
		bool frist = true;
		while (ss >> word) {
			if (!frist) cout << " ";

			string lowerWord = word;
			for (int k = 0; k < lowerWord.size(); k++) {
				lowerWord[k] = tolower(lowerWord[k]);
			}

			if (lowerWord == lowerTarget) {
				SetConsoleTextAttribute(hConsole, 6);
				cout << word;
				SetConsoleTextAttribute(hConsole, originalAttributes);
				count++;
			}
			else {
				cout << word;
			}
			frist = false;
		}
		cout << endl;
	}
	cout << "찾은 단어 개수 : " << count << endl;
}

void RotateSentences() {
	int n = fullData.size();
	vector<string> newData(n);
	for (int i = 0; i < n; i++) {
		newData[(i + 1) % n] = fullData[i];
	}
	fullData = newData;
	UnifiedPrint();
}

int main() {
	FileOpen();
	string input;

	while (true) {
		cin >> input;
		if (input == "a") {
			system("cls");
			TurnLoRo();
			UnifiedPrint();
		}
		else if (input == "b") {
			PrintWord();
		}
		else if (input == "c") {
			system("cls");
			colorOn = !colorOn;
			UnifiedPrint();
		}
		else if (input == "d") {
			system("cls");
			backwardOn = !backwardOn;
			UnifiedPrint();
		}
		else if (input == "e") {
			system("cls");
			starOn = !starOn;
			UnifiedPrint();
		}
		else if (input == "f") {
			system("cls");
			reverseWordOn = !reverseWordOn;
			UnifiedPrint();
		}
		else if (input == "g") {
			system("cls");
			ReplaceChar();
		}
		else if (input == "h") {
			system("cls");
			compareH = !compareH;
			SplitAtDigit(compareH);
		}
		else if (input == "i") {
			system("cls");
			SearchWord();
		}
		else if (input == "j") {
			system("cls");
			RotateSentences();
		}
		else if (input == "q") {
			break;
		}
	}
	return 0;
}