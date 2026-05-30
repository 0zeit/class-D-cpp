/*
// Level 2-1 좌표 목록 연산

아래 Point 구조체가 주어진다. 함수들을 구현하고 main() 을 작성하시오.
실행은 폴더 내 CMakeLists.txt 를 참고 및 수정하여 실행. using namespace std 사용금지.

[구현할 함수]
    float getDistance(const Point& a, const Point& b)
        두 점 사이 거리 반환. <cmath> 의 sqrt() 사용 가능.

    Point getMidpoint(const Point& a, const Point& b)
        두 점의 중점을 Point 로 반환.

    void print(const Point& p)
        "(x, y)" 형식으로 출력. 소수점 1자리.

    void printAll(const vector<Point>& points)
        "N. (x, y)" 형식으로 번호와 함께 전체 출력.
        반드시 const_iterator 를 명시적으로 사용할 것.

    void sortByDistance(vector<Point>& points, const Point& origin)
        origin 으로부터의 거리 기준 오름차순(가까운 순) 정렬.
        std::sort 사용 금지. 버블 정렬 방식으로 직접 구현.
        이터레이터를 사용할 것.

조건:
1. auto 사용 금지. 이터레이터 타입을 명시적으로 선언.
2. std::sort 사용 금지.
3. 읽기 전용 매개변수에 const& 를 붙일 것.

주의 (버블 정렬 경계 조건):
내부 루프에서 it 와 it+1 을 비교하므로,
it+1 이 end() 를 가리키지 않도록 루프 종료 조건을 주의할 것.
5_함수.cpp 의 sort() 구현을 참고하되, 범위를 꼼꼼히 확인할 것.

// === main 실행 예시 =======================

Point p1 = {3.0f, 4.0f};
Point p2 = {0.0f, 0.0f};
print(p1);                              // (3.0, 4.0)
cout << getDistance(p1, p2) << "\n";    // 5.0
Point mid = getMidpoint(p1, p2);
print(mid);                             // (1.5, 2.0)

vector<Point> pts;
pts.push_back({3.0f, 4.0f});    // 원점 거리 5.0
pts.push_back({1.0f, 0.0f});    // 원점 거리 1.0
pts.push_back({2.0f, 2.0f});    // 원점 거리 약 2.83

Point origin = {0.0f, 0.0f};
sortByDistance(pts, origin);
printAll(pts);

*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
};

/* 내용 서술 */

int main() {
    return 0;
}