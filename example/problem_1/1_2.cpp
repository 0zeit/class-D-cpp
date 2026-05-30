/*
// Level 1-2 이터레이터로 벡터 다루기

vector<int> 를 받는 아래 함수들을 구현하시오. auto, 배열 인덱스([]), 범위 기반 for 는 전부 사용 금지. 이터레이터 타입을 항상 명시적으로 선언해야 한다.
실행은 폴더 내 CMakeLists.txt 를 참고 및 수정하여 실행. using namespace std 사용금지.

[구현할 함수]
    int sumPositives(const vector<int>& v)
        양수(> 0) 원소의 합 반환. 없으면 0.

    int countIf(const vector<int>& v, int threshold)
        threshold 이상인 원소 개수 반환.

    void doubleAll(vector<int>& v)
        모든 원소를 2배로 변경.

    void removeNegatives(vector<int>& v)
        음수인 원소를 전부 제거.

    void printAll(const vector<int>& v)
        원소를 공백으로 구분하여 출력 후 개행.

조건:
1. auto 사용 금지.
2. 배열 인덱스 [] 사용 금지.
3. 범위 기반 for 사용 금지.
4. const& 매개변수에는 const_iterator 사용.
5.      & 매개변수에는       iterator 사용.

힌트 (removeNegatives 구현 시):
erase() 는 해당 원소를 제거하고 그 다음 위치의 이터레이터를 반환한다.
erase 를 호출한 뒤에는 it 를 따로 ++해서는 안 된다.

// === main 실행 예시 =======================

vector<int> v = {3, -1, 0, 7, -4, 2};
printAll(v);                          // 3 -1 0 7 -4 2
cout << sumPositives(v) << "\n";      // 12
cout << countIf(v, 3)   << "\n";      // 2   (3 과 7 이 해당)
doubleAll(v);
printAll(v);                          // 6 -2 0 14 -8 4
removeNegatives(v);
printAll(v);                          // 6 0 14 4

*/

#include <iostream>
#include <vector>

/* 내용 서술 */

int main() {
    return 0;
}