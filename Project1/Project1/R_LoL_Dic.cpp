#include <iostream>

using namespace std;

struct CharatherInfo {
	char name[100];
	int hp;
	int mp;
	int speed;
	int range;
	char position[100];

	bool isvalue;
};

CharatherInfo LoL_Dic[100] = {
	{"Jayce", 3466, 8307, 452, 73, "mid", true},
	{"Vayne", 3318, 2790, 390, 60, "support", true},
	{"Lee Sin", 9864, 6257, 747, 19, "support", true},
	{"Teemo", 1915, 1313, 700, 68, "mid", true},
	{"Nami", 2968, 2153, 803, 74, "support", true},
	{"Jinx", 2583, 3042, 123, 53, "jungle", true},
	{"Cassiopeia", 6067, 7330, 683, 24, "top", true},
	{"Ahri", 4573, 7079, 177, 79, "top", true},
	{"Fiora", 2591, 9329, 337, 81, "jungle", true},
	{"Zac", 9864, 7272, 405, 49, "bottom", true},
	{"Janna", 4922, 2275, 690, 66, "jungle", true},
	{"Ashe", 7421, 5549, 428, 31, "top", true},
	{"Twitch", 2980, 7703, 204, 91, "mid", true},
	{"Ezreal", 3660, 9835, 274, 44, "mid", true},
	{"Sona", 5655, 8442, 252, 26, "bottom",true},
	{"Lulu", 3231, 2014, 503, 32, "support",true},
	{"Amumu", 6763, 3994, 427, 19, "jungle",true},
	{"Master Yi", 5737, 7168, 434, 61, "top",true},
	{"Jarvan", 1895, 3070, 323, 80, "mid",true},
	{"Shen", 4794, 9220, 783, 42, "mid",true},
	{"Fizz", 9864, 1913, 433, 38, "bottom",true},
	{"Taric", 6158, 7451, 160, 36, "bottom",true},
};

CharatherInfo list;

int TextTest(const char* str1, const char* str2) {
	while (*str1 != '\0' && (*str1 == *str2)) {
		str1++;
		str2++;
	}
	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

void Strcpy(char* chead, char* ctail) {
	while (*ctail != '\0') {
		*chead = *ctail;
		chead++;
		ctail++;
	}
	*chead = '\0';
}

void Search(char str[], int temp) {
	if (temp >= 100) {
		cout << "없습니다.";
		return;
	}
	if (TextTest(LoL_Dic[temp].name, str) == 0 && LoL_Dic[temp].isvalue == true) {
		cout << "Name : " << LoL_Dic[temp].name << endl;
		cout << "HP : " << LoL_Dic[temp].hp << endl;
		cout << "MP : " << LoL_Dic[temp].mp << endl;
		cout << "Speed : " << LoL_Dic[temp].speed << endl;
		cout << "Range : " << LoL_Dic[temp].range << endl;
		cout << "Position : " << LoL_Dic[temp].position << endl;
		return;
	}
	Search(str, temp + 1);
}

void ChampSearch() {
	int indexarr = 0;
	char seararr[100];
	cout << "찾을 챔피언의 이름을 입력 : ";
	cin.getline(seararr, 100);
	Search(seararr, indexarr);
}

int InsertValue() {
	int stat = 0;
	while (true)
	{
		cin >> stat;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "정수만 입력" << endl;
		}
		else
		{
			if (cin.get() != '\n') {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "정수만 입력" << endl;
				continue;
			}
			return stat;
		}
	}
}

void Insert(int hp, int mp, int sp, int ra, int temp, char name[], char pos[]) {
	if (temp >= 100) {
		cout << "잘못된 접근" << endl;
		return;
	}
	if (LoL_Dic[temp].isvalue == false) {
		Strcpy(LoL_Dic[temp].name, name);
		LoL_Dic[temp].hp = hp;
		LoL_Dic[temp].mp = mp;
		LoL_Dic[temp].speed = sp;
		LoL_Dic[temp].range = ra;
		Strcpy(LoL_Dic[temp].position, pos);
		LoL_Dic[temp].isvalue = true;
		return;
	}
	Insert(hp, mp, sp, ra, temp + 1, name, pos);
}

void NameCompare(int temp, char name[]) {
	if (temp >= 100) {
		return;
	}
	if (TextTest(LoL_Dic[temp].name, name) == 0 && LoL_Dic[temp].isvalue == true) {
		cout << "동일한 이름의 챔피언이 존재 다시 입력하세요 : " << endl;
		cin.getline(name, 100);
		NameCompare(0, name);
		return;
	}
	NameCompare(temp + 1, name);
}

void ChampInsert() {
	for (int i = 0; i < 100; i++) {
		if (LoL_Dic[i].isvalue == false) {
			break;
		}
		else if(i == 99) {
			cout << "리스트가 가득 찼습니다.";
			return;
		}
	}
	char namearr[100], posarr[100];
	int h, m, s, r, indexarr = 0;
	cout << "추가할 캐릭터의 이름을 입력 : ";
	cin.getline(namearr, 100);
	NameCompare(0, namearr);
	cout << "Hp : ";
	h = InsertValue();
	cout << "MP : ";
	m = InsertValue();
	cout << "Speed : ";
	s = InsertValue();
	cout << "Range : ";
	r = InsertValue();
	cout << "Position : ";
	cin.getline(posarr, 100);
	Insert(h, m, s, r, indexarr, namearr, posarr);
	cout << "추가 완료" << endl;

}

void Delete(char str[], int temp) {
	if (temp >= 100) {
		cout << "없습니다." << endl;
		return;
	}
	if (TextTest(LoL_Dic[temp].name, str) == 0 && LoL_Dic[temp].isvalue == true) {
		LoL_Dic[temp] = {};
		cout << "삭제 되었습니다.";
		return;
	}
	Delete(str, temp + 1);
	
}

void ChampDelete() {
	char delarr[100];
	int indexarr = 0;
	cout << "삭제할 챔피언의 이름을 입력 : ";
	cin.getline(delarr, 100);
	Delete(delarr, indexarr);
}

void DeleteALL(char str[], int temp, int &count) {
	if (temp >= 100) {
		return;
	}
	if (TextTest(LoL_Dic[temp].position, str) == 0 && LoL_Dic[temp].isvalue == true) {
		LoL_Dic[temp] = {};
		count++;
	}
	DeleteALL(str, temp + 1, count);
	
}

void ChampDeleteAll() {
	char dearr[100];
	int indexarr = 0, delcount = 0;
	cout << "삭제할 포지션 선택 : ";
	cin.getline(dearr, 100);
	DeleteALL(dearr, indexarr, delcount);
	if (delcount == 0) {
		cout << "리스트에 찾는 포지션이 존재하지 않습니다." << endl;
	}
	else {
		cout << "삭제 완료" << endl;
	}
}

void ChampPrintAll(int temp) {
	if (temp >= 100) {
		return;
	}
	if (LoL_Dic[temp].isvalue == true) {
		cout << LoL_Dic[temp].name << ", ";
		cout << LoL_Dic[temp].hp << ", ";
		cout << LoL_Dic[temp].mp << ", ";
		cout << LoL_Dic[temp].speed << ", ";
		cout << LoL_Dic[temp].range << ", ";
		cout << LoL_Dic[temp].position << endl;
	}
	ChampPrintAll(temp + 1);
}

void FindMaxHp(int temp, int top) {
	if (temp >= 100) {
		return;
	}
	if (top == LoL_Dic[temp].hp && LoL_Dic[temp].isvalue == true) {
		cout << "Name : " << LoL_Dic[temp].name << endl;
		cout << "HP : " << LoL_Dic[temp].hp << endl;
		cout << "MP : " << LoL_Dic[temp].mp << endl;
		cout << "Speed : " << LoL_Dic[temp].speed << endl;
		cout << "Range : " << LoL_Dic[temp].range << endl;
		cout << "Position : " << LoL_Dic[temp].position << endl << endl;
	}
	FindMaxHp(temp + 1, top);
}

void ChampFMH() {
	int king = 0, indexarr = 0;
	for (int i = 0; i < 100; i++) {
		if (LoL_Dic[i].isvalue == true) {
			king = LoL_Dic[i].hp;
			break;
		}
	}
	for (int i = 0; i < 100; i++) {
		if (king < LoL_Dic[i].hp && LoL_Dic[i].isvalue == true) {
			king = LoL_Dic[i].hp;
		}
	}
	FindMaxHp(indexarr, king);
}

void ExratctTemp(CharatherInfo temp[], int& count, int index) {
	if (index >= 100) {
		return;
	}
	if (LoL_Dic[index].isvalue == true) {
		temp[count] = LoL_Dic[index];
		count++;
	}
	ExratctTemp(temp, count, index + 1);
}

void BubbleInner(CharatherInfo temp[], int max, int index) {
	if (index >= max) {
		return;
	}
	if (temp[index].hp < temp[index + 1].hp) {
		list = temp[index];
		temp[index] = temp[index + 1];
		temp[index + 1] = list;
	}
	BubbleInner(temp, max, index + 1);
}

void BubbleOuter(CharatherInfo temp[], int n) {
	if (n <= 1) {
		return;
	}
	BubbleInner(temp, n - 1, 0);
	BubbleOuter(temp, n - 1);
}

void InjectTemp(CharatherInfo temp[], int& count, int index) {
	if (index >= 100) {
		return;
	}
	if (LoL_Dic[index].isvalue == true) {
		LoL_Dic[index] = temp[count];
		count++;
	}
	InjectTemp(temp, count, index + 1);
}

void ChampSBH() {
	CharatherInfo temp[100] = {};
	int count = 0;

	ExratctTemp(temp, count, 0);

	BubbleOuter(temp, count);
	count = 0;

	InjectTemp(temp, count, 0);

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
			int printcount = 0;
			ChampPrintAll(printcount);
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