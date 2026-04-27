#include <iostream>

using namespace std;

struct CharatherInfo {
	char name[100];
	int hp;
	int mp;
	int speed;
	int range;
	char position[100];
};

CharatherInfo LoL_Dic[100] = {
	{"Jayce", 3466, 8307, 452, 73, "mid"},
	{"Vayne", 3318, 2790, 390, 60, "support"},
	{"Lee Sin", 9864, 6257, 747, 19, "support"},
	{"Teemo", 1915, 1313, 700, 68, "mid"},
	{"Nami", 2968, 2153, 803, 74, "support"},
	{"Jinx", 2583, 3042, 123, 53, "jungle"},
	{"Cassiopeia", 6067, 7330, 683, 24, "top"},
	{"Ahri", 4573, 7079, 177, 79, "top"},
	{"Fiora", 2591, 9329, 337, 81, "jungle"},
	{"Zac", 9864, 7272, 405, 49, "bottom"},
	{"Janna", 4922, 2275, 690, 66, "jungle"},
	{"Ashe", 7421, 5549, 428, 31, "top"},
	{"Twitch", 2980, 7703, 204, 91, "mid"},
	{"Ezreal", 3660, 9835, 274, 44, "mid"},
	{"Sona", 5655, 8442, 252, 26, "bottom"},
	{"Lulu", 3231, 2014, 503, 32, "support"},
	{"Amumu", 6763, 3994, 427, 19, "jungle"},
	{"Master Yi", 5737, 7168, 434, 61, "top"},
	{"Jarvan", 1895, 3070, 323, 80, "mid"},
	{"Shen", 4794, 9220, 783, 42, "mid"},
	{"Fizz", 9864, 1913, 433, 38, "bottom"},
	{"Taric", 6158, 7451, 160, 36, "bottom" },
};

int indexarr = 22;

int TextTest(const char* str1, const char* str2) {
	while (*str1 != '\0' && (*str1 == *str2)) {
		str1++;
		str2++;
	}
	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

void StrCpy(char* head, char* tail) {
	while (*tail != '\0') {
		*head = *tail;
		head++;
		tail++;
	}
	*head = '\0';
}

void ChampSearch() {
	if (indexarr == 0) {
		cout << "챔피언이 존재하지 않습니다." << endl;
	}
	char searr[100];
	int searchcount = 0;
	cout << "찾을 챔피언을 입력하세요 : ";
	cin.getline(searr, 100);
	for (int i = 0; i < indexarr; i++) {
		if (TextTest(LoL_Dic[i].name, searr) == 0) {
			cout << "Name : " << LoL_Dic[i].name << endl;
			cout << "HP : " << LoL_Dic[i].hp << endl;
			cout << "MP : " << LoL_Dic[i].mp << endl;
			cout << "Speed : " << LoL_Dic[i].speed << endl;
			cout << "Range : " << LoL_Dic[i].range << endl;
			cout << "Position : " << LoL_Dic[i].position << endl;
			searchcount++;
		}
	}
	if (searchcount == 0) {
		cout << "찾으시는 챔피언이 존재하지 않습니다." << endl;
		return;
	}
}

int InsertVaule() {
	int stat;
	while (true){
		cin >> stat;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "정수만 입력하세요." << endl;
		}
		else {
			if (cin.get() != '\n') {
				cout << "정수만 입력하세요." << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			return stat;
		}
		

	}
}

void ChampInsert() {
	if (indexarr >= 100) {
		cout << "리스트가 초과되었습니다. 챔피언을 삭제해주세요." << endl;
	}
	char namearr[100], posarr[100];
	int h, m, s, r;

	cout << "추가할 챔피언의 이름을 입력하세요 : ";
	cin.getline(namearr, 100);
	for (int i = 0; i < indexarr; i++) {
		if (TextTest(LoL_Dic[i].name, namearr) == 0) {
			cout << "이미 동일한 이름의 챔피언이 존재합니다. 다시 입력하세요" << endl;
			continue;
		}
	}
	cout << "Hp : ";
	h = InsertVaule();
	cout << "Mp : ";
	m = InsertVaule();
	cout << "Speed : ";
	s = InsertVaule();
	cout << "Range : ";
	r = InsertVaule();
	cout << "Position : ";
	cin.getline(posarr, 100);


	StrCpy(LoL_Dic[indexarr].name, namearr);
	LoL_Dic[indexarr].hp = h;
	LoL_Dic[indexarr].mp = m;
	LoL_Dic[indexarr].speed = s;
	LoL_Dic[indexarr].range = r;
	StrCpy(LoL_Dic[indexarr].position, posarr);

	indexarr++;
	cout << "추가완료" << endl;
}

void ChampDelete() {
	if (indexarr == 0) {
		cout << "삭제 못함" << endl;
	}
	char delarr[100];
	int delcount = 0;
	cout << "삭제할 챔피언 입력 : ";
	cin.getline(delarr, 100);
	for (int i = indexarr - 1; i >= 0; i--) {
		if (TextTest(LoL_Dic[i].name, delarr) == 0) {
			for (int j = i; j < indexarr - 1; j++) {
				LoL_Dic[j] = LoL_Dic[j + 1];
			}
			cout << "삭제를 완료했습니다.";
			return;
		}
	}
	cout << "챔피언이 존재하지 않습니다.";
}

void ChampDeleteAll() {
	if (indexarr == 0) {
		cout << "삭제 못함" << endl;
	}
	char delarr[100];
	int delcount = 0;
	cout << "삭제할 포지션 입력 : ";
	cin.getline(delarr, 100);
	for (int i = indexarr - 1; i >= 0; i--) {
		if (TextTest(LoL_Dic[i].position, delarr) == 0) {
			for (int j = i; j < indexarr - 1; j++) {
				LoL_Dic[j] = LoL_Dic[j + 1];
			}
			delcount++;
		}
	}
	if (delcount == 0) {
		cout << "포지션이 존재하지 않습니다.";
	}
	else {
		cout << "삭제를 완료 했습니다." << endl;
	}
}

void ChampPrintAll() {
	if (indexarr == 0) {
		cout << "리스트에 챔피언이 없습니다." << endl;
		return;
	}
	cout << "챔피언 리스트" << endl;
	for (int i = 0; i < indexarr; i++) {
		cout << LoL_Dic[i].name << ", ";
		cout << LoL_Dic[i].hp << ", ";
		cout << LoL_Dic[i].mp << ", ";
		cout << LoL_Dic[i].speed << ", ";
		cout << LoL_Dic[i].range << ", ";
		cout << LoL_Dic[i].position << endl;
	}
}

void ChampFMH() {
	if (indexarr == 0) {
		cout << "없어요" << endl;
	}
	int king;
	king = LoL_Dic[0].hp;
	for (int i = 1; i < indexarr; i++) {
		if (king < LoL_Dic[i].hp) {
			king = LoL_Dic[i].hp;
		}
	}
	for (int i = 0; i < indexarr; i++) {
		if (king == LoL_Dic[i].hp) {
			cout << "Name : " << LoL_Dic[i].name << endl;
			cout << "HP : " << LoL_Dic[i].hp << endl;
			cout << "MP : " << LoL_Dic[i].mp << endl;
			cout << "Speed : " << LoL_Dic[i].speed << endl;
			cout << "Range : " << LoL_Dic[i].range << endl;
			cout << "Position : " << LoL_Dic[i].position << endl << endl;
		}
	}
}

void ChampSBH() {
	if (indexarr <= 1) {
		cout << "없어요" << endl;
	}
	CharatherInfo temp;
	for (int i = 0; i < indexarr - 1; i++) {
		for (int j = 0; j < indexarr - 1; j++) {
			if (LoL_Dic[j].hp < LoL_Dic[j + 1].hp) {
				temp = LoL_Dic[j];
				LoL_Dic[j] = LoL_Dic[j + 1];
				LoL_Dic[j + 1] = temp;
			}
		}
	}
	cout << "정렬 완료" << endl;
}

void HelpRule() {
	cout << "명령어 목록" << endl;
	cout << "[Search]" << endl;
	cout << "[Insert]" << endl;
	cout << "[Delete]" << endl;
	cout << "[DeleteAll]" << endl;
	cout << "[PrintAll]" << endl;
	cout << "[FindMaxHp]" << endl;
	cout << "[SortByHp]" << endl;
}

int main() {
	char input[100];
	while (true) {
		cout << "사용하려는 명령어를 입력하세요. 종료는 'end' 명령어 찾기는 'help' 입력. : ";
		cin.getline(input, 100);
		if (TextTest(input, "Search") == 0) {
			ChampSearch();
		}
		else if (TextTest(input, "Insert") == 0) {
			ChampInsert();
		}
		else if (TextTest(input, "Delete") == 0) {
			ChampDelete();
		}
		else if (TextTest(input, "DeleteAll") == 0) {
			ChampDeleteAll();
		}
		else if (TextTest(input, "PrintAll") == 0) {
			ChampPrintAll();
		}
		else if (TextTest(input, "FindMaxHp") == 0) {
			ChampFMH();
		}
		else if (TextTest(input, "SortByHp") == 0) {
			ChampSBH();
		}
		else if (TextTest(input, "help") == 0) {
			HelpRule();
		}
		else if (TextTest(input, "end") == 0) {
			cout << "종료 되었습니다.";
			return 0;
		}
		else {
			cout << "잘못 입력하셨습니다. 다시 입력하세요." << endl;
			continue;
		}
	}
}