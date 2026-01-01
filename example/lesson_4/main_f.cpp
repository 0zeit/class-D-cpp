#include <cmath>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

namespace lesson4 {
    class Status {
    protected:
        int mCurrent;
        int mMax;

        sf::RectangleShape mBarBg;
        sf::RectangleShape mBarFg;

        void UpdateBar() {
            float        ratio         = static_cast<float>(mCurrent) / static_cast<float>(mMax);
            sf::Vector2f size_original = mBarBg.getSize();
            sf::Vector2f size_new      = {size_original.x * ratio, size_original.y};

            mBarFg.setSize(size_new);
        }

    public:
        Status(float x, float y, float width, float height, int max_value, sf::Color color) {
            mCurrent = mMax = max_value;

            mBarBg.setSize({width, height});
            mBarBg.setPosition({x, y});
            mBarBg.setFillColor(sf::Color(50, 50, 50));

            mBarFg.setSize({width, height});
            mBarFg.setPosition({x, y});
            mBarFg.setFillColor(color);
        }

        virtual ~Status() = default;

        int GetCurrent() const {
            return mCurrent;
        }

        int GetMax() const {
            return mMax;
        }

        bool IsDepleted() const {
            return mCurrent == 0;
        }

        void Decrease(int amount) {
            mCurrent -= amount;
            if (mCurrent < 0) {
                mCurrent = 0;
            }
            UpdateBar();
        }

        void Increase(int amount) {
            mCurrent += amount;
            if (mMax < mCurrent) {
                mCurrent = mMax;
            }
            UpdateBar();
        }

        virtual void Draw(sf::RenderWindow& window) {
            window.draw(mBarBg);
            window.draw(mBarFg);
        }
    };

    class Health : public Status {
    public:
        Health(float x, float y, int max_hp) : Status(x, y, 200.0f, 30.0f, max_hp, sf::Color::Green) {
        }

        void Draw(sf::RenderWindow& window) override {
            if (IsDepleted() == true) {
                mBarFg.setFillColor(sf::Color::Red);
            }
            else {
                mBarFg.setFillColor(sf::Color::Green);
            }

            Status::Draw(window);
        }
    };

    class Mana : public Status {
    public:
        Mana(float x, float y, int max_mp) : Status(x, y, 200.0f, 20.0f, max_mp, sf::Color::Blue) {
        }

        bool CanUse(int cost) const {
            return cost <= mCurrent;
        }

        void Draw(sf::RenderWindow& window) override {
            if (IsDepleted() == true) {
                mBarFg.setFillColor(sf::Color::Red);
            }
            else {
                mBarFg.setFillColor(sf::Color::Blue);
            }

            Status::Draw(window);
        }
    };

    class Character {
    protected:
        std::string     mName;
        sf::CircleShape mCharacter;
        sf::Vector2f    mPosition;
        Health          mHealth;
        Mana            mMana;

        virtual void OnDeath() {
            std::cout << mName << "이(가) 쓰러졌다!" << std::endl;

            mCharacter.setFillColor(sf::Color(100, 100, 100));
        }

    public:
        Character(const std::string& name, float pos_x, float pos_y, int max_hp, int max_mp, sf::Color color) : mName(name),
                                                                                                                mHealth(pos_x, pos_y, max_hp),
                                                                                                                mMana(pos_x, pos_y + 35.0f, max_mp) {
            mPosition = {pos_x, pos_y};

            mCharacter.setRadius(25.0f);
            mCharacter.setPosition({pos_x - 60.0f, pos_y});
            mCharacter.setFillColor(color);
            mCharacter.setOutlineColor(sf::Color::White);
            mCharacter.setOutlineThickness(2.0f);
        }

        virtual ~Character() = default;

        std::string GetName() const {
            return mName;
        }

        int GetHealth() const {
            return mHealth.GetCurrent();
        }

        bool IsAlive() const {
            return mHealth.IsDepleted() == false;
        }

        virtual void TakeDamage(int damage) {
            mHealth.Decrease(damage);

            std::cout << mName << "이(가) " << damage << " 데미지를 받았다! ";
            std::cout << "남은 체력: " << mHealth.GetCurrent() << "/" << mHealth.GetMax() << std::endl;

            if (IsAlive() == false) {
                OnDeath();
            }
        }

        void Heal(int amount) {
            mHealth.Increase(amount);

            std::cout << mName << "이(가) " << amount << " 체력을 회복했다! ";
            std::cout << "현재 체력: " << mHealth.GetCurrent() << "/" << mHealth.GetMax() << std::endl;
        }

        bool UseMana(int cost) {
            if (mMana.CanUse(cost) == false) {
                std::cout << mName << ": 마나가 부족하다!" << std::endl;

                return false;
            }

            mMana.Decrease(cost);

            return true;
        }

        void RestoreMana(int amount) {
            mMana.Increase(amount);
        }

        virtual void Draw(sf::RenderWindow& window) {
            if (IsAlive() == true) {
                window.draw(mCharacter);
                mHealth.Draw(window);
                mMana.Draw(window);
            }
        }
    };

    class Player : public Character {
    protected:
        void OnDeath() override {
            std::cout << "게임 오버!" << GetName() << "이(가) 쓰러졌다..." << std::endl;

            mCharacter.setFillColor(sf::Color::Red);
        }

    public:
        Player(std::string& name, float pos_x, float pos_y) : Character(name, pos_x, pos_y, 100, 50, sf::Color::Green) {
        }

        bool Skill(Character& target) {
            const int MANA_COST = 20;
            const int DAMAGE    = 40;

            if (UseMana(MANA_COST) == false) {
                return false;
            }

            std::cout << GetName() << "의 스킬 사용!" << std::endl;

            target.TakeDamage(DAMAGE);

            return true;
        }
    };

    class Enemy : public Character {
    protected:
        void OnDeath() override {
            std::cout << "승리! " << GetName() << "을(를) 처치했다!" << std::endl;

            mCharacter.setFillColor(sf::Color(50, 50, 50));
        }

    public:
        Enemy(std::string& name, float pos_x, float pos_y) : Character(name, pos_x, pos_y, 80, 30, sf::Color::Red) {
        }

        void CounterAttack(Character& target) {
            const int DAMAGE = 15;

            if (IsAlive() == false) {
                return;
            }

            std::cout << GetName() << "의 반격!" << std::endl;

            target.TakeDamage(DAMAGE);
        }
    };

} // namespace lesson4

int main() {
    using namespace lesson4;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Lesson 4 - Mini RPG ver.3");
    window.setFramerateLimit(60);

    sf::Font font("./res/font.ttf");

    std::string player_name("플레이어");
    std::string enemy_name("몹");

    Player player(player_name, 100.0f, 400.0f);
    Enemy  enemy(enemy_name, 400.0f, 400.0f);

    sf::Text           text_attack(font, L"공격", 25);
    sf::Text           text_heal(font, L"회복", 25);
    sf::Text           text_skill(font, L"스킬", 25);
    sf::RectangleShape button_attack({50.0f, 50.0f});
    sf::RectangleShape button_heal({50.0f, 50.0f});
    sf::RectangleShape button_skill({50.0f, 50.0f});

    text_attack.setPosition({50.0f, 100.0f});
    text_attack.setFillColor(sf::Color::Black);
    button_attack.setPosition({50.0f, 100.0f});
    button_attack.setFillColor(sf::Color::Red);

    text_heal.setPosition({50.0f, 160.0f});
    text_heal.setFillColor(sf::Color::Black);
    button_heal.setPosition({50.0f, 160.0f});
    button_heal.setFillColor(sf::Color::Green);

    text_skill.setPosition({50.0f, 220.0f});
    text_skill.setFillColor(sf::Color::Black);
    button_skill.setPosition({50.0f, 220.0f});
    button_skill.setFillColor(sf::Color::Cyan);

    while (window.isOpen() == true) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mousePressed->position);

                    // 공격 버튼
                    if (button_attack.getGlobalBounds().contains(mousePos)) {
                        if (player.IsAlive() == true && enemy.IsAlive() == true) {
                            enemy.TakeDamage(20);

                            if (enemy.IsAlive() == true) {
                                enemy.CounterAttack(player);
                            }

                            std::cout << std::endl; // 개행
                        }
                    }

                    // 스킬 버튼
                    if (button_skill.getGlobalBounds().contains(mousePos)) {
                        if (player.IsAlive() == true && enemy.IsAlive() == true) {
                            if (player.Skill(enemy) == true) {
                                // 스킬 성공하면 반격 없음
                            }
                        }

                        std::cout << std::endl; // 개행
                    }

                    // 힐 버튼
                    if (button_heal.getGlobalBounds().contains(mousePos)) {
                        if (player.IsAlive() == true) {
                            player.Heal(30);
                            player.RestoreMana(20);

                            if (enemy.IsAlive() == true) {
                                enemy.CounterAttack(player);
                            }
                        }

                        std::cout << std::endl; // 개행
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));

        player.Draw(window);
        enemy.Draw(window);

        window.draw(button_attack);
        window.draw(button_skill);
        window.draw(button_heal);
        window.draw(text_attack);
        window.draw(text_skill);
        window.draw(text_heal);

        window.display();
    }

    return 0;
}

/*
- Character가 기초 클래스로 바뀜:
    - 이제 Player, Enemy가 상속받음
    - 공통 기능은 Character에, 특수 기능은 각 클래스에

- 캡슐화(Encapsulation) 강화:
    - mHealth, mMana가 protected로 변경
    - 외부에서 직접 접근 불가, TakeDamage(), Heal() 같은 함수로만 접근

- 상속 (Inheritance) 활용:
    - Status -> Health, Mana
    - Character -> Player, Enemy

- 불변성(Invariance) 유지:
    - TakeDamage()는 반드시 0 체크, OnDeath() 호출
    - Heal()은 반드시 최대치 체크
    - 실수로라도 값 변경을 할 수 없음!

- 구현 은닉(Implementation Hiding) 활용:
    - UpdateBar()과 같이 외부에서 건드려선 안될 코드는 숨기기

- 다형성(Polymorphism) 활용:
    - OnDeath()가 각 클래스마다 다름 (override)
    - Player 죽으면 "게임 오버", Enemy 죽으면 "승리"
    - Player: Skill() (마나 소모 쌘공격)
    - Enemy: CounterAttack() (반격)

4. 조합(Composition) 활용:
   - Character가 Health, Mana를 자료형으로서 "가짐"

🤔 생각해보기:
1. 왜 mHealth, mMana를 protected로 바꿨을까?
2. Player와 Enemy의 OnDeath()가 다른 이유는?
3. 만약 Stamina를 추가한다면?
*/