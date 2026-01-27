#include <iostream>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

namespace lesson6 {
    class Shape {
    protected:
        sf::Vector2f mPosition;
        sf::Color    mColor;

    public:
        Shape(float x, float y, sf::Color color) : mPosition(x, y), mColor(color) {
        }

        virtual ~Shape() = default;

        sf::Vector2f GetPosition() const {
            return mPosition;
        }

        virtual void SetPosition(float x, float y) {
            mPosition = {x, y};
        }

        virtual void        Draw(sf::RenderWindow& window) = 0;
        virtual std::string GetType() const                = 0;
    };

    class Circle : public Shape {
    private:
        float           mRadius;
        sf::CircleShape mCircle;

    public:
        Circle(float x, float y, float radius, sf::Color color) : Shape(x, y, color), mRadius(radius) {
            mCircle.setRadius(radius);
            mCircle.setPosition(mPosition);
            mCircle.setFillColor(mColor);
            mCircle.setOutlineThickness(2.0f);
            mCircle.setOutlineColor(sf::Color::White);

            std::cout << "Circle 생성" << std::endl;
        }

        ~Circle() override {
            std::cout << "Circle 소멸" << std::endl;
        }

        std::string GetType() const override {
            return "원";
        }

        void SetPosition(float x, float y) override {
            mPosition = {x, y};

            mCircle.setPosition(mPosition);
        }

        void Draw(sf::RenderWindow& window) override {
            window.draw(mCircle);
        }
    };

    class Rectangle : public Shape {
    private:
        float              mWidth, mHeight;
        sf::RectangleShape mRect;

    public:
        Rectangle(float x, float y, float w, float h, sf::Color color) : Shape(x, y, color), mWidth(w), mHeight(h) {
            mRect.setSize({w, h});
            mRect.setPosition(mPosition);
            mRect.setFillColor(mColor);
            mRect.setOutlineThickness(2.0f);
            mRect.setOutlineColor(sf::Color::White);

            std::cout << "Rectangle 생성" << std::endl;
        }

        ~Rectangle() override {
            std::cout << "Rectangle 소멸" << std::endl;
        }

        std::string GetType() const override {
            return "사각형";
        }

        void SetPosition(float x, float y) override {
            mPosition = {x, y};
            mRect.setPosition(mPosition);
        }

        void Draw(sf::RenderWindow& window) override {
            window.draw(mRect);
        }
    };

    class Triangle : public Shape {
    private:
        float           mSize;
        sf::CircleShape mTriangle;

    public:
        Triangle(float x, float y, float size, sf::Color color) : Shape(x, y, color), mSize(size) {
            mTriangle.setRadius(size);
            mTriangle.setPointCount(3);
            mTriangle.setPosition(mPosition);
            mTriangle.setFillColor(mColor);
            mTriangle.setOutlineThickness(2.0f);
            mTriangle.setOutlineColor(sf::Color::White);

            std::cout << "Triangle 생성" << std::endl;
        }

        std::string GetType() const override {
            return "삼각형";
        }

        void SetPosition(float x, float y) override {
            mPosition = {x, y};
            mTriangle.setPosition(mPosition);
        }

        ~Triangle() override {
            std::cout << "Triangle 소멸" << std::endl;
        }

        void Draw(sf::RenderWindow& window) override {
            window.draw(mTriangle);
        }
    };

    class ShapeManager {
    private:
        std::vector<std::unique_ptr<Shape>> mShapes;

    public:
        size_t GetShapeCount() const {
            return mShapes.size();
        }

        void AddCircle(float x, float y, float radius, sf::Color color) {
            mShapes.push_back(std::make_unique<Circle>(x, y, radius, color));
        }

        void AddRectangle(float x, float y, float w, float h, sf::Color color) {
            mShapes.push_back(std::make_unique<Rectangle>(x, y, w, h, color));
        }

        void AddTriangle(float x, float y, float size, sf::Color color) {
            mShapes.push_back(std::make_unique<Triangle>(x, y, size, color));
        }

        void RemoveLastShape() {
            if (mShapes.empty() == false) {
                std::cout << "\n"
                          << mShapes.back()->GetType() << " 삭제"
                          << std::endl;

                mShapes.pop_back(); // 자동으로 메모리 해제
            }
        }

        void Clear() {
            std::cout << "\n모든 도형 삭제" << std::endl;
            mShapes.clear(); // 자동으로 전부 해제
        }

        void DrawAll(sf::RenderWindow& window) {
            for (const auto& shape : mShapes) {
                shape->Draw(window); // 다형성(Polymorphism)
            }
        }

        // 마지막 도형 이동 (예시)
        void MoveLastShape(float dx, float dy) {
            if (mShapes.empty() == false) {
                sf::Vector2f pos = mShapes.back()->GetPosition();
                mShapes.back()->SetPosition(pos.x + dx, pos.y + dy);
            }
        }
    };

} // namespace lesson6

int main() {
    using namespace lesson6;

    sf::RenderWindow window(sf::VideoMode({1000, 700}), "Lesson 6 - Shape Drawer");
    window.setFramerateLimit(60);

    sf::Font font("./res/font.ttf");

    ShapeManager manager;

    struct Button {
        sf::RectangleShape shape;
        sf::Text           text;
        std::string        label;
    };

    std::vector<Button> buttons;

    auto create_button = [&](float x, float y, const std::string& label, sf::Color color) { // [](){} 으로 함수도 만들 수 있음!
        Button btn{
            .shape = []() {
                sf::RectangleShape s;
                s.setSize({150.0f, 50.0f});
                s.setOutlineThickness(2.0f);
                s.setOutlineColor(sf::Color::White);

                return s;
            }(),

            .text  = sf::Text(font, sf::String::fromUtf8(label.begin(), label.end()), 20),
            .label = label};

        btn.shape.setPosition({x, y});
        btn.shape.setFillColor(color);
        btn.text.setPosition({x + 10.0f, y + 12.0f});
        btn.text.setFillColor(sf::Color::White);

        buttons.push_back(btn);
    };

    create_button(20.0f, 20.0f, "원 추가", sf::Color(200, 50, 50));
    create_button(180.0f, 20.0f, "사각형 추가", sf::Color(50, 50, 200));
    create_button(340.0f, 20.0f, "삼각형 추가", sf::Color(50, 200, 50));
    create_button(500.0f, 20.0f, "마지막 삭제", sf::Color(150, 150, 50));
    create_button(660.0f, 20.0f, "전체 삭제", sf::Color(100, 100, 100));

    sf::Text text_info(font, L"", 18);
    text_info.setPosition({20.0f, 650.0f});
    text_info.setFillColor(sf::Color::White);

    auto color_random = []() {
        return sf::Color(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);
    };

    while (window.isOpen() == true) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mouse_pressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse_pressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f pos_mouse = window.mapPixelToCoords(mouse_pressed->position);

                    for (const auto& btn : buttons) {
                        if (btn.shape.getGlobalBounds().contains(pos_mouse)) {
                            if (btn.label == "원 추가") {
                                float x = rand() % 700 + 150;
                                float y = rand() % 400 + 150;
                                float r = rand() % 40 + 20;
                                manager.AddCircle(x, y, r, color_random());
                            }
                            else if (btn.label == "사각형 추가") {
                                float x = rand() % 700 + 150;
                                float y = rand() % 400 + 150;
                                float w = rand() % 80 + 40;
                                float h = rand() % 80 + 40;
                                manager.AddRectangle(x, y, w, h, color_random());
                            }
                            else if (btn.label == "삼각형 추가") {
                                float x = rand() % 700 + 150;
                                float y = rand() % 400 + 150;
                                float s = rand() % 50 + 30;
                                manager.AddTriangle(x, y, s, color_random());
                            }
                            else if (btn.label == "마지막 삭제") {
                                manager.RemoveLastShape();
                            }
                            else if (btn.label == "전체 삭제") {
                                manager.Clear();
                            }
                        }
                    }
                }
            }

            if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
                float moveSpeed = 10.0f;

                if (key_pressed->code == sf::Keyboard::Key::Left) {
                    manager.MoveLastShape(-moveSpeed, 0);
                }
                if (key_pressed->code == sf::Keyboard::Key::Right) {
                    manager.MoveLastShape(moveSpeed, 0);
                }
                if (key_pressed->code == sf::Keyboard::Key::Up) {
                    manager.MoveLastShape(0, -moveSpeed);
                }
                if (key_pressed->code == sf::Keyboard::Key::Down) {
                    manager.MoveLastShape(0, moveSpeed);
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));
        manager.DrawAll(window);

        for (const auto& btn : buttons) {
            window.draw(btn.shape);
            window.draw(btn.text);
        }

        std::string info = "도형 개수: " + std::to_string(manager.GetShapeCount()) +
                           "  |  화살표 키: 마지막 도형 이동";
        text_info.setString(sf::String::fromUtf8(info.begin(), info.end()));
        window.draw(text_info);

        window.display();
    }

    std::cout << "\n프로그램 종료 - 모든 도형 자동 정리됨" << std::endl;

    return 0;
}

/*
🤔 생각해보기:

1. unique_ptr (스마트 포인터, C++11):
    - std::unique_ptr<Shape> : Shape의 "유일한 소유자"
    - 자동 메모리 관리 (delete 불필요!)
    - 벡터에서 pop_back()하면 자동 소멸

2. make_unique:
    - std::make_unique<Circle>(...) : 안전한 생성
    - new 대신 사용

3. 다형성 (Polymorphism):
    - Shape* → Circle, Rectangle, Triangle
    - shape->Draw() : 각자 다른 Draw() 호출

4. 메모리 안전성:
    - 예외 발생해도 자동 정리
    - 메모리 누수 걱정 없음
    - 누가 소유하는지 명확 (unique = 유일한 소유자)

5. shared_ptr은 언제 쓸까?
    → 여러 곳에서 같은 객체를 공유할 때

Raw Pointer와 비교:
    - Shape* shape = new Circle(...);
    - delete shape;  // 필수! 깜빡하면 메모리 누수
*/