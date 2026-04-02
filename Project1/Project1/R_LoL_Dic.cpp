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
	{"Taric", 6158, 7451, 160, 36, "bottom" }
};

int indexarr = 22;
int arrcount = 0;

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

void SearchTest(char c[]) {
	if (indexarr == arrcount) {
		return;
	}
	if (TextTest(LoL_Dic[arrcount].name, c) == 0) {
		cout << "Name : " << LoL_Dic[arrcount].name << endl;
		cout << "HP : " << LoL_Dic[arrcount].hp << endl;
		cout << "MP : " << LoL_Dic[arrcount].mp << endl;
		cout << "Speed : " << LoL_Dic[arrcount].speed << endl;
		cout << "Range : " << LoL_Dic[arrcount].range << endl;
		cout << "Position : " << LoL_Dic[arrcount].position << endl;
		return;
	}
	arrcount++;
	return SearchTest(c);
}

void ChampSearch() {
	arrcount = 0;
	if (indexarr == 0) {
		cout << "리스트에 챔피언이 없습니다. 챔피언을 추가해 주세요." << endl;
		return;
	}
	char searcharr[100];
	cout << "찾으실 챔피언의 이름을 입력하세요 : ";
	cin.getline(searcharr,100);
	SearchTest(searcharr);
	if (indexarr <= arrcount) {
		cout << "찾으시는 챔피언이 존재하지 않습니다." << endl;
		return;
	}
}

void ChampInsert() {
	arrcount = 0;
	if (indexarr >= 100) {
		cout << "더 이상 캐릭터를 추가할 수 없습니다. 캐릭터를 추가해 주세요.";
		return;
	}
	char insertarr[100];
}

void DeleteTest(char del[]) {
	if (arrcount < 0) {
		cout << "챔피언이 존재하지 않습니다." << endl;
		return;
	}
	if (TextTest(LoL_Dic[arrcount].name, del) == 0) {
		for (int i = arrcount; i < indexarr-1; i++) {
			LoL_Dic[i] = LoL_Dic[i + 1];
		}
		cout << "삭제 되었습니다." << endl;
		indexarr--;
		return;
	}
	else {
		arrcount--;
		DeleteTest(del);
	}
}

void ChampDelete() {
	if (indexarr == 0) {
		cout << "삭제할 챔피언이 존재하지 않습니다." << endl;
		return;
	}
	char delarr[100];
	int delcount = 0;
	arrcount = indexarr - 1;
	cout << "삭제할 챔피언의 이름을 입력하세요 : ";
	cin.getline(delarr, 100);
	DeleteTest(delarr);
}

void DeleteAllTest(char del[],int dec) {
	if (arrcount < 0 && dec != 0) {
		cout << "삭제 되었습니다." << endl;
		return;
	}
	else if (arrcount < 0) {
		cout << "포지션이 존재하지 않습니다." << endl;
		return;
	}
	if (TextTest(LoL_Dic[arrcount].position, del) == 0) {
		for (int i = arrcount; i < indexarr - 1; i++) {
			LoL_Dic[i] = LoL_Dic[i + 1];
		}
		indexarr--;
		dec++;
	}
	arrcount--;
	DeleteAllTest(del,dec);
	
}

void ChampDeleteAll() {
	if (indexarr == 0) {
		cout << "삭제할 포지션이 존재하지 않습니다." << endl;
		return;
	}
	char delarr[100];
	int delcount = 0;
	arrcount = indexarr - 1;
	cout << "삭제할 포지션을 입력하세요 : ";
	cin.getline(delarr, 100);
	DeleteAllTest(delarr,delcount);
}

void ChampPrintAll() {
	if (indexarr == 0) {
		cout << "리스트에 챔피언이 없습니다. 챔피언을 추가해 주세요." << endl;
		return;
	}
	if (arrcount == indexarr) {
		arrcount = 0;
		return;
	}
	cout << LoL_Dic[arrcount].name << ", ";
	cout << LoL_Dic[arrcount].hp << ", ";
	cout << LoL_Dic[arrcount].mp << ", ";
	cout << LoL_Dic[arrcount].speed << ", ";
	cout << LoL_Dic[arrcount].range << ", ";
	cout << LoL_Dic[arrcount].position << endl;
	arrcount++;
	return ChampPrintAll();
}

void ChampFMH() {

}

void ChampSBH() {

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
			arrcount = 0;
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