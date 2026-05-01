#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

struct CharahterInfo {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};

struct Node {
	CharahterInfo info;

	Node* prev;
	Node* next;
};

Node* head = nullptr;
Node* tail = nullptr;

void ArrayS2LinkedList(CharahterInfo arr[], int size) {
	head = nullptr;
	tail = nullptr;

	for (int i = 0; i < size; i++) {
		Node* newNode = new Node;
		newNode->info = arr[i];

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			head->prev = tail;
			head->next = tail;
			tail->next = head;
			tail->prev = head;
		}
		else {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
			tail->next = head;
			head->prev = tail;
		}
	}
}

void LoadDataFile() {
	ifstream file("testdata.txt");
	if (!file.is_open()) {
		cout << "파일을 열 수 없습니다.";
		return;
	}

	char line[500];
	CharahterInfo tempArray[100];
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
	ArrayS2LinkedList(tempArray, dataCount);
	cout << "파일 연동 완료";
}

void ChampSearch() {
	if (head == nullptr) return;
	string searchname;
	cout << "찾을 챔피언 : ";
	cin.ignore(1000, '\n');
	getline(cin, searchname);
	Node* curr = head;
	do {
		if (curr->info.name == searchname) {
			cout << "Name : " << curr->info.name << endl;
			cout << "HP : " << curr->info.hp << endl;
			cout << "MP : " << curr->info.mp << endl;
			cout << "Speed : " << curr->info.speed << endl;
			cout << "Range : " << curr->info.range << endl;
			cout << "Position : " << curr->info.position << endl;
			return;
		}
		else {
			curr = curr->next;
		}
	} while (curr != head);
}

int InsertValue() {
	int stat = 0;
	while (true) {
		cin >> stat;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "정수만 입력 : ";
		}
		else {
			if (cin.get() != '\n') {
				cin.clear();
				cin.ignore();
				cout << "정수만 입력 : ";
				continue;
			}
			return stat;
		}
	}
}

void ChampInsert() {
	Node* insnode = new Node;
	Node* LP = head;
	bool namecompare = false;
	do {
		namecompare = false;
		cout << "추가할 챔피언 이름 : ";
		getline(cin, insnode->info.name);
		do {
			if (head == nullptr) {
				break;
			}
			if (insnode->info.name == LP->info.name) {
				cout << "동일한 이름의 챔피언 존재" << endl;
				namecompare = true;
				LP = head;
			}
			else {
				LP = LP->next;
			}
		} while (LP != head);
	} while (namecompare);
	cout << "HP : ";
	insnode->info.hp = InsertValue();
	cout << "MP : ";
	insnode->info.mp = InsertValue();
	cout << "Speed : ";
	insnode->info.speed = InsertValue();
	cout << "Range : ";
	insnode->info.range = InsertValue();
	cout << "Position : ";
	getline(cin, insnode->info.position);

	if (head == nullptr) {
		head = insnode;
		tail = insnode;
		head->next = insnode;
		head->prev = tail;
		tail->next = head;
		tail->prev = insnode;
		return;
	}
	if (head->info.hp <= insnode->info.hp) {
		insnode->next = head;
		head->prev = insnode;
		head = insnode;
		head->prev = tail;
		tail->next = head;
		return;
	}
	LP = head;
	do {
		if (LP == tail && LP->info.hp > insnode->info.hp) {
			insnode->prev = tail;
			tail->next = insnode;
			tail = insnode;
			head->prev = tail;
			tail->next = head;
			return;
		}
		if (LP->info.hp <= insnode->info.hp) {
			LP->prev->next = insnode;
			insnode->prev = LP->prev;
			insnode->next = LP;
			LP->prev = insnode;
			return;
		}
		else {
			LP = LP->next;
		}
	} while (LP != head);
}

void ChampPrintAll() {
	Node* curr = head;
	do {
		cout << curr->info.name << ", ";
		cout << curr->info.hp << ", ";
		cout << curr->info.mp << ", ";
		cout << curr->info.speed << ", ";
		cout << curr->info.range << ", ";
		cout << curr->info.position << endl;
		curr = curr->next;
	} while (curr != head);
}

int main() {
	LoadDataFile();
	while (true) {
		int a = 0;
		cin >> a;
		switch (a) {
		case 1:
			ChampSearch();
			break;
		case 2:
			ChampPrintAll();
		}

	}
	return 0;
}