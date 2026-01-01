#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

namespace lesson4 {
    // 체력, 마나, 스태미나 등 여러 스탯 바의 공통 기능을 담는 클래스
    class Status {
    protected:        // 상속된 클래스(Child Class, 자식 클래스)에서 접근 가능
        int mCurrent; // 현재 값
        int mMax;     // 최대 값

        sf::RectangleShape mBarBg; // 배경
        sf::RectangleShape mBarFg; // 전경

        // 바 길이 조정하기
        void UpdateBar() {
            float        ratio         = static_cast<float>(mCurrent) / static_cast<float>(mMax);
            sf::Vector2f size_original = mBarBg.getSize();
            sf::Vector2f size_new      = {size_original.x * ratio, size_original.y};

            mBarFg.setSize(size_new);
        }

    public: // 어디서든 접근 가능
        Status(float x, float y, float width, float height, int max_value, sf::Color color) {
            mCurrent = mMax = max_value;

            mBarBg.setSize({width, height});
            mBarBg.setPosition({x, y});
            mBarBg.setFillColor(sf::Color(50, 50, 50));

            mBarFg.setSize({width, height});
            mBarFg.setPosition({x, y});
            mBarFg.setFillColor(color);
        }

        // 가상(virtual) 소멸자, 상속 사용 시 필수!
        // 소멸자(Destructor)는 생상자와 반대되는 개념, 데이터를 메모리에서 지워줌
        // virtual 을 설정한 모든 함수들은 자식 클래스들이 재정의(override) 해서 내용을 바꿀 수 있음
        // default 는 컴파일러에게 가능한 가장 기본적인 소멸자를 자동으로 생성해 달라는 뜻
        virtual ~Status() = default;

        // Getter(protected 에 가려진 값 받아오기)
        int GetCurrent() const {
            return mCurrent;
        }

        int GetMax() const {
            return mMax;
        }

        bool IsDepleted() const { // 고갈 여부
            return mCurrent == 0;
        }

        void Decrease(int amount) { // 값 감소 (데미지, 마나 소모 등)
            mCurrent -= amount;

            // 불변성(invariance) 유지, 0 미만으로 못내려가게!
            if (mCurrent < 0) {
                mCurrent = 0;
            }

            UpdateBar(); // 자동으로 바 업데이트
        }

        void Increase(int amount) { // 값 증가 (힐, 마나 회복 등)
            mCurrent += amount;

            // 불변성(invariance) 유지, 최대치 초과를 못하게!
            if (mCurrent > mMax) {
                mCurrent = mMax;
            }

            UpdateBar(); // 자동으로 바 업데이트!
        }

        // 그리기
        virtual void Draw(sf::RenderWindow& window) {
            window.draw(mBarBg);
            window.draw(mBarFg);
        }
    };

    // Status 를 상속해 체력 만들기
    class Health : public Status {
    public:
        Health(float x, float y, int max_hp) : Status(x, y, 200.0f, 30.0f, max_hp, sf::Color::Green) { // Status 생성자 호출
        }

        void Draw(sf::RenderWindow& window) override { // override(재정의) 키워드에 주목!
            if (IsDepleted() == true) {                // 체력이 고갈되면 색상 변경
                mBarFg.setFillColor(sf::Color::Red);
            }
            else {
                mBarFg.setFillColor(sf::Color::Green);
            }

            Status::Draw(window); // 부모 클래스 Draw 호출
        }
    };

    // Status 를 상속해 마나 만들기
    class Mana : public Status {
    public:
        Mana(float x, float y, int max_mp) : Status(x, y, 200.0f, 20.0f, max_mp, sf::Color::Blue) { // Status 생성자 호출
        }

        // 마나 소모 가능 여부 체크, 마나만 가지고 있는 함수!
        bool CanUse(int cost) const {
            return mCurrent >= cost;
        }

        void Draw(sf::RenderWindow& window) override { // override(재정의) 키워드에 주목!
            if (IsDepleted() == true) {                // 체력이 고갈되면 색상 변경
                mBarFg.setFillColor(sf::Color::Red);
            }
            else {
                mBarFg.setFillColor(sf::Color::Blue);
            }

            Status::Draw(window); // 부모 클래스 Draw 호출
        }
    };

    // 캐릭터 안에서 체력과 마나 활용해보기
    class Character {
    public:
        sf::CircleShape mCharacter; // 캐릭터 모양
        sf::Vector2f    mPosition;  // 캐릭터 위치
        Health          mHealth;    // 캐릭터 체력
        Mana            mMana;      // 캐릭터 마나

        Character(float pos_x, float pos_y, int max_hp, int max_mp, sf::Color color) : mHealth(pos_x, pos_y, max_hp),
                                                                                       mMana(pos_x, pos_y + 35.0f, max_mp) {
            mPosition = {pos_x, pos_y};

            // 캐릭터 설정
            mCharacter.setRadius(25.0f);
            mCharacter.setPosition({pos_x - 60.0f, pos_y});
            mCharacter.setFillColor(color);
            mCharacter.setOutlineColor(sf::Color::White);
            mCharacter.setOutlineThickness(2.0f);
        }

        void Draw(sf::RenderWindow& window) {
            window.draw(mCharacter);

            mHealth.Draw(window);
            mMana.Draw(window);
        }
    };
} // namespace lesson4

int main() {
    using namespace lesson4;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Lesson 4 - Mini RPG ver.2");
    window.setFramerateLimit(60);

    sf::Font font("./res/font.ttf");

    Character player(100.0f, 400.0f, 100, 50, sf::Color::Green);
    Character enemy(400.0f, 400.0f, 80, 30, sf::Color::Red);

    // 간단한 버튼들, 한글 텍스트는 앞에 L을 써야함(텍스트 포맷)
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
                        // 이제 바도 자동으로 줄어듦!
                        enemy.mHealth.Decrease(20);

                        std::cout << "적 HP: " << enemy.mHealth.GetCurrent() << "/" << enemy.mHealth.GetMax() << std::endl;
                    }

                    // 힐 버튼
                    if (button_heal.getGlobalBounds().contains(mousePos)) {
                        // 최대치 자동 체크!
                        player.mHealth.Increase(30);

                        std::cout << "플레이어 HP: " << player.mHealth.GetCurrent() << "/" << player.mHealth.GetMax() << std::endl;
                    }

                    // 스킬 버튼
                    if (button_skill.getGlobalBounds().contains(mousePos)) {
                        const int MANA_COST = 20;

                        // 마나 체크 후 사용!
                        if (player.mMana.CanUse(MANA_COST) == true) {
                            player.mMana.Decrease(MANA_COST);
                            enemy.mHealth.Decrease(40);

                            std::cout << "스킬 사용! 마나: " << player.mMana.GetCurrent() << std::endl;
                        }
                        else {
                            std::cout << "마나 부족!" << std::endl;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));

        player.Draw(window);
        enemy.Draw(window);

        window.draw(button_attack);
        window.draw(button_heal);
        window.draw(button_skill);
        window.draw(text_attack);
        window.draw(text_heal);
        window.draw(text_skill);

        window.display();
    }

    return 0;
}

/*
첫번째 코드(main_1)에서 개선된 점을 찾아서 나열해보자! ✅
*/