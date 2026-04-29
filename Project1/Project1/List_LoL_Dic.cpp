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

void Array2SLinkedList(charaterinfo arr[], int size) {
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
		else {
			tail->next = newNode;
			tail = newNode;
			tail->next = head;
		}
	}
}

void LoadDataFile() {
	ifstream file("testdata.txt");
	if (!file.is_open()) {
		cout << "파일을 열 수 없습니다." << endl;
		return;
	}
	char line[500];
	charaterinfo tempArray[100];
	int dataCount = 0;

	while (file.getline(line, 500) && dataCount < 100) {

		char* token = strtok(line, "\t");

		if (token != nullptr) {
			tempArray[dataCount].name = token;
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			tempArray[dataCount].hp = atoi(token);
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			tempArray[dataCount].mp = atoi(token);
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			tempArray[dataCount].speed = atoi(token);
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			tempArray[dataCount].range = atoi(token);
		}
		token = strtok(nullptr, "\t");
		if (token != nullptr) {
			tempArray[dataCount].position = token;
		}
		dataCount++;
	}
	file.close();
	Array2SLinkedList(tempArray, dataCount);
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

int InsertValue() {
	int value = 0;
	while (true) {
		cin >> value;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "정수만 입력하세요" << endl;
		}
		else {
			if (cin.get() != '\n') {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "정수만 입력하세요2" << endl;
				continue;
			}
			return value;
		}
	}
}

void ChampInsert() {
	system("cls");
	Node* insnode = new Node;
	Node* prev = tail;
	Node* curr = head;
	cout << "추가할 챔피언의 이름을 입력하세요 : ";
	bool inscompare = false;
	do {
		inscompare = false;
		cin.ignore(1000, '\n');
		getline(cin, insnode->info.name);
		do {
			if (head == nullptr) {
				inscompare = false;
				break;
			}
			if (insnode->info.name == curr->info.name) {
				cout << "리스트에 중복된 이름이 존재합니다. 다시 입력하세요 : ";
				curr = head;
				inscompare = true;
				break;
			}
			else {
				curr = curr->next;
			}
		} while (curr != head);
	} while (inscompare);
	cout << "HP : ";
	insnode->info.hp = InsertValue();
	cout << "MP : ";
	insnode->info.mp = InsertValue();
	cout << "Speed : ";
	insnode->info.speed = InsertValue();
	cout << "Range : ";
	insnode->info.range = InsertValue();
	cout << "Position : ";
	cin.clear();
	getline(cin, insnode->info.position);

	if (head == nullptr && tail == nullptr) {
		head = insnode;
		tail = insnode;
		insnode->next = head;
		cout << "삽입 완료!" << endl;
		return;
	}

	if (head->info.hp <= insnode->info.hp) {
		insnode->next = head;
		head = insnode;
		tail->next = head;
		cout << "삽입 완료!" << endl;
		return;
	}

	do {
		if (curr == tail && curr->info.hp >= insnode->info.hp) {
			curr->next = insnode;
			insnode->next = head;
			tail = insnode;
			cout << "삽입 완료1" << endl;
			return;
		}
		if (curr->info.hp <= insnode->info.hp) {
			insnode->next = curr;
			prev->next = insnode;
			cout << "삽입 완료 2" << endl;
			return;
		}
		else {
			prev = prev->next;
			curr = curr->next;
		}
	} while (curr != head);
	cout << "프로그램 오류" << endl;
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
	while (searchName == head->info.position) {
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
			count++;
			break;
		}
		Node* deletetarget = head;
		head = head->next;
		tail->next = head;
		delete deletetarget;
		cout << "삭제완료 2" << endl;
		count++;
	}
	if (head == nullptr) {
		if (count != 0) {
			cout << "삭제 완료." << endl;
		}
		else {
			cout << "찾는 챔피언이 리스트에 없습니다." << endl;
		}
		return;
	}
	Node* curr = head;
	Node* prev = tail;
	do {
		if (curr->info.position == searchName) {
			count++;
			if (curr == head && curr == tail) {
				head = nullptr;
				tail = nullptr;
				break;
			}
			else {
				Node* deletetarget = curr;
				curr = curr->next;
				prev->next = curr;
				if (deletetarget == head) {
					head = curr;
				}
				if (deletetarget == tail) {
					tail = prev;
				}
				delete deletetarget;
			}
		}
		else {
			prev = prev->next;
			curr = curr->next;
		}
	} while (curr != head && head != nullptr);
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

int FindHP(int max_hp, Node* startnode) {
	Node* curr = startnode;
	do {
		if (curr->info.hp > max_hp) {
			max_hp = curr->info.hp;
		}
		curr = curr->next;
	} while (curr != startnode);
	return max_hp;
}

void ChampFMH() {
	if (head == nullptr) {
		cout << "리스트에 챔피언이 없습니다!";
		return;
	}
	int max_hp = head->info.hp;
	Node* curr = head;
	max_hp = FindHP(max_hp, curr);
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
	if (head == nullptr || tail == head) {
		cout << "리스트에 챔피언이 너무 적거나 없습니다." << endl;
		return;
	}
	Node* sortedHead = nullptr;
	Node* sortedTail = nullptr;

	while (head != nullptr) {

		int max_hp = FindHP(head->info.hp, head);

		Node* maxNode = head;
		Node* maxPrev = tail; 

		while (maxNode->info.hp != max_hp) {
			maxPrev = maxNode;
			maxNode = maxNode->next;
		}

		if (maxNode == head && maxNode == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			maxPrev->next = maxNode->next; 

			if (maxNode == head) {
				head = maxNode->next; 
				tail->next = head;
			}
			else if (maxNode == tail) {
				tail = maxPrev;        
				tail->next = head;
			}
		}

		if (sortedHead == nullptr) {
			sortedHead = maxNode;
			sortedTail = maxNode;
			maxNode->next = sortedHead; 
		}
		else {
			sortedTail->next = maxNode;
			sortedTail = maxNode;
			sortedTail->next = sortedHead;
		}
	}

	head = sortedHead;
	tail = sortedTail;
	cout << "정렬 완료" << endl;
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