/*
// Level 3-1 재고 관리기

아래 구조체와 명령어를 처리하는 루프를 작성하시오.
실행은 폴더 내 CMakeLists.txt 를 참고 및 수정하여 실행. using namespace std 사용금지.

[명령어]
    add
        이름, 수량, 단가 입력 후 vector<Product> 에 추가.
        수량 또는 단가가 0 이하면 오류 메시지 출력, 추가 안 함.

    restock
        이름 입력 → 추가 수량 입력 후 해당 상품 재고 증가.
        상품이 없으면 오류 메시지 출력.

    sell
        이름 입력 → 판매 수량 입력.
        재고 차감. 판매 수량 > 재고 이면 오류 메시지, 차감 안 함.

    print
        전체 상품 목록 출력 (번호, 이름, 재고, 단가).

    total
        전체 재고 금액 합계 출력.  각 상품의 stock * price 의 합.

    quit
        종료.

조건:
1. add / restock / sell / print / total 은 각각 별도 함수로 분리할 것.
2. 이름 검색 시 iterator 를 사용할 것 (auto 불가).
3. print 에서는 const_iterator 를 명시적으로 사용할 것.
4. 읽기 전용 매개변수에 const& 를 붙일 것.
5. 명령어 입력은 대소문자 구분 없이 처리할 것 (5_함수.cpp 의 toUpper 패턴 참고).

// === 터미널 실행 예시 =======================

> add
Name Stock Price: 사과 100 500

> add
Name Stock Price: 바나나 50 300

> print
1. 사과    stock:100  price:500.00
2. 바나나  stock:50   price:300.00

> total
Total: 65000.00

> sell
Name Amount: 사과 30
Sold: 사과 30개 (남은 재고: 70개)

> sell
Name Amount: 바나나 200
Error: 재고 부족 (현재: 50개)

> restock
Name Amount: 사과 50
Restocked: 사과 +50개 (현재: 120개)

> quit
Bye

*/

#include <iostream>
#include <string>
#include <vector>

struct Product {
    std::string name;
    int         stock;
    float       price;
};

/* 내용 서술 */

int main() {
    return 0;
}