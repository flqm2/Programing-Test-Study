#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y, z;
};

Point arr[10];
bool valid[10] = { false };
int bottom_idx = 0; 
int point_count = 0; 
bool f_mode = false; 

void Print() {
    if (f_mode) {
        vector<pair<Point, double>> vec;
        for (int i = 0; i < 10; i++) {
            if (valid[i]) {
                double dist = sqrt(arr[i].x * arr[i].x + arr[i].y * arr[i].y + arr[i].z * arr[i].z);
                vec.push_back({ arr[i], dist });
            }
        }

        sort(vec.begin(), vec.end(), [](const pair<Point, double>& a, const pair<Point, double>& b) {
            return a.second < b.second;
            });

        for (int i = 9; i >= 0; i--) {
            cout << setw(2) << i << " | ";
            if (i < vec.size()) {
                cout << vec[i].first.x << " " << vec[i].first.y << " " << vec[i].first.z
                    << "   (거리: " << fixed << setprecision(2) << vec[i].second << ")";
            }
            cout << endl;
        }
    }
    else {
        for (int i = 9; i >= 0; i--) {
            cout << setw(2) << i << " | ";
            if (valid[i]) {
                cout << arr[i].x << " " << arr[i].y << " " << arr[i].z;
            }
            cout << endl;
        }
    }
    cout << endl;
}

void Cmd_Plus(int x, int y, int z) {
    if (point_count >= 10) return;

    int top_idx = (bottom_idx + point_count) % 10;
    arr[top_idx] = { x, y, z };
    valid[top_idx] = true;
    point_count++;
}

void Cmd_Minus() {
    if (point_count <= 0) return;

    int top_idx = (bottom_idx + point_count - 1) % 10;
    valid[top_idx] = false;
    point_count--;
}

void Cmd_E(int x, int y, int z) {
    if (point_count >= 10) return;

    for (int i = point_count - 1; i >= 0; i--) {
        int from = (bottom_idx + i) % 10;
        int to = (from + 1) % 10;
        arr[to] = arr[from];
        valid[to] = true;
    }

    arr[bottom_idx] = { x, y, z };
    valid[bottom_idx] = true;
    point_count++;
}

void Cmd_D() {
    if (point_count <= 0) return;

    valid[bottom_idx] = false;
    bottom_idx = (bottom_idx + 1) % 10; 
    point_count--;
}


void Cmd_B() {
    if (point_count <= 0) return;

    Point temp[10];
    bool temp_valid[10] = { false };

    for (int i = 0; i < 10; i++) {
        if (valid[i]) {
            int new_idx = (i - 1 + 10) % 10;
            temp[new_idx] = arr[i];
            temp_valid[new_idx] = true;
        }
    }

    for (int i = 0; i < 10; i++) {
        arr[i] = temp[i];
        valid[i] = temp_valid[i];
    }
    bottom_idx = (bottom_idx - 1 + 10) % 10;
}

void Cmd_C() {
    for (int i = 0; i < 10; i++) valid[i] = false;
    bottom_idx = 0;
    point_count = 0;
}

void Cmd_G() {
    if (point_count < 2) {
        cout << "거리를 계산하려면 2개 이상의 점이 필요합니다." << endl;
        return;
    }

    vector<Point> pts;
    for (int i = 0; i < 10; i++) {
        if (valid[i]) pts.push_back(arr[i]);
    }

    double max_d = -1.0;
    double min_d = 9999999.0;
    pair<Point, Point> max_p, min_p;

    for (size_t i = 0; i < pts.size(); i++) {
        for (size_t j = i + 1; j < pts.size(); j++) {
            double d = sqrt(pow(pts[i].x - pts[j].x, 2) + pow(pts[i].y - pts[j].y, 2) + pow(pts[i].z - pts[j].z, 2));
            if (d > max_d) { max_d = d; max_p = { pts[i], pts[j] }; }
            if (d < min_d) { min_d = d; min_p = { pts[i], pts[j] }; }
        }
    }
    cout << "▶ 가장 먼 두 점: (" << max_p.first.x << " " << max_p.first.y << " " << max_p.first.z << ") & ("
        << max_p.second.x << " " << max_p.second.y << " " << max_p.second.z << ") -> 거리: " << fixed << setprecision(2) << max_d << endl;
    cout << "▶ 가장 가까운 두 점: (" << min_p.first.x << " " << min_p.first.y << " " << min_p.first.z << ") & ("
        << min_p.second.x << " " << min_p.second.y << " " << min_p.second.z << ") -> 거리: " << fixed << setprecision(2) << min_d << endl;
}

int main() {
    string input;

    while (true) {
        cin >> input;

        if (input == "+") {
            int x, y, z;
            cin >> x >> y >> z;
            Cmd_Plus(x, y, z);
            Print();
        }
        else if (input == "-") {
            Cmd_Minus();
            Print();
        }
        else if (input == "e") {
            int x, y, z;
            cin >> x >> y >> z;
            Cmd_E(x, y, z);
            Print();
        }
        else if (input == "d") {
            Cmd_D();
            Print();
        }
        else if (input == "a") {
            Print();
            cout << "▶ 저장된 점의 개수: " << point_count << "개\n" << endl;
        }
        else if (input == "b") {
            Cmd_B();
            Print();
        }
        else if (input == "c") {
            Cmd_C();
            Print();
        }
        else if (input == "f") {
            f_mode = !f_mode;
            Print();
        }
        else if (input == "g") {
            Print();
            Cmd_G();
            cout << endl;
        }
        else if (input == "q") {
            break;
        }
        else {
            cout << "잘못된 명령어입니다." << endl;
        }
    }
    return 0;
}