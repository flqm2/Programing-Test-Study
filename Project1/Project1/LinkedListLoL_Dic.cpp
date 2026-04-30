#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

bool programeExit = false;

struct Charatherinfo {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;

};

struct Node {
	Charatherinfo info;
	Node* next;
};

Node* head = nullptr;
Node* tail = nullptr;

void LinkedListData(Charatherinfo arr[], int size) {
	head = nullptr;
	tail = nullptr;

	for (int i = 0; i < size; i++) {
		Node* newNode = new Node;
		newNode->info = arr[i];

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			newNode->next = head;
		}

	}
}

void LoadDataFile() {
	ifstream file("testdata.txt");
	if (!file.is_open()) {
		cout << "파일을 열 수 없습니다." << endl;
		programeExit = true;
		return;
	}

	char line[500];
	Charatherinfo tempArray[100];
	int dataCount = 0;

	while (file.getline(line, 500) && dataCount < 100) {
		char* token = strtok(line, "\t");
		if (token != nullptr) tempArray[dataCount].name = token;
		token = strtok(nullptr, "\t");
		if (token != nullptr) tempArray[dataCount].hp = atoi(token);
		token = strtok(nullptr, "\t");
		if (token != nullptr) tempArray[dataCount].mp = atoi(token);
		token = strtok(nullptr, "\t");
		if (token != nullptr) tempArray[dataCount].speed = atoi(token);
		token = strtok(nullptr, "\t");
		if (token != nullptr) tempArray[dataCount].range = atoi(token);
		token = strtok(nullptr, "\t");
		if (token != nullptr) tempArray[dataCount].position = token;
		dataCount++;
	}
	file.close();
	LinkedListData(tempArray, dataCount);
	cout << "파일 로드 완료" << endl;
}

int main() {
	string;
}