/*
// Level 3-2 복합 클래스 설계: Student & School

다음을 만족하는 두 클래스를 완성하시오.
실행은 폴더 내 CMakeLists.txt 를 참고 및 수정하여 실행. using namespace std 사용금지.

[Student 클래스]
    [멤버 변수] (private)
        string name
        int*   scores        : 과목 점수 동적 배열
        int    subject_count : 과목 수

    [멤버 함수]
        Student(const string& name, int subject_count)
            생성자. scores 를 new[] 로 동적 할당, 전부 0 으로 초기화.

        Student(const Student& other)
            복사 생성자. 깊은 복사.

        ~Student()
            소멸자. delete[] scores.

        void setScore(int idx, int score)
            idx 번 과목 점수 설정.
            idx 가 범위 밖이거나 score 가 0~100 밖이면 무시.

        float getAverage() const
            평균 점수 반환. subject_count == 0 이면 0.0f 반환.

        string getName() const
            이름 반환.

        void print() const
            "이름: 평균 XX.XX점 [s0 s1 ...]" 형식으로 출력.

[School 클래스]
    [멤버 변수] (private)
        string    name
        Student** students  // Student 포인터들의 동적 배열
        size_t    capacity
        size_t    count     // (초기값 0)

    [멤버 함수]
        School(const string& name, size_t capacity)
            생성자. students = new Student*[capacity].

        ~School()
            소멸자. students[i] 를 먼저 delete, 그 다음 students 를 delete[].
            순서를 틀리면 메모리 누수 발생.

        bool addStudent(const Student& s)
            Student 복사 생성자를 이용해 깊은 복사본을 new 로 생성하여 저장.
            capacity 초과 시 false 반환.

        void printAll() const
            "N. " 번호와 함께 전체 학생 출력.

        void printTop() const
            평균이 가장 높은 학생을 "[최우수]" 와 함께 출력.
            학생이 없으면 "No students." 출력.

조건:
1. 값을 수정하지 않는 함수에 const 를 붙일 것.
2. School::addStudent 는 매개변수 Student 의 깊은 복사본을 저장할 것.
3. School 소멸자 내 메모리 해제 순서를 반드시 지킬 것.
4. string/Student 매개변수는 const& 로 받을 것.

// === 터미널 실행 예시 =======================

Student s1("Alice", 3);
s1.setScore(0, 90); s1.setScore(1, 85); s1.setScore(2, 92);
s1.print();

Student s2("Bob", 3);
s2.setScore(0, 70); s2.setScore(1, 75); s2.setScore(2, 80);

School sc("MutableSchool", 5);
sc.addStudent(s1);
sc.addStudent(s2);
sc.printAll();
// 1. Alice: 평균 89.00점 [90 85 92]
// 2. Bob: 평균 75.00점 [70 75 80]

sc.printTop();
// [최우수] Alice: 평균 89.00점 [90 85 92]

*/

#include <iostream>
#include <string>

/* 내용 서술 */

int main() {
    return 0;
}