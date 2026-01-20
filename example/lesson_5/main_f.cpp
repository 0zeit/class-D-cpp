#include <cmath>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

namespace lesson5 {
    enum class OrderStatus {
        Pending,   // 접수
        Preparing, // 준비중
        Ready,     // 준비완료
        Delivered, // 전달완료
        Cancelled  // 취소
    };

    enum class PaymentMethod {
        Cash,    // 현금
        Card,    // 카드
        Transfer // 계좌이체
    };

    class Order {
    private:
        int           mOrderId;
        std::string   mCustomerName;
        OrderStatus   mOrderStatus;
        PaymentMethod mPaymentMethod;
        double        mTotalPrice;

    public:
        Order(int order_id, const std::string& customer_name, PaymentMethod payment_method, double price) : mOrderId(order_id),
                                                                                                            mCustomerName(customer_name),
                                                                                                            mOrderStatus(OrderStatus::Pending),
                                                                                                            mPaymentMethod(payment_method),
                                                                                                            mTotalPrice(price) {
        }

        int GetOrderId() const {
            return mOrderId;
        }

        std::string GetCustomerName() const {
            return mCustomerName;
        }

        OrderStatus GetStatus() const {
            return mOrderStatus;
        }

        double GetTotalPrice() const {
            return mTotalPrice;
        }

        void AdvanceStatus() {
            switch (mOrderStatus) {
                case OrderStatus::Pending:
                    mOrderStatus = OrderStatus::Preparing;
                    std::cout << "[주문 #" << mOrderId << "] 준비 시작!" << std::endl;
                    break;

                case OrderStatus::Preparing:
                    mOrderStatus = OrderStatus::Ready;
                    std::cout << "[주문 #" << mOrderId << "] 준비 완료!" << std::endl;
                    break;

                case OrderStatus::Ready:
                    mOrderStatus = OrderStatus::Delivered;
                    std::cout << "[주문 #" << mOrderId << "] 전달 완료!" << std::endl;
                    break;

                case OrderStatus::Delivered:
                    std::cout << "[주문 #" << mOrderId << "] 이미 전달 완료된 주문입니다!" << std::endl;
                    break;

                case OrderStatus::Cancelled:
                    std::cout << "[주문 #" << mOrderId << "] 취소된 주문입니다!" << std::endl;
                    break;
            }
        }

        void Cancel() {
            if (mOrderStatus == OrderStatus::Delivered) {
                std::cout << "[주문 #" << mOrderId << "] 이미 전달된 주문은 취소 불가!" << std::endl;
                return;
            }

            if (mOrderStatus == OrderStatus::Cancelled) {
                std::cout << "[주문 #" << mOrderId << "] 이미 취소된 주문입니다!" << std::endl;
                return;
            }

            mOrderStatus = OrderStatus::Cancelled;
            std::cout << "[주문 #" << mOrderId << "] 주문이 취소되었습니다." << std::endl;
        }

        std::string GetStatusName() const {
            switch (mOrderStatus) {
                case OrderStatus::Pending:
                    return "접수";

                case OrderStatus::Preparing:
                    return "준비중";

                case OrderStatus::Ready:
                    return "준비완료";

                case OrderStatus::Delivered:
                    return "전달완료";

                case OrderStatus::Cancelled:
                    return "취소됨";

                default:
                    return "알 수 없음";
            }
        }

        std::string GetPaymentName() const {
            switch (mPaymentMethod) {
                case PaymentMethod::Card:
                    return "카드";

                case PaymentMethod::Cash:
                    return "현금";

                case PaymentMethod::Transfer:
                    return "계좌이체";

                default:
                    return "알 수 없음";
            }
        }

        sf::Color GetStatusColor() const {
            switch (mOrderStatus) {
                case OrderStatus::Pending:
                    return sf::Color::Yellow;

                case OrderStatus::Preparing:
                    return sf::Color(255, 165, 0);

                case OrderStatus::Ready:
                    return sf::Color::Green;

                case OrderStatus::Delivered:
                    return sf::Color::Blue;

                case OrderStatus::Cancelled:
                    return sf::Color::Red;

                default:
                    return sf::Color::White;
            }
        }
    };

    class OrderManager {
    private:
        std::vector<Order> mOrders;
        int                mNextOrderId = 1001;

    public:
        void CreateOrder(const std::string& customer_name, PaymentMethod payment_method, double price) {
            mOrders.push_back(Order(mNextOrderId, customer_name, payment_method, price));

            std::cout << "\n=== 새 주문 등록 ===" << std::endl;
            std::cout << "주문번호: " << mNextOrderId << std::endl;
            std::cout << "고객명: " << customer_name << std::endl;
            std::cout << "결제: " << mOrders.back().GetPaymentName() << std::endl;
            std::cout << "금액: " << price << "원" << std::endl;
            std::cout << "==================\n"
                      << std::endl;

            mNextOrderId++;
        }

        std::vector<Order>& GetOrders() {
            return mOrders;
        }

        Order* FindOrder(int order_id) { // 포인터!
            for (auto& order : mOrders) {
                if (order.GetOrderId() == order_id) {
                    return &order;
                }
            }

            return nullptr;
        }

        int GetTotalOrders() const {
            return mOrders.size();
        }

        int GetActiveOrders() const {
            int count = 0;

            for (const auto& order : mOrders) {
                if ((order.GetStatus() != OrderStatus::Delivered) && (order.GetStatus() != OrderStatus::Cancelled)) {
                    count++;
                }
            }

            return count;
        }
    };
} // namespace lesson5

int main() {
    using namespace lesson5;

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1200, 800}), "Lesson 5 - Restaurant Order System");
    window.setFramerateLimit(60);

    sf::Font font = sf::Font("./res/font.ttf");

    OrderManager manager;

    sf::Text title(font, L"레스토랑 주문 관리 시스템", 30);
    title.setPosition({20.0f, 20.0f});
    title.setFillColor(sf::Color::White);

    struct PresetOrder {
        std::string   name;
        PaymentMethod payment;
        double        price;
    };

    std::vector<PresetOrder> presets = {
        {"AAA", PaymentMethod::Card, 15000},
        {"BBB", PaymentMethod::Cash, 20000},
        {"CCC", PaymentMethod::Transfer, 18000},
        {"DDD", PaymentMethod::Card, 25000}};

    std::vector<sf::RectangleShape> buttons_add;
    std::vector<sf::Text>           texts_add;

    for (size_t i = 0; i < presets.size(); ++i) {
        sf::RectangleShape button = sf::RectangleShape({180.0f, 50.0f});

        button.setPosition({20.0f + (i * 190.0f), 80.0f});
        button.setFillColor(sf::Color(100, 150, 100));
        button.setOutlineThickness(2.0f);
        button.setOutlineColor(sf::Color::White);
        buttons_add.push_back(button);

        std::string label_button = presets[i].name + "\n" + std::to_string((int)presets[i].price) + "원";
        sf::Text    text         = sf::Text(font, sf::String::fromUtf8(label_button.begin(), label_button.end()), 18);

        text.setPosition({40.0f + (i * 190.0f), 80.0f});
        text.setFillColor(sf::Color::Black);
        texts_add.push_back(text);
    }

    sf::RectangleShape bg_order_list({1160.0f, 600.0f});
    bg_order_list.setPosition({20.0f, 160.0f});
    bg_order_list.setFillColor(sf::Color(40, 40, 40));
    bg_order_list.setOutlineThickness(2.0f);
    bg_order_list.setOutlineColor(sf::Color::White);

    sf::Text text_stats(font, L"", 18);
    text_stats.setPosition({20.0f, 770.0f});
    text_stats.setFillColor(sf::Color::White);

    int order_id_selected = -1;

    while (window.isOpen() == true) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mouse_pressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse_pressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mouse_pos = window.mapPixelToCoords(mouse_pressed->position);

                    for (size_t i = 0; i < buttons_add.size(); ++i) {
                        if (buttons_add[i].getGlobalBounds().contains(mouse_pos)) {
                            manager.CreateOrder(presets[i].name, presets[i].payment, presets[i].price);
                        }
                    }

                    float offset_y = 170.0f;

                    for (auto& order : manager.GetOrders()) {
                        sf::FloatRect rect_order = sf::FloatRect({30.0f, offset_y}, {1140.0f, 70.0f});

                        if (rect_order.contains(mouse_pos)) {
                            order_id_selected = order.GetOrderId();

                            std::cout << "\n[주문 #" << order_id_selected << "] 선택됨" << std::endl;
                        }

                        offset_y += 80.0f;
                    }
                }
            }

            if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
                if (order_id_selected != -1) {
                    Order* order = manager.FindOrder(order_id_selected); // 포인터!

                    if (order != nullptr) { // 주문이 있는지 확인
                        if (key_pressed->code == sf::Keyboard::Key::Space) {
                            order->AdvanceStatus();
                        }

                        if (key_pressed->code == sf::Keyboard::Key::X) {
                            order->Cancel();
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(title);

        for (size_t i = 0; i < buttons_add.size(); ++i) {
            window.draw(buttons_add[i]);
            window.draw(texts_add[i]);
        }

        window.draw(bg_order_list);

        float offset_y = 170.0f;

        for (auto& order : manager.GetOrders()) {
            sf::RectangleShape card_order = sf::RectangleShape({1140.0f, 70.0f});

            card_order.setPosition({30.0f, offset_y});
            card_order.setFillColor(sf::Color(60, 60, 60));

            if (order.GetOrderId() == order_id_selected) {
                card_order.setOutlineThickness(3.0f);
                card_order.setOutlineColor(sf::Color::Cyan);
            }
            else {
                card_order.setOutlineThickness(1.0f);
                card_order.setOutlineColor(sf::Color(100, 100, 100));
            }

            window.draw(card_order);

            sf::RectangleShape box_status = sf::RectangleShape({20.0f, 70.0f});

            box_status.setPosition({30.0f, offset_y});
            box_status.setFillColor(order.GetStatusColor());
            window.draw(box_status);

            std::string orderInfo = "#" + std::to_string(order.GetOrderId()) +
                                    "  |  " + order.GetCustomerName() +
                                    "  |  " + order.GetStatusName() +
                                    "  |  " + order.GetPaymentName() +
                                    "  |  " + std::to_string((int)order.GetTotalPrice()) + "원";

            sf::Text text_info = sf::Text(font, sf::String::fromUtf8(orderInfo.begin(), orderInfo.end()), 18);

            text_info.setPosition({60.0f, offset_y + 25.0f});
            text_info.setFillColor(sf::Color::White);
            window.draw(text_info);

            offset_y += 80.0f;
        }

        std::string stats = "총 주문: " + std::to_string(manager.GetTotalOrders()) +
                            "  |  진행중: " + std::to_string(manager.GetActiveOrders()) +
                            "  |  조작: [클릭] 선택  [Space] 다음단계  [X] 취소";

        text_stats.setString(sf::String::fromUtf8(stats.begin(), stats.end()));
        window.draw(text_stats);

        if (manager.GetTotalOrders() == 0) {
            sf::Text text_guide(font, L"위 버튼을 클릭해서 주문을 추가하세요!", 24);

            text_guide.setPosition({400.0f, 400.0f});
            text_guide.setFillColor(sf::Color(150, 150, 150));
            window.draw(text_guide);
        }

        window.display();
    }

    return 0;
}

/*
이 코드에서 배운 개념:

1. enum class 활용: <-- 중요!!
   - OrderStatus: 주문 상태 관리
   - PaymentMethod: 결제 방식 구분
   - 각 enum에 따라 다른 동작 (switch)

2. 벡터 활용:
   - std::vector<Order>로 여러 주문 관리
   - 포인터 없이 값으로 저장

3. 주문 찾기:
   - FindOrder()로 특정 주문 접근
   - nullptr 체크 (포인터 맛보기)

4. 실무 패턴:
   - OrderManager로 주문 중앙 관리
   - 자동 ID 생성 (mNextOrderId++)

🤔 생각해보기:
1. 만약 주문을 삭제하는 기능을 추가한다면?
   → vector.erase() 사용
2. 여러 결제 수단을 선택할 수 있다면?
   → UI에 결제 선택 버튼 추가
*/