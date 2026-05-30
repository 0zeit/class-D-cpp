/*
// Level 2-2 동적 배열 클래스: IntBuffer

동적 배열(new/delete)을 내부에서 관리하는 IntBuffer 클래스를 작성하시오.
실행은 폴더 내 CMakeLists.txt 를 참고 및 수정하여 실행. using namespace std 사용금지.

[멤버 변수] (private)
    int*   data     : 동적으로 할당된 정수 배열
    size_t capacity : 최대 저장 가능 개수
    size_t count    : 현재 저장된 개수 (초기값 0)

[멤버 함수]
    IntBuffer(size_t capacity)
        생성자. new[] 로 capacity 만큼 동적 할당.

    IntBuffer(const IntBuffer& other)
        복사 생성자. 반드시 깊은 복사(Deep Copy) 로 구현.
        새 배열을 new[] 로 따로 할당하고 값을 복사할 것.

    ~IntBuffer()
        소멸자. delete[] 로 반드시 메모리 해제.

    bool push(int value)
        value 를 끝에 추가. capacity 초과 시 false 반환, 저장 안 함.
        성공 시 true 반환.

    bool pop(int& out)
        마지막 원소를 out 에 꺼내고 count 를 1 감소. 비어있으면 false 반환.
        성공 시 true 반환.

    int peek() const
        원소 들여다보기. 마지막 원소를 반환. 비어있으면 -1 반환 (제거는 하지 않음).

    bool isEmpty() const
        count == 0 이면 true.

    bool isFull() const
        count == capacity 이면 true.

    size_t size() const
        현재 count 반환.

    void print() const
        "[a, b, c]" 형식으로 출력. 빈 경우 "[]" 출력.

조건:
1. 값을 수정하지 않는 함수에 const 를 붙일 것.
2. 복사 생성자는 반드시 새 배열을 new[] 로 따로 할당할 것 (포인터 복사 금지).
3. data 는 private 으로 유지. 외부 직접 접근 금지.

// === main 실행 예시 =======================

IntBuffer buf(3);
cout << buf.isEmpty() << "\n";     // 1
buf.push(10); buf.push(20); buf.push(30);
buf.print();                       // [10, 20, 30]
cout << buf.isFull() << "\n";      // 1
cout << buf.push(99) << "\n";      // 0 (가득 참)

int val;
buf.pop(val);
cout << val << "\n";               // 30
buf.print();                       // [10, 20]

IntBuffer buf2(buf);               // 복사 생성자
buf2.push(99);
buf2.print();                      // [10, 20, 99]
buf.print();                       // [10, 20]  ← buf 는 영향 없음

*/

#include <iostream>

/* 내용 서술 */

int main() {
    return 0;
}