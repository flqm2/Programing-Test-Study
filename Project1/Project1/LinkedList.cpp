#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

bool programExit = false;

struct charahterinfo{
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};

struct Node{
	charahterinfo info;
	Node* next;
};

Node* head = nullptr;
Node* tail = nullptr;

void Array2LinkedList(charahterinfo arr[], int size) {
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
			newNode->next = head;
		}
	}
}

void LoadDataFile() {
	ifstream file("testdata.txt");
	if (!file.is_open()) {
		cout << "파일을 열 수 없습니다." << endl;
		programExit = true;
		return;
	}

	char line[500];
	charahterinfo tempArray[100];
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
	Array2LinkedList(tempArray, dataCount);
	cout << "파일 로드 완료" << endl;
}

void ChampSearch() {
	if (head == nullptr) {
		cout << "리스트가 비어있습니다." << endl;
		return;
	}
	string searchName;
	cout << "찾을 챔피언의 이름을 입력하세요 : ";
	cin.ignore(1000, '\n');
	getline(cin, searchName);
	Node* curr = head;
	do {
		if (curr->info.name == searchName) {
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
	int stat = 0;
	while (true){
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
	Node* curr = head;
	Node* prev = tail;
	bool inscompare = false;
	do {
		inscompare = false;
		cout << "추가할 챔피언의 이름 입력 : ";
		cin.ignore(1000, '\n');
		getline(cin, insnode->info.name);
		do {
			if (head == nullptr) {
				inscompare = false;
				break;
			}
			if (curr->info.name == insnode->info.name) {
				cout << "이미 같은 이름이 존재" << endl;
				inscompare = true;
				curr = head;
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
	cin.ignore(1000, '\n');
	getline(cin, insnode->info.position);
	curr = head;
	if (head == nullptr) {
		head = insnode;
		tail = insnode;
		tail->next = head;
		return;
	}
	if (head->info.hp <= insnode->info.hp) {
		insnode->next = head;
		head = insnode;
		tail->next = head;
		cout << "삽입" << endl;
		return;
	}
	do {
		if (curr->info.hp >= insnode->info.hp && curr == tail) {
			tail->next = insnode;
			tail = insnode;
			tail->next = head;
			return;
		}
		if (curr->info.hp <= insnode->info.hp) {
			insnode->next = curr;
			curr = insnode;
			prev->next = curr;
		}
		else {
			prev = prev->next;
			curr = curr->next;
		}
	} while (curr != head);
	
}

void ChampDelete() {
	if (head == nullptr) {
		return;
	}
	cout << "삭제할 챔피언 입력 : ";
	string deltename;
	cin.ignore(1000, '\n');
	getline(cin, deltename);
	Node* curr = head;
	Node* prev = tail;
	if (head->info.name == deltename) {
		Node* deleteNode = head;
		head = head->next;
		tail->next = head;
		delete deleteNode;
	}
	do {
		if (curr->info.name == deltename) {
			if (curr == head && curr == tail) {
				delete head;
				head = nullptr;
				tail = nullptr;
				return;
			}
			Node* deleteNode = curr;
			curr = curr->next;
			prev->next = curr;
			delete deleteNode;
		}
		else {
			prev = prev->next;
			curr = curr->next;
		}
	} while (curr != head);
}

void ChampDeleteAll() {
	if (head == nullptr) {
		return;
	}
	cout << "삭제할 포지션 입력 : ";
	string deltename;
	cin.ignore(1000, '\n');
	getline(cin, deltename);
	while (head->info.position == deltename) {
		if (head == tail) {
			head = nullptr;
			tail = nullptr;
			return;
		}
		Node* deleteNode = head;
		head = head->next;
		tail->next = head;
		delete deleteNode;
	}
	Node* curr = head;
	Node* prev = tail;
	do {
		if (curr->info.position == deltename) {
			if (curr == head && curr == tail) {
				delete head;
				head = nullptr;
				tail = nullptr;
				return;
			}
			else {
				Node* deleteNode = curr;
				curr = curr->next;
				prev->next = curr;
				if (deleteNode == head) head = curr;
				if (deleteNode == tail) tail = curr;
				delete deleteNode;

			}
		}
		else {
			prev = prev->next;
			curr = curr->next;
		}
	} while (curr != head);
}

void ChampPrintAll() {
	if (head == nullptr) {
		cout << "리스트가 비어있습니다." << endl;
		return;
	}
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

int FindHP(int max_hp, Node* startedNode) {
	Node* curr = startedNode;
	do {
		if (curr->info.hp > max_hp) {
			max_hp = curr->info.hp;
		}
		curr = curr->next;
	} while (curr != head);
	return max_hp;
}

void ChampFMH() {
	Node* curr = head;
	int max_hp = curr->info.hp;
	max_hp = FindHP(max_hp, curr);
	curr = head;
	do	{
		if (curr->info.hp == max_hp) {
			cout << "Name : " << curr->info.name << endl;
			cout << "HP : " << curr->info.hp << endl;
			cout << "MP : " << curr->info.mp << endl;
			cout << "Speed : " << curr->info.speed << endl;
			cout << "Range : " << curr->info.range << endl;
			cout << "Position : " << curr->info.position << endl;
			cout << "=========================================" << endl;
		}
		curr = curr->next;
	} while (curr != head);
}

void ChampSBH() {
	Node* sortedhead = nullptr;
	Node* sortedtail = nullptr;

	while (head != nullptr) {
		Node* curr = head;
		Node* prev = tail;
		int max_hp = FindHP(head->info.hp, curr);
		while (curr->info.hp != max_hp) {
			prev = curr;
			curr = curr->next;
		}
		if (curr == head && curr == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			prev->next = curr->next;
			if (curr == head) {
				head = head->next;
				tail->next = head;
			}
			if (curr == tail) {
				tail = prev;
				tail->next = head;
			}
		}

		if (sortedhead == nullptr) {
			sortedhead = curr;
			sortedtail = curr;
			curr->next = sortedhead;
		}
		else {
			sortedtail->next = curr;
			sortedtail = curr;
			sortedtail->next = sortedhead;
		}
	}
	head = sortedhead;
	tail = sortedtail;
}

void HelpRule() {
	cout << "=====================명령어 목록======================";
	cout << "[Search] : 챔피언을 검색합니다." << endl;
	cout << "[Insert] : 챔피언을 추가합니다." << endl;
	cout << "[Delete] : 챔피언을 삭제합니다." << endl;
	cout << "[DeleteAll] : 입력한 포지션을 모두 삭제합니다." << endl;
	cout << "[PrintAll] : 모든 챔피언을 출력합니다." << endl;
	cout << "[FindMaxHp] : 체력이 가장 높은 챔피언들을 검색합니다." << endl;
	cout << "[SortByHp] : 체력이 높은 순서로 챔피언을 정렬합니다." << endl;
	cout << "======================================================" << endl;
}

void SeleteNumber(string input) {
	while (true) {
		cout << "사용할 명령어를 입력하세요 종료는 'end' 명령어 확인은 'help' 입력 : ";
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
			cout << "프로그램 종료.";
			return;
		}
		else if (input == "help") {
			HelpRule();
		}
		else {
			cout << "잘못 입력하셨습니다. 다시 입력하세요." << endl;
		}
	}
}

int main() {
	string input;
	LoadDataFile();
	if (programExit == true) return 0;
	SeleteNumber(input);
	return 0;
}