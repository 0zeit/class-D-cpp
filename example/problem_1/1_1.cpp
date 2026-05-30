/*
// Level 1-1 클래스 기초 설계: Wallet

다음을 만족하는 Wallet 클래스를 작성한 뒤, main() 을 완성하여 실행 예시와 동일하게 출력하시오.
실행은 폴더 내 CMakeLists.txt 를 참고 및 수정하여 실행. using namespace std 사용금지.

[멤버 변수] (private)
    string owner   : 소유자 이름
    int    balance : 잔액 (초기값 0)

[멤버 함수]
    Wallet(const string& owner)
        생성자. balance 는 0 으로 초기화.

    bool deposit(int amount)
        잔액 추가.  amount 가 1 미만이면 false 반환, 처리 안 함.
        성공 시 true 반환.

    bool withdraw(int amount)
        잔액 차감.  amount 가 1 미만이거나 balance 초과면 false 반환, 처리 안 함.
        성공 시 true 반환.

    int getBalance() const
        현재 잔액 반환.

    void print() const
        "[소유자] 잔액: XXX원" 형식으로 출력.

조건:
    1. 값을 수정하지 않는 멤버 함수에는 반드시 const 를 붙일 것.
    2. string 매개변수는 반드시 const& 로 받을 것.
    3. 클래스 외부에서 balance 에 직접 접근하지 말 것 (private 유지).

// === main 실행 예시 =======================

Wallet w("철수");
w.print();                          // [철수] 잔액: 0원
w.deposit(5000);
w.print();                          // [철수] 잔액: 5000원
cout << w.withdraw(3000) << "\n";   // 1
w.print();                          // [철수] 잔액: 2000원
cout << w.withdraw(9999) << "\n";   // 0
w.print();                          // [철수] 잔액: 2000원
cout << w.getBalance()   << "\n";   // 2000

*/

#include <iostream>
#include <string>

/* 내용 서술 */

int main() {
    return 0;
}