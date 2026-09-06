#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

vector<string> fullData;

void Print() {
	for (int i = 0; i < fullData.size(); i++) {
		stringstream ss(fullData[i]);
		string word;
		bool frist = true;
		while (ss >> word) {
			if (!frist) cout << " ";
			cout << word;
			frist = false;
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
	Print();
}


void TurnLoRo(){
	string text;
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

void ChangeColor(bool compare) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	WORD originalAttributes = consoleInfo.wAttributes;

	int colorCount = 0;
	if (compare == false) {
		for (int i = 0; i < fullData.size(); i++) {
			stringstream ss(fullData[i]);
			string word;
			bool frist = true;
			while (ss >> word) {
				if (word[0] >= 'A' && word[0] <= 'Z') {
					SetConsoleTextAttribute(hConsole, 6);
					colorCount++;
				}
				if (!frist) cout << " ";
				cout << word;
				SetConsoleTextAttribute(hConsole, originalAttributes);
				frist = false;
			}
			cout << setw(5) << "단어 개수 : " << colorCount << endl;
			colorCount = 0;
		}
	}
	else {
		SetConsoleTextAttribute(hConsole, originalAttributes);
		Print();
	}
}

void BackWord(bool compare) {
	if (compare == true) {
		Print();
	}
	else {
		for (int i = 0; i < fullData.size(); i++) {
			int dataSize = fullData[i].size();
			for (int j = dataSize - 1; j >= 0; j--) {
				cout << fullData[i][j];
			}
			cout << endl;
		}
	}
}

void StarPrint(bool compare) {
	if (compare == true) {
		Print();
	}
	else {
		for (int i = 0; i < fullData.size(); i++) {
			stringstream ss(fullData[i]);
			string word;
			bool frist = true;
			while (ss >> word) {
				if (!frist) cout << "*";
				cout << word;
				frist = false;
			}
			cout << endl;
		}
	}
}

void ReverseWordOrder() {
	for (int i = 0; i < fullData.size(); i++) {
		stringstream ss(fullData[i]);
		vector<string> words;
		string word;
		while (ss >> word) {
			words.push_back(word); 
		}
		for (int j = words.size() - 1; j >= 0; j--) { 
			if (j != words.size() - 1) cout << " ";
			cout << words[j];
		}
		cout << endl;
	}
}

int main() {
	FileOpen();
	string input;
	bool compare = false;
	bool compare2 = false;
	bool compare3 = false;
	while (true) {
		cin >> input;
		if (input == "a") {
			system("cls");
			TurnLoRo();
			Print();
		}
		else if (input == "b") {
			PrintWord();
		}
		else if (input == "c") {
			system("cls");
			ChangeColor(compare);
			compare = !compare;
		}
		else if (input == "d") {
			system("cls");
			BackWord(compare3);
			compare3 = !compare3;
		}
		else if (input == "e") {
			system("cls");
			StarPrint(compare2);
			compare2 = !compare2;
		}
		else if (input == "f") {
			ReverseWordOrder();
		}
		else if (input == "q") {
			break;
		}

	}
	return 0;
}