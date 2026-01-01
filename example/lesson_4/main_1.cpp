#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

// 이 코드는 심각한 버그를 포함하고 있다. 어디가 문제일까? 🤔
namespace lesson4 {
    class Character {
    public:
        // 캐릭터 스탯(Status, 능력치)
        int mHealth;    // 체력
        int mHealthMax; // 최대 체력
        int mMana;      // 마나
        int mManaMax;   // 최대 마나

        // 시각적 요소들
        sf::CircleShape    mCharacter;   // 캐릭터
        sf::RectangleShape mHealthBarBG; // 체력바 배경
        sf::RectangleShape mHealthBarFG; // 체력바
        sf::RectangleShape mManaBarBG;   // 마나바 배경
        sf::RectangleShape mManaBarFG;   // 마나바
        sf::Vector2f       mPosition;    // 캐릭터 위치

        Character(float pos_x, float pos_y, int hp, int mp, sf::Color color) {
            mPosition = {pos_x, pos_y};
            mHealth = mHealthMax = hp;
            mMana = mManaMax = mp;

            sf::Vector2f bar_hp_size = {200.0f, 30.0f};
            sf::Vector2f bar_mp_size = {200.0f, 20.0f};

            // 캐릭터 설정
            mCharacter.setRadius(25.0f);
            mCharacter.setPosition({pos_x - 60.0f, pos_y});
            mCharacter.setFillColor(color);
            mCharacter.setOutlineColor(sf::Color::White);
            mCharacter.setOutlineThickness(2.0f);

            // 체력바 설정
            mHealthBarBG.setSize(bar_hp_size);
            mHealthBarBG.setPosition({pos_x, pos_y});
            mHealthBarBG.setFillColor(sf::Color(50, 50, 50));

            mHealthBarFG.setSize(bar_hp_size);
            mHealthBarFG.setPosition({pos_x, pos_y});
            mHealthBarFG.setFillColor(sf::Color::Green);

            // 마나바 설정
            mManaBarBG.setSize(bar_mp_size);
            mManaBarBG.setPosition({pos_x, pos_y + 35.0f});
            mManaBarBG.setFillColor(sf::Color(50, 50, 50));

            mManaBarFG.setSize(bar_mp_size);
            mManaBarFG.setPosition({pos_x, pos_y + 35.0f});
            mManaBarFG.setFillColor(sf::Color::Blue);
        }

        void Draw(sf::RenderWindow& window) {
            window.draw(mCharacter);
            window.draw(mHealthBarBG);
            window.draw(mHealthBarFG);
            window.draw(mManaBarBG);
            window.draw(mManaBarFG);
        }
    };
} // namespace lesson4

int main() {
    using namespace lesson4;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Lesson 4 - Mini RPG ver.1");
    window.setFramerateLimit(120);

    // 폰트 로딩
    sf::Font font("./res/font.ttf");

    Character player(100.0f, 400.0f, 100, 50, sf::Color::Green);
    Character enemy(400.0f, 400.0f, 80, 30, sf::Color::Red);

    // 간단한 버튼들, 한글 텍스트는 앞에 L을 써야함(텍스트 포맷)
    sf::Text           text_attack(font, L"공격", 25);
    sf::Text           text_heal(font, L"회복", 25);
    sf::RectangleShape button_attack({50.0f, 50.0f});
    sf::RectangleShape button_heal({50.0f, 50.0f});

    text_attack.setPosition({50.0f, 100.0f});
    text_attack.setFillColor(sf::Color::Black);
    button_attack.setPosition({50.0f, 100.0f});
    button_attack.setFillColor(sf::Color::Red);

    text_heal.setPosition({50.0f, 160.0f});
    text_heal.setFillColor(sf::Color::Black);
    button_heal.setPosition({50.0f, 160.0f});
    button_heal.setFillColor(sf::Color::Green);

    while (window.isOpen() == true) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mousePressed->position);

                    // 공격 버튼 클릭
                    if (button_attack.getGlobalBounds().contains(mousePos)) {
                        // . 으로 만들어진 객체가 소유한 public 멤버들에게 접근 가능
                        enemy.mHealth -= 20;

                        std::cout << "Enemy health: " << enemy.mHealth << std::endl;
                    }

                    // 힐 버튼 클릭
                    if (button_heal.getGlobalBounds().contains(mousePos)) {
                        player.mHealth += 30;

                        std::cout << "Player health: " << player.mHealth << "/" << player.mHealthMax << std::endl;
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));

        player.Draw(window);
        enemy.Draw(window);

        window.draw(button_attack);
        window.draw(button_heal);
        window.draw(text_attack);
        window.draw(text_heal);

        window.display();
    }

    return 0;
}

/*
코드를 실행해서 문제점들을 찾아서 나열해 보자!
...
어떻게 해결 할 수 있을까? 🤔
*/