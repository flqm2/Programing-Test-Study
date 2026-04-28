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
	cin.ignore(1000, '\n');
	getline(cin, insnode->info.name);
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

	if (head->info.hp <= insnode->info.hp) {
		insnode->next = head;
		head = insnode;
		tail->next = head;
		cout << "삽입 완료!" << endl;
		return;
	}

	do {
		if (curr == tail && curr->info.hp > insnode->info.hp) {
			curr->next = insnode;
			insnode->next = head;
			tail = insnode;
			cout << "삽입 완료1" << endl;
			return;
		}
		if (curr->info.hp < insnode->info.hp) {
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
	if (head == nullptr && tail == head) {
		cout << "리스트에 챔피언이 너무 적거나 없습니다." << endl;
		return;
	}

	Node* sortedhead = nullptr;
	Node* sortedtail = nullptr;

	while (head != nullptr) {
		int max_hp = FindHP(max_hp, head);

		Node* maxNode = head;
		Node* prevNode = tail;

		if (maxNode->info.hp != max_hp) {
			prevNode = maxNode;
			maxNode = maxNode->next;
		}

		if (maxNode == head && maxNode == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			prevNode->next = maxNode->next;

		}
	}






	//// 새롭게 만들어질 정렬된 리스트를 가리킬 포인터
	//Node* sortedHead = nullptr;
	//Node* sortedTail = nullptr;

	//// 기존 리스트(head)가 완전히 빌 때까지(nullptr이 될 때까지) 반복
	//while (head != nullptr) {

	//	// 1. 직접 만드신 FindHP 함수를 호출하여 현재 리스트의 최고 체력(값)을 찾습니다!
	//	int max_hp = FindHP(head->info.hp, head);

	//	// 2. 최고 체력을 가진 노드(maxNode)와 그 이전 노드(maxPrev)를 찾습니다.
	//	// (노드를 뜯어내려면 이전 노드가 다음 노드를 덮어쓰도록 연결해야 하므로 prev가 꼭 필요합니다)
	//	Node* maxNode = head;
	//	Node* maxPrev = tail; // 원형 리스트이므로 head의 이전 노드는 tail입니다.

	//	while (maxNode->info.hp != max_hp) {
	//		maxPrev = maxNode;
	//		maxNode = maxNode->next;
	//	}

	//	// 3. 찾은 maxNode를 기존 리스트에서 뜯어냅니다(Detach).
	//	if (maxNode == head && maxNode == tail) {
	//		// 리스트에 노드가 딱 1개 남았던 경우, 이제 기존 리스트는 텅 비게 됩니다.
	//		head = nullptr;
	//		tail = nullptr;
	//	}
	//	else {
	//		maxPrev->next = maxNode->next; // 이전 노드가 잘려나갈 노드의 다음을 가리키게 하여 점프!

	//		if (maxNode == head) {
	//			head = maxNode->next;  // 뜯어낸 노드가 head였다면, 다음 노드가 새로운 head가 됨
	//			tail->next = head;     // 꼬리도 새로운 head를 가리키도록 갱신
	//		}
	//		else if (maxNode == tail) {
	//			tail = maxPrev;        // 뜯어낸 노드가 tail이었다면, 이전 노드가 새로운 tail이 됨
	//			tail->next = head;
	//		}
	//	}

	//	// 4. 뜯어낸 maxNode를 새로운 정렬 리스트의 맨 뒤에 붙입니다(Append).
	//	if (sortedHead == nullptr) {
	//		sortedHead = maxNode;
	//		sortedTail = maxNode;
	//		maxNode->next = sortedHead; // 새 리스트도 원형 유지
	//	}
	//	else {
	//		sortedTail->next = maxNode;
	//		sortedTail = maxNode;
	//		sortedTail->next = sortedHead; // 새 리스트 원형 유지
	//	}
	//}

	//// 5. 정렬이 완료된 새 리스트를 메인 리스트(head, tail)로 덮어씌웁니다.
	//head = sortedHead;
	//tail = sortedTail;
	

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