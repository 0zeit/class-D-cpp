#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

// 이름공간(Namespace)은 코드를 그룹화하고 이름 충돌(Name Collision)을 방지
// 예: 만약 lib1, lib2 두 라이브러리에 모두 "Button" 이라는 클래스가 있으면?
//      -> lib1::Button, lib2::Button 으로 구분 가능!
namespace lesson3 {

    // 클래스는 우리가 원하는 정보들의 모임.
    // public 은 접근 제어문, lesson 5 에서 자세하게 다룰 예정
    class ButtonBrushColor {
    public:
        // 이 클래스가 필요로하는 자료들을 담기 위한 변수들
        // 이름은 아무렇게 지어도 되지만, 선생님은 항상 m을 앞에 붙임(클래스에 소속된 변수들을 "멤버 변수"라고 부르기때문!)
        sf::RectangleShape mButton;
        sf::Color          mButtonColor;
        bool               mIsSelected;

        // ButtonBrushColor 클래스의 생성자(Constructor)
        // ButtonBrushColor 의 객체(Object)를 생성할 때 마다 이 함수가 호출됨(클래스 이름과 함수 이름이 똑같아야 함)
        // 생성자는 클래스의 객체를 만들때 사용되기에 따로 자료형을 필요로 하지않음, 클래스 스스로가 하나의 자료형!
        // 그렇기에 생성자에는 주로 객체를 어떻게 만들것인지를 적어 내려감
        ButtonBrushColor(float x, float y, sf::Color color) {
            mButton.setSize({50.0f, 50.0f});
            mButton.setPosition({x, y});
            mButton.setFillColor(color);
            mButton.setOutlineThickness(2.0f);
            mButton.setOutlineColor(sf::Color::White);

            mButtonColor = color;
            mIsSelected  = false;
        }

        // Getter(데이터 받아오기)/Setter(데이터 설정하기) 구간
        // 현재는 단순히 값을 반환/설정만 하지만, 나중에 이것저것 기능을 추가할 수 있음
        sf::Color GetColor() {
            return mButtonColor;
        }

        bool IsClicked(sf::Vector2f mouse_pos) {
            // getGlobalBounds는 SFML 내에 준비된 함수, 마우스 위치가 RectangleShape 안에 있는지 확인
            return mButton.getGlobalBounds().contains(mouse_pos);
        }

        void SetSelected(bool selected) {
            mIsSelected = selected;

            // if (selected) 와 동일
            // 하지만 실무/실전에서는 동료들도 자신의 코드를 보기때문에, 이 코드가 무엇을 하는지 코드 스스로 설명할 수 있다면 되면 최고!(이를 명시성 이라고 함)
            if (selected == true) {
                mButton.setOutlineThickness(5.0f);
            }
            else {
                mButton.setOutlineThickness(2.0f);
            }
        }

        // 다른 잡다한 함수들
        void Draw(sf::RenderWindow& window) {
            window.draw(mButton);
        }
    };

    class ButtonBrushSize {
    public:
        sf::RectangleShape mButton;
        sf::CircleShape    mPreview;
        float              mBrushSize;
        bool               mIsSelected;

        ButtonBrushSize(float x, float y, float size) {
            mButton.setSize({50.0f, 50.0f});
            mButton.setPosition({x, y});
            mButton.setFillColor(sf::Color(100, 100, 100));
            mButton.setOutlineThickness(2.0f);
            mButton.setOutlineColor(sf::Color::White);

            mPreview.setRadius(size);
            mPreview.setPosition({x + 25.0f - size, y + 25.0f - size});
            mPreview.setFillColor(sf::Color::Transparent);
            mPreview.setOutlineColor(sf::Color::Black);
            mPreview.setOutlineThickness(1.0f);

            mBrushSize  = size;
            mIsSelected = false;
        }

        // Getter(데이터 받아오기)/Setter(데이터 설정하기) 구간
        float GetSize() {
            return mBrushSize;
        }

        bool IsClicked(sf::Vector2f mouse_pos) {
            return mButton.getGlobalBounds().contains(mouse_pos);
        }

        void SetSelected(bool selected) {
            mIsSelected = selected;

            if (selected == true) {
                mButton.setOutlineThickness(5.0f);
            }
            else {
                mButton.setOutlineThickness(2.0f);
            }
        }

        // 다른 잡다한 함수들
        void Draw(sf::RenderWindow& window) {
            window.draw(mButton);
            window.draw(mPreview);
        }
    };
} // namespace lesson3

/*
두 클래스(ButtonBrushColor, ButtonBrushSize)들의 공통점이 많이보인다.
"코드 중복(Code Duplication)"을 해결하기 위해 어떤 방법이 있을까? 🤔 생각해보자.
*/

int main() {
    // using namespace 를 활용하면 이름공간을 매번 써야하는 번거로움을 생략 가능!
    // ⚠️ 하지만 남용은 금물, 특히 C++ 의 표준인 std 이름공간 생략은 입문자들이 자주 저지르는 큰 실수!
    using namespace lesson3;

    // sf::RenderWindow window(sf::VideoMode({1000, 700}), "Mini Paint"); 와 동일, RenderWindow 클래스의 생성자 호출
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1000, 700}), "Mini Paint");
    window.setFramerateLimit(100);

    sf::RectangleShape canvas;
    canvas.setSize({800.0f, 700.0f});
    canvas.setPosition({0.0f, 0.0f});
    canvas.setFillColor(sf::Color::White);

    std::vector<sf::CircleShape> drawn_circles;

    sf::Color color_current = sf::Color::Black;
    float     size_current  = 5.0f;

    std::vector<ButtonBrushColor> buttons_color;
    buttons_color.push_back(ButtonBrushColor(820.0f, 50.0f, sf::Color::Black));
    buttons_color.push_back(ButtonBrushColor(880.0f, 50.0f, sf::Color::Red));
    buttons_color.push_back(ButtonBrushColor(820.0f, 110.0f, sf::Color::Green));
    buttons_color.push_back(ButtonBrushColor(880.0f, 110.0f, sf::Color::Blue));
    buttons_color.push_back(ButtonBrushColor(820.0f, 170.0f, sf::Color::Yellow));
    buttons_color.push_back(ButtonBrushColor(880.0f, 170.0f, sf::Color::Magenta));
    buttons_color[0].SetSelected(true);

    std::vector<ButtonBrushSize> buttons_size;
    buttons_size.push_back(ButtonBrushSize(820.0f, 300.0f, 3.0f));
    buttons_size.push_back(ButtonBrushSize(880.0f, 300.0f, 5.0f));
    buttons_size.push_back(ButtonBrushSize(820.0f, 360.0f, 10.0f));
    buttons_size[1].SetSelected(true);

    // ButtonBrushColor button_erase(820.0f, 500.0f, sf::Color::White); 와 동일, ButtonBrushColor 클래스의 생성자 호출
    // using namespace 로 이름공간을 생략했기 때문에 바로 사용가능, 원래라면 lesson3::ButtonBrushColor
    ButtonBrushColor button_erase = ButtonBrushColor(820.0f, 500.0f, sf::Color::White);

    sf::RectangleShape button_clear;
    button_clear.setSize({110.0f, 50.0f});
    button_clear.setPosition({820.0f, 600.0f});
    button_clear.setFillColor(sf::Color(200, 50, 50));
    button_clear.setOutlineThickness(2.0f);
    button_clear.setOutlineColor(sf::Color::White);

    // 이와 같은 "확인용" bool 형 변수를 주로 "플래그(Flag)" 라고 부름
    bool is_drawing = false;
    // 보간(Interpolation, 補間. 사이사이 채우기 라는 뜻)
    bool is_using_interpolation = true;

    sf::Vector2f mouse_pos_prev;
    bool         has_pos_prev = false;

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
                    sf::Vector2f mouse_pos = window.mapPixelToCoords(mouse_pressed->position);

                    for (size_t i = 0; i < buttons_color.size(); ++i) {
                        if (buttons_color[i].IsClicked(mouse_pos) == true) {

                            // C++ 에선 std::vector 로 동적 배열을 만들고 다음과 같이 for 문을 이용해
                            // 동적 배열 안에 있는 요소들을 하나씩 빼와서 사용가능
                            for (auto& button : buttons_color) {
                                button.SetSelected(false);
                            }

                            button_erase.SetSelected(false);
                            buttons_color[i].SetSelected(true);

                            color_current = buttons_color[i].GetColor();
                        }
                    }

                    for (size_t i = 0; i < buttons_size.size(); ++i) {
                        if (buttons_size[i].IsClicked(mouse_pos) == true) {
                            for (auto& button : buttons_size) {
                                button.SetSelected(false);
                            }

                            buttons_size[i].SetSelected(true);

                            size_current = buttons_size[i].GetSize();
                        }
                    }

                    if (button_erase.IsClicked(mouse_pos) == true) {
                        for (auto& button : buttons_color) {
                            button.SetSelected(false);
                        }

                        button_erase.SetSelected(true);

                        color_current = sf::Color::White;
                    }

                    if (button_clear.getGlobalBounds().contains(mouse_pos) == true) {
                        drawn_circles.clear();
                    }

                    if (canvas.getGlobalBounds().contains(mouse_pos) == true) {
                        is_drawing = true;
                    }
                }
            }

            // 마우스 클릭을 땠을때 발현되는 부분
            // 🤔 이 부분은 왜 있을까? 생각해보자!
            if (event->is<sf::Event::MouseButtonReleased>()) {
                is_drawing   = false;
                has_pos_prev = false;
            }
        }

        if (is_drawing == true) {
            sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // 캔버스(그리는 곳) 안에 마우스가 있으면
            if (canvas.getGlobalBounds().contains(mouse_pos) == true) {

                // 보간 기능이 켜져 있으면
                if (is_using_interpolation == true) {

                    // 마우스의 이전 위치가 있으면
                    if (has_pos_prev == true) {
                        float dx       = mouse_pos.x - mouse_pos_prev.x;
                        float dy       = mouse_pos.y - mouse_pos_prev.y;
                        float distance = std::sqrt(dx * dx + dy * dy);
                        int   steps    = static_cast<int>(distance / (size_current * 0.5f));

                        for (int i = 0; i <= steps; ++i) {

                            // 이 부분은 삼항연산자로 대체 가능
                            // float t = (0 < steps) ? static_cast<float>(i) / steps : 0.f;
                            float t;

                            if (0 < steps) {
                                t = static_cast<float>(i) / steps;
                            }
                            else {
                                t = 0.0f;
                            }

                            float interpolated_x = mouse_pos_prev.x + dx * t;
                            float interpolated_y = mouse_pos_prev.y + dy * t;

                            sf::CircleShape circle(size_current);
                            circle.setPosition({interpolated_x - size_current, interpolated_y - size_current});
                            circle.setFillColor(color_current);

                            drawn_circles.push_back(circle);
                        }
                    }
                    // 마우스의 이전 위치가 없으면
                    else {
                        sf::CircleShape circle = sf::CircleShape(size_current);
                        circle.setPosition({mouse_pos.x - size_current, mouse_pos.y - size_current});
                        circle.setFillColor(color_current);

                        drawn_circles.push_back(circle);
                    }

                    mouse_pos_prev = mouse_pos;
                    has_pos_prev   = true;
                }
                // 보간 기능이 꺼져 있으면
                else {
                    sf::CircleShape circle = sf::CircleShape(size_current);
                    circle.setPosition({mouse_pos.x - size_current, mouse_pos.y - size_current});
                    circle.setFillColor(color_current);

                    drawn_circles.push_back(circle);
                }
            }
            // 🤔 이 부분은 왜 있을까? 한번 생각해보자!
            else {
                has_pos_prev = false;
            }
        }

        window.clear(sf::Color(50, 50, 50));
        window.draw(canvas);

        for (const auto& circle : drawn_circles) {
            window.draw(circle);
        }

        for (auto& button : buttons_color) {
            button.Draw(window);
        }

        for (auto& button : buttons_size) {
            button.Draw(window);
        }

        button_erase.Draw(window);

        window.draw(button_clear);
        window.display();
    }

    return 0;
}