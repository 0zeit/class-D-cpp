#include <iostream>
#include <string>
#include <vector>

/*
struct와 class의 차이점?
 - struct는 모든 멤버들이 기본적으로 public, 주로 새로운 자료형을 만들 때 활용
 - class는 모든 멤버들이 기본적으로 private, 주로 시스템을 구축할 때 사용
 - 큰 차이는 없지만, 프로그래머들의 암묵적인 약속이 존재하는 정도...
*/

struct Misc { // 기타 아이템
    std::string mName;
    int         mValue;

    Misc(const std::string& name, int value) : mName(name), mValue(value) {
    }

    void display() const {
        std::cout << "아이템: " << mName << " (가격: " << mValue << "원)" << std::endl;
    }
};

struct Weapon { // 무기 아이템
    std::string mName;
    int         mValue;
    int         mDamage;

    Weapon(const std::string& name, int value, int damage) : mName(name), mValue(value), mDamage(damage) {
    }

    void display() const {
        std::cout << "무기: " << mName << " (공격력: " << mDamage << ")" << " (가격: " << mValue << "원)" << std::endl;
    }
};

struct Magic { // 마법 아이템
    std::string mName;
    int         mValue;
    int         mManaCost;

    Magic(const std::string& name, int value, int mana) : mName(name), mValue(value), mManaCost(mana) {
    }

    void display() const {
        std::cout << "스킬: " << mName << " (마나: " << mManaCost << ")" << " (가격: " << mValue << "원)" << std::endl;
    }
};

// mName과 mValue는 공통된 요소들이기에 부모 클래스 Item을 만들어 각 struct들에게 상속도 가능, 이번 예제에선 생략

template <typename T> // 템플레이트로 어떤 자료형이든 상관없이 수락! 코드를 일반화!
class Inventory {
private:
    std::vector<T> mItems; // "어떤 자료 타입" T를 받아서 동적배열에 할당!
    size_t         mMaxSize;

public:
    Inventory(int size = 10) : mMaxSize(size) {
    }

    bool add(const T& item) {
        if (mItems.size() >= mMaxSize) {
            std::cout << "인벤토리가 가득 찼습니다!" << std::endl;

            return false;
        }

        mItems.push_back(item);

        return true;
    }

    T* get(int index) { // 지정된 자료 타입의 포인터를 받아오기!
        if (mItems.size() <= index) {
            return nullptr;
        }

        return &mItems[index];
    }

    bool remove(size_t index) {
        if (mItems.size() <= index) {
            std::cout << "유효하지 않은 인덱스입니다!" << std::endl;

            return false;
        }

        mItems.erase(mItems.begin() + index);

        return true;
    }

    void display() const {
        std::cout << "\n=== 인벤토리 (" << mItems.size() << "/" << mMaxSize << ") ===" << std::endl;

        if (mItems.empty()) {
            std::cout << "(비어있음)" << std::endl;

            return;
        }

        for (size_t i = 0; i < mItems.size(); i++) {
            std::cout << "[" << i << "] ";

            mItems[i].display();
        }
    }

    T* findByName(const std::string& name) {
        for (size_t i = 0; i < mItems.size(); i++) {
            if (mItems[i].mName == name) {
                return &mItems[i];
            }
        }

        return nullptr;
    }

    int size() const {
        return mItems.size();
    }
    int capacity() const {
        return mMaxSize;
    }
};

int main() {
    Inventory<Misc>   inv_misc(5);
    Inventory<Weapon> inv_weapon(5);
    Inventory<Magic>  inv_magic(5);
    Inventory<Misc>   inv_test(2); // 테스트용 작은 인벤토리

    inv_misc.add(Misc("체력 물약", 100));
    inv_misc.add(Misc("마나 물약", 150));
    inv_misc.add(Misc("해독제", 50));
    inv_misc.display();

    inv_weapon.add(Weapon("목검", 100, 10));
    inv_weapon.add(Weapon("강철검", 150, 25));
    inv_weapon.add(Weapon("전설의 검", 150000, 100));
    inv_weapon.display();

    inv_magic.add(Magic("마을지도", 100, 30));
    inv_magic.add(Magic("모범택시 부르기", 300, 50));
    inv_magic.display();

    std::cout << "\n=== 검색 테스트" << std::endl;

    Misc* found = inv_misc.findByName("마나 물약");

    if (found != nullptr) {
        std::cout << "찾음: ";

        found->display();
    }
    else {
        std::cout << "찾을 수 없습니다!" << std::endl;
    }

    std::cout << "\n=== 제거 테스트" << std::endl;
    std::cout << "무기 인벤토리에서 1번 무기 제거..." << std::endl;

    inv_weapon.remove(1);
    inv_weapon.display();

    std::cout << "\n=== 용량 초과 테스트 ===" << std::endl;
    std::cout << "크기 2 인벤토리에 3개 추가 시도..." << std::endl;
    inv_test.add(Misc("아이템1", 10));
    inv_test.add(Misc("아이템2", 20));
    inv_test.add(Misc("아이템3", 30));
    inv_test.display();

    return 0;
}

/*
🤔 생각해보기:

 - 코드를 마치 변수처럼 활용 가능! 코드가 어떤 자료형식이던 상관없이 실행이 가능!
*/