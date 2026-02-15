#include <iostream>
#include <string>
#include <vector>

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
        std::cout << "무기: " << mName << " (공격력: " << mDamage << ")" << std::endl;
    }
};

class MiscInventory { // 기타 아이템 전용 인벤토리
private:
    std::vector<Misc> mMiscs;
    int               mMaxSize;

public:
    MiscInventory(int size = 10) : mMaxSize(size) {
    }

    bool add(const Misc& item) {
        // 인벤토리에 추가하기
        return false;
    }

    Misc* get(int index) { // Misc 포인터 형
        // 가져오기
        return nullptr;
    }

    bool remove(int index) {
        // 인벤토리에서 지우기
        return false;
    }

    void display() const {
        std::cout << "\n=== 기타 아이템 인벤토리" << std::endl;
        // 모든 기타 아이템 표시하기
    }

    int size() const {
        return mMiscs.size();
    }

    int capacity() const {
        return mMaxSize;
    }
};

class WeaponInventory { // 무기 아이템 전용 인벤토리, 코드가 기타 아이템 인벤토리랑 거의 동일
private:
    std::vector<Weapon> mWeapons;
    int                 mMaxSize;

public:
    WeaponInventory(int size = 10) : mMaxSize(size) {
    }

    bool add(const Weapon& item) {
        // 인벤토리에 추가하기
        return false;
    }

    Weapon* get(int index) { // Weapon 포인터 형
        // 가져오기
        return nullptr;
    }

    bool remove(int index) {
        // 인벤토리에서 지우기
        return false;
    }

    void display() const {
        std::cout << "\n=== 무기 아이템 인벤토리" << std::endl;
        // 모든 무기 아이템 표시하기
    }

    int size() const {
        return mWeapons.size();
    }

    int capacity() const {
        return mMaxSize;
    }
};

int main() {
    MiscInventory inv_misc(5);

    inv_misc.add(Misc("체력 물약", 100));
    inv_misc.add(Misc("마나 물약", 150));
    inv_misc.add(Misc("해독제", 50));
    inv_misc.display();

    WeaponInventory inv_weapon(5);

    inv_weapon.add(Weapon("목검", 100, 10));
    inv_weapon.add(Weapon("강철검", 150, 25));
    inv_weapon.add(Weapon("전설의 검", 1500, 100));
    inv_weapon.display();

    std::cout << "\n1번 아이템 제거..." << std::endl;

    inv_misc.remove(1);
    inv_misc.display();

    return 0;
}

/*
🤔 생각해보기:

1. 굳이 인벤토리 시스템을 아이템 종류마다 다 나눠야 하는가?
    - 코드가 동일하기에 굳이 나누는 의미가 보이지 않음

2. 인벤토리를 만들고 싶은 아이템 종류가 3개, 5개, 10개... 계속 늘어나면?
    - 동일한 코드를 계속 써야하고 기능을 하나 추가할 때마다 전부 수정해야함!

-> 그렇기에 우리는 C++에서 템플레이트(Template)를 활용하여 "코드를 일반화(Generic Programming)"!
*/