#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <filesystem>

using namespace std;

struct Vertex { double x{}, y{}, z{}; };
struct Texture { double s{}, t{}; };
struct Corner { int vertex{}; int texture{}; }; // texture가 0이면 텍스처 인덱스가 지정되지 않은 상태
struct Face { vector<string> tokens; int line{}; };

// 숫자 뒤의 잘못된 문자, NaN, 무한대와 범위를 벗어난 값을 검사한다.
double ReadNumber(const string& token, double low, double high) {
    size_t used = 0;
    double value = stod(token, &used);
    if (used != token.size() || !isfinite(value) || value < low || value > high)
        throw runtime_error("잘못된 좌표값입니다: " + token);
    return value;
}

int ReadIndex(const string& token) {
    if (token.empty() || token.find_first_not_of("0123456789") != string::npos)
        throw runtime_error("잘못된 인덱스입니다: " + token);
    int value = stoi(token);
    if (value < 1) throw runtime_error("인덱스는 1 이상이어야 합니다: " + token);
    return value;
}

Corner ReadCorner(const string& token) {
    size_t slash = token.find('/');
    if (slash == string::npos) return { ReadIndex(token), 0 };
    if (token.find('/', slash + 1) != string::npos)
        throw runtime_error("정점/텍스처 인덱스 형식으로 입력해야 합니다: " + token);
    return { ReadIndex(token.substr(0, slash)), ReadIndex(token.substr(slash + 1)) };
}

bool SameVertex(const Vertex& a, const Vertex& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

void PrintVertex(ostream& out, const Vertex& v) {
    out << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}

// 각 면을 독립적으로 검사하여 오류가 있어도 다음 면을 계속 처리한다.
void PrintFace(ostream& out, const Face& face, size_t number,
    const vector<Vertex>& vertices, const vector<Texture>& textures,
    const vector<bool>& validVertex, const vector<bool>& validTexture) {
    try {
        if (face.tokens.size() != 3)
            throw runtime_error("삼각형의 꼭짓점은 정확히 3개여야 합니다.");
        array<Corner, 3> corners;
        for (int i = 0; i < 3; ++i) {
            corners[i] = ReadCorner(face.tokens[i]);
            const Corner& c = corners[i];
            if (static_cast<size_t>(c.vertex) > vertices.size())
                throw runtime_error("정점 인덱스가 저장된 정점의 범위를 벗어났습니다.");
            if (!validVertex[c.vertex - 1])
                throw runtime_error("잘못된 정점 데이터를 참조하는 면입니다.");
            if (c.texture != 0) {
                if (static_cast<size_t>(c.texture) > textures.size())
                    throw runtime_error("텍스처 인덱스가 저장된 텍스처의 범위를 벗어났습니다.");
                if (!validTexture[c.texture - 1])
                    throw runtime_error("잘못된 텍스처 데이터를 참조하는 면입니다.");
            }
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                if (corners[i].vertex == corners[j].vertex)
                    throw runtime_error("삼각형의 정점 인덱스가 중복되었습니다.");
                if (SameVertex(vertices[corners[i].vertex - 1], vertices[corners[j].vertex - 1]))
                    throw runtime_error("삼각형의 정점 좌표값이 중복되었습니다.");
            }
        }
        const Vertex& a = vertices[corners[0].vertex - 1];
        const Vertex& b = vertices[corners[1].vertex - 1];
        const Vertex& c = vertices[corners[2].vertex - 1];
        double ux = b.x - a.x, uy = b.y - a.y, uz = b.z - a.z;
        double vx = c.x - a.x, vy = c.y - a.y, vz = c.z - a.z;
        double cx = uy * vz - uz * vy;
        double cy = uz * vx - ux * vz;
        double cz = ux * vy - uy * vx;
        // 추가 검사: 서로 다른 세 점이 일직선에 있으면 삼각형을 만들 수 없다.
        if (cx == 0.0 && cy == 0.0 && cz == 0.0)
            throw runtime_error("세 정점이 일직선에 있어 삼각형의 넓이가 0입니다.");

        out << "삼각형 " << number << " (" << corners[0].vertex << ", "
            << corners[1].vertex << ", " << corners[2].vertex << "): 정점 좌표 ";
        for (const Corner& corner : corners) {
            PrintVertex(out, vertices[corner.vertex - 1]);
            out << ' ';
        }
        out << "\n    텍스처 좌표 ";
        for (const Corner& corner : corners) {
            if (corner.texture == 0) out << "(지정되지 않음) ";
            else {
                const Texture& uv = textures[corner.texture - 1];
                out << '(' << uv.s << ", " << uv.t << ") ";
            }
        }
        out << '\n';
    }
    catch (const exception& e) {
        out << "삼각형 " << number << " [입력 줄 " << face.line << "] 오류: " << e.what() << '\n';
    }
}

int main(int argc, char* argv[]) {
    string inputName, outputName;
    if (argc >= 2) inputName = argv[1];
    else {
        cout << "불러올 파일 이름을 입력하세요 (예: cube.txt): ";
        if (!getline(cin, inputName)) return 1;
    }
    if (argc >= 3) outputName = argv[2];
    else {
        cout << "결과를 저장할 파일 이름을 입력하세요 (엔터: result.txt): ";
        getline(cin, outputName);
        if (outputName.empty()) outputName = "result.txt";
    }
    ifstream input(inputName);
    if (!input) { cerr << "입력 파일을 열 수 없습니다.\n"; return 1; }
    error_code ec;
    if (filesystem::equivalent(inputName, outputName, ec)) {
        cerr << "입력 파일과 결과 파일은 서로 다른 파일이어야 합니다.\n";
        return 1;
    }

    vector<Vertex> vertices;
    vector<Texture> textures;
    vector<bool> validVertex, validTexture;
    vector<Face> faces;
    ostringstream report;
    report << setprecision(10);
    string line;
    int lineNumber = 0;
    while (getline(input, line)) {
        ++lineNumber;
        if (lineNumber == 1 && line.compare(0, 3, "\xEF\xBB\xBF") == 0)
            line.erase(0, 3); // UTF-8 BOM
        size_t comment = line.find('#');
        if (comment != string::npos) line.erase(comment);
        istringstream ss(line);
        string type, token;
        if (!(ss >> type)) continue;
        vector<string> tokens;
        while (ss >> token) tokens.push_back(token);
        try {
            if (type == "v") {
                // 잘못된 데이터도 자리를 유지하여 이후 인덱스가 밀리지 않도록 한다.
                vertices.push_back({});
                validVertex.push_back(false);
                if (tokens.size() != 3) throw runtime_error("정점(v)은 좌표값 x, y, z가 필요합니다.");
                Vertex v{ ReadNumber(tokens[0], -1, 1), ReadNumber(tokens[1], -1, 1),
                          ReadNumber(tokens[2], -1, 1) };
                vertices.back() = v;
                validVertex.back() = true;
            }
            else if (type == "vt") {
                textures.push_back({});
                validTexture.push_back(false);
                if (tokens.size() != 2) throw runtime_error("텍스처(vt)는 좌표값 s, t가 필요합니다.");
                Texture t{ ReadNumber(tokens[0], 0, 1), ReadNumber(tokens[1], 0, 1) };
                textures.back() = t;
                validTexture.back() = true;
            }
            else if (type == "f") faces.push_back({ tokens, lineNumber });
            else throw runtime_error("알 수 없는 데이터 종류입니다: " + type);
        }
        catch (const exception& e) {
            report << "입력 줄 " << lineNumber << " 오류: " << e.what() << '\n';
        }
    }
    if (input.bad()) { cerr << "입력 파일을 읽는 중 오류가 발생했습니다.\n"; return 1; }

    bool duplicate = false;
    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = i + 1; j < vertices.size(); ++j) {
            if (validVertex[i] && validVertex[j] && SameVertex(vertices[i], vertices[j])) {
                duplicate = true;
                report << "중복된 정점 좌표의 인덱스: " << i + 1 << "번과 " << j + 1 << '\n';
            }
        }
    }
    for (size_t i = 0; i < faces.size(); ++i)
        PrintFace(report, faces[i], i + 1, vertices, textures, validVertex, validTexture);
    if (!duplicate) report << "중복된 정점 좌표값이 없습니다.\n";
    if (faces.empty()) report << "삼각형 면(f) 데이터가 없습니다.\n";

    ofstream output(outputName);
    if (!output) { cerr << "결과 파일을 열 수 없습니다.\n"; return 1; }
    output << report.str();
    output.close();
    if (!output) { cerr << "결과 파일을 저장하는 중 오류가 발생했습니다.\n"; return 1; }
    cout << report.str() << "결과 저장 완료: " << outputName << '\n';
    return 0;
}
