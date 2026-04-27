#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

struct charaterinfo {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};

struct Node {
	charaterinfo info;
	Node* next;
};

Node* head = nullptr;
Node* tail = nullptr;

void LoadDataFile() {
	ifstream file("testdata.txt");
	if (!file.is_open()) {
		cout << "파일을 열 수 없습니다." << endl;
		return;
	}
	char line[500];

	while (file.getline(line, 500)) {
		Node* newNode = new Node;

		char* token = strtok(line, "\t");

		if (token != nullptr) {
			newNode->info.name = token;
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			newNode->info.hp = atoi(token);
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			newNode->info.mp = atoi(token);
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			newNode->info.speed = atoi(token);
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			newNode->info.range = atoi(token);
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			newNode->info.position = token;
		}

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			newNode->next = head;
		}
		else {
			tail->next = newNode;
			tail = newNode;
			tail->next = head;
		}
	}
	file.close();
	cout << "데이터 로드 완료" << endl;
}

void ChampSearch() {
	system("cls");
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다!";
		return;
	}
	string searchName;
	Node* curr = head;
	cout << "찾을 챔피언의 이름을 입력하세요 : ";
	cin.ignore(1000, '\n');
	getline(cin, searchName);
	do {
		if (searchName == curr->info.name) {
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
	cout << "찾는 챔피언이 리스트에 없습니다." << endl;
}

void ChampInsert() {

}

void ChampDelete() {
	system("cls");
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다!";
		return;
	}
	string searchName;
	cout << "삭제할 챔피언의 이름을 입력하세요 : ";
	cin.ignore(1000, '\n');
	getline(cin, searchName);
	if (searchName == head->info.name && tail == head) {
		delete head;
		head = nullptr;
		tail = nullptr;
		cout << "삭제완료 1" << endl;
		return;
	}
	if (searchName == head->info.name) {
		Node* deletetarget = head;
		head = head->next;
		tail->next = head;
		delete deletetarget;
		cout << "삭제완료 2" << endl;
		return;
	}
	Node* curr = head;
	do {
		if (searchName == curr->next->info.name) {
			Node* deletetarget = curr->next;
			if (deletetarget == tail) {
				tail = curr;
			}
			curr->next = curr->next->next;

			delete deletetarget;
			cout << "삭제완료 3" << endl;
			return;
		}
		else {
			curr = curr->next;
		}
	} while (curr != head);
	cout << "찾는 챔피언이 리스트에 없습니다." << endl;
}

void ChampDeleteAll() {
	system("cls");
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다!";
		return;
	}
	string searchName;
	int count = 0;
	cout << "삭제할 포지션을 입력하세요 : ";
	cin.ignore(1000, '\n');
	getline(cin, searchName);
	if (searchName == head->info.position && tail == head) {
		delete head;
		head = nullptr;
		tail = nullptr;
		cout << "삭제완료 1" << endl;
		return;
	}
	if (searchName == head->info.position) {
		Node* deletetarget = head;
		head = head->next;
		tail->next = head;
		delete deletetarget;
		cout << "삭제완료 2" << endl;
		count++;
	}
	Node* curr = head;
	do {
		if (searchName == curr->next->info.position) {
			Node* deletetarget = curr->next;
			if (deletetarget == tail) {
				tail = curr;
			}
			curr->next = curr->next->next;

			delete deletetarget;
			count++;
		}
		else {
			curr = curr->next;
		}
	} while (curr != head);
	if (count != 0) {
		cout << "삭제 완료." << endl;
	}
	else {
		cout << "찾는 챔피언이 리스트에 없습니다." << endl;
	}
}

void ChampPrintAll() {
	system("cls");
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다!";
		return;
	}
	Node* curr = head;
	do {
		cout << curr->info.name << " , ";
		cout << curr->info.hp << " , ";
		cout << curr->info.mp << " , ";
		cout << curr->info.speed << " , ";
		cout << curr->info.range << " , ";
		cout << curr->info.position << endl;
		curr = curr->next;
	} while (curr != head);
}

void ChampFMH() {
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다!";
		return;
	}
	int max_hp = head->info.hp;
	Node* curr = head;
	do {
		if (curr->info.hp > max_hp) {
			max_hp = curr->info.hp;
		}
		else {
			curr = curr->next;
		}
	} while (curr != head);
	curr = head;
	do {
		if (curr->info.hp == max_hp) {
			cout << "Name : " << curr->info.name << endl;
			cout << "HP : " << curr->info.hp << endl;
			cout << "MP : " << curr->info.mp << endl;
			cout << "Speed : " << curr->info.speed << endl;
			cout << "Range : " << curr->info.range << endl;
			cout << "Position : " << curr->info.position << endl;
			cout << "========================================" << endl;
		}
		curr = curr->next;
	} while (curr != head);
}

void ChampSBH() {

}

void SeleteNumber(string input) {
	while (true) {
		cout << "사용할 명령어를 입력하세요 종료는 'end' 입력. : ";
		cin >> input;
		if (input == "Search") {
			ChampSearch();
		}
		else if (input == "Insert") {
			ChampInsert();
		}
		else if (input == "Delete") {
			ChampDelete();
		}
		else if (input == "DeleteAll") {
			ChampDeleteAll();
		}
		else if (input == "PrintAll") {
			ChampPrintAll();
		}
		else if (input == "FindMaxHp") {
			ChampFMH();
		}
		else if (input == "SortByHp") {
			ChampSBH();
		}
		else if (input == "end") {
			cout << "end" << endl;
			return;
		}
		else {
			cout << "잘못 입력했습니다. 다시 입력하세요" << endl;
			continue;
		}
		
	}
}

int main() {
	string input;

	LoadDataFile();
	SeleteNumber(input);
}