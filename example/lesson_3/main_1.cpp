#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1000, 700}), "Mini Paint");
    window.setFramerateLimit(100);

    // 메인 프로그램 루프 (윈도우가 열려있는 동안 반복)
    while (window.isOpen() == true) {

        // 이벤트 루프 (키보드, 마우스등 외부에서 들어오는 입력을 계속 감시)
        while (const auto event = window.pollEvent()) {

            // SFML의 프로그램이 종료되면 SFML 창도 닫는 기능. SFML 나름대로의 기본 패턴
            // 꺾쇠 괄호 <> 는 C++ 에 있어서 템플릿(Template) 이라하며 이후 lesson 8 부터 자세하게 다룰 예정
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // SFML의 프로그램에서 마우스 클릭이 발생하면 발현되는 구간, 똑같이 SFML 나름대로의 기본 패턴
            // --! ⚠️ 이 패턴은 C++ 버전 17, SFML 버전 3 부터만 가능 !--
            if (const auto* mouse_pressed = event->getIf<sf::Event::MouseButtonPressed>()) {

                // 마우스 클릭이 왼쪽 클릭이면
                if (mouse_pressed->button == sf::Mouse::Button::Left) {
                    // main_2.cpp 로...
                }
            }

            // 마우스 클릭을 땠을때 발현되는 부분
            if (event->is<sf::Event::MouseButtonReleased>()) {
                // main_2.cpp 로...
            }
        }

        window.clear(sf::Color(50, 50, 50));

        window.display();
    }

    return 0;
}