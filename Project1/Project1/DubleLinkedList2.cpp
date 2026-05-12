#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

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

	Node* next;
	Node* prev;
};

Node* head = nullptr;
Node* tail = nullptr;

bool programExit = false;

void Liset(CharahterInfo arr[], int size) {
	head = nullptr;
	tail = nullptr;
	for (int i = 0; i < size; i++) {
		Node* newNode = new Node;
		newNode->info = arr[i];

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			head->next = newNode;
			head->prev = tail;
			tail->next = head;
			tail->prev = newNode;
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
	fstream file("testdata.txt");
	if (!file.is_open()) {
		cout << "파일 로드 실패";
		programExit = true;
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
	Liset(tempArray, dataCount);
	cout << "파일 로드 완료" << endl;
}

void ChampSearch() {
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다." << endl;
		return;
	}

	string searchname;
	cout << "찾을 챔피언의 이름을 입력하세요 : ";
	getline(cin, searchname);
	Node* LP = head;

	do	{
		if (LP->info.name == searchname) {
			cout << "Name : " << LP->info.name << endl;
			cout << "HP : " << LP->info.hp << endl;
			cout << "MP : " << LP->info.mp << endl;
			cout << "Speed : " << LP->info.speed << endl;
			cout << "Range : " << LP->info.range << endl;
			cout << "Position : " << LP->info.position << endl;
			return;
		}
		else {
			LP = LP->next;
		}
	} while (LP != head);
	cout << "찾는 챔피언이 리스트에 없습니다.";
}

int IsnertValue() {
	int stat;
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
				cin.ignore(1000, '\n');
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

	do{
		namecompare = false;
		cout << "추가할 챔피언 이름 입력 : ";
		getline(cin, insnode->info.name);
		do {
			if (head == nullptr) break;
			if (LP->info.name == insnode->info.name) {
				cout << "동일한 이름의 챔피언이 존재합니다." << endl;
				namecompare = true;
				LP = head;
				break;
			}
			else {
				LP = LP->next;
			}
		} while (LP != head);

	} while (namecompare);
	cout << "HP : ";
	insnode->info.hp = IsnertValue();
	cout << "MP : ";
	insnode->info.mp = IsnertValue();
	cout << "Speed : ";
	insnode->info.speed = IsnertValue();
	cout << "Range : ";
	insnode->info.range = IsnertValue();
	cout << "Position : ";
	getline(cin, insnode->info.position);

	if (head == nullptr) {
		head = insnode;
		tail = insnode;
		head->next = insnode;
		head->prev = tail;
		tail->next = head;
		tail->prev = insnode;
		cout << "삽입 완료" << endl;
		return;
	}
	if (head->info.hp <= insnode->info.hp) {
		insnode->next = head;
		head->prev = insnode;
		head = insnode;
		head->prev = tail;
		tail->next = insnode;
		cout << "삽입 완료" << endl;
		return;
	}
	LP = head;
	do {
		if (LP->info.hp > insnode->info.hp && LP == tail) {
			tail->next = insnode;
			insnode->prev = tail;
			tail = insnode;
			tail->next = head;
			head->prev = tail;
			cout << "삽입 완료" << endl;
			return;
		}
		if (LP->info.hp <= insnode->info.hp) {
			insnode->next = LP;
			insnode->prev = LP->prev;
			LP->prev->next = insnode;
			LP->prev = insnode;
			cout << "삽입 완료" << endl;
			return;
		}
		else {
			LP = LP->next;
		}
	} while (LP != head);
}

void ChampDelete() {
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다." << endl;
		return;
	}
	cout << "삭제할 챔피언의 이름을 입력하세요 : ";
	string delname;
	getline(cin, delname);
	if (head == tail && head->info.name == delname) {
		delete head;
		head = nullptr;
		tail = nullptr;
		cout << "삭제 완료 리스트가 완전히 비었습니다." << endl;
		return;
	}
	if (head->info.name == delname) {
		Node* deletenode = head;
		head = head->next;
		head->prev = tail;
		tail->next = head;
		delete deletenode;
		cout << "삭제 완료." << endl;
		return;
	}
	Node* LP = head;
	do	{
		if (LP->info.name == delname && LP == tail) {
			Node* deletenode = tail;
			tail = tail->prev;
			tail->next = head;
			head->prev = tail;
			delete deletenode;
			cout << "삭제 완료." << endl;
			return;
		}
		if (LP->info.name == delname) {
			Node* deletenode = LP;
			LP->prev->next = LP->next;
			LP->next->prev = LP->prev;
			delete deletenode;
			cout << "삭제 완료." << endl;
			return;
		}
		else {
			LP = LP->next;
		}
	} while (LP != head);
	cout << "삭제할 챔피언이 리스트에 없습니다." << endl;
}

void ChampDeleteAll() {
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다." << endl;
		return;
	}
	cout << "삭제할 포지션을 입력하세요 : ";
	string delpos;
	int delcount = 0;
	getline(cin, delpos);
	if (head == tail && head->info.position == delpos) {
		delete head;
		head = nullptr;
		tail = nullptr;
		cout << "삭제 완료 리스트가 완전히 비었습니다." << endl;
		return;
	}
	while (head->info.position == delpos) {
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
			cout << "삭제 완료 리스트가 완전히 비었습니다." << endl;
			return;
		}
		Node* deletenode = head;
		head = head->next;
		head->prev = tail;
		tail->next = head;
		delete deletenode;
		delcount++;
	}
	Node* LP = head;
	do {
		if (LP->info.position == delpos && LP == tail) {
			Node* deletenode = tail;
			tail = tail->prev;
			tail->next = head;
			head->prev = tail;
			delete deletenode;
			cout << "삭제 완료." << endl;
			return;
		}
		if (LP->info.position == delpos) {
			Node* deletenode = LP;
			LP->prev->next = LP->next;
			LP->next->prev = LP->prev;

			LP = LP->next;
			delete deletenode;
			delcount++;
		}
		else {
			LP = LP->next;
		}
	} while (LP != head);
	if (delcount != 0) {
		cout << "삭제 완료" << endl;
	}
	else {
		cout << "삭제할 챔피언이 리스트에 없습니다." << endl;
	}
}

void ChampPrintAll() {
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다." << endl;
		return;
	}
	Node* LP = head;

	do {
		cout << LP->info.name << " , ";
		cout << LP->info.hp << " , ";
		cout << LP->info.mp << " , ";
		cout << LP->info.speed << " , ";
		cout << LP->info.range << " , ";
		cout << LP->info.position << endl;
		LP = LP->next;
	} while (LP != head);
}

int FindHP(Node* startednode, int max_hp) {
	Node* LP = startednode;
	do 	{
		if (max_hp < LP->info.hp) {
			max_hp = LP->info.hp;
		}
		LP = LP->next;
	} while (LP != head);
	return max_hp;
}

void ChampFMH() {
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다." << endl;
		return;
	}

	int max_hp = head->info.hp;
	Node* LP = head;
	max_hp = FindHP(LP, max_hp);

	LP = head;
	do	{
		if (LP->info.hp == max_hp) {
			cout << "Name : " << LP->info.name << endl;
			cout << "HP : " << LP->info.hp << endl;
			cout << "MP : " << LP->info.mp << endl;
			cout << "Speed : " << LP->info.speed << endl;
			cout << "Range : " << LP->info.range << endl;
			cout << "Position : " << LP->info.position << endl;
			cout << "========================================" << endl;
		}
		LP = LP->next;
	} while (LP != head);
}

void ChampSBH() {
	if (head == nullptr || head == tail) {
		cout << "리스트에 챔피언이 없거나 적습니다." << endl;
		return;
	}
	Node* sortedhead = nullptr;
	Node* sortedtail = nullptr;

	while (head != nullptr) {
		Node* LP = head;
		int max_hp = head->info.hp;

		max_hp = FindHP(LP, max_hp);
		
		while (LP->info.hp != max_hp) {
			LP = LP->next;
		}

		if (LP == head && LP == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			LP->prev->next = LP->next;
			LP->next->prev = LP->prev;

			if (LP == head) {
				head = head->next;
				head->prev = tail;
				tail->next = head;
			}
			if (LP == tail) {
				tail = tail->prev;
				tail->next = head;
				head->prev = tail;
			}
		}
		if (sortedhead == nullptr) {
			sortedhead = LP;
			sortedtail = LP;
			sortedhead->next = LP;
			sortedtail->prev = LP;
			sortedhead->prev = sortedtail;
			sortedtail->next = sortedhead;
		}
		else {
			sortedtail->next = LP;
			LP->prev = sortedtail;
			sortedtail = LP;
			sortedtail->next = sortedhead;
			sortedhead->prev = sortedtail;
		}
	}
	head = sortedhead;
	tail = sortedtail;
	cout << "정렬 완료";
}

void ListNumber(string input) {
	cout << "사용할 명령어를 입력하세요 종료는 'end' 입력 : ";
	getline(cin, input);
	if (input == "Search") ChampSearch();
	else if (input == "Insert") ChampInsert();
	else if (input == "Delete") ChampDelete();
	else if (input == "DeleteAll") ChampDeleteAll();
	else if (input == "PrintAll") ChampPrintAll();
	else if (input == "FindMaxHP") ChampFMH();
	else if (input == "SortByHp") ChampSBH();
	else if (input == "end") {
		programExit = true;
		cout << "프로그램 종료";
		return;
	}
	else {
		cout << "잘못 입력하셨습니다.";
	}
}

int main() {
	string input;
	LoadDataFile();
	while (true) {
		if (programExit == true) return 0;
		ListNumber(input);
	}
	return 0;
}