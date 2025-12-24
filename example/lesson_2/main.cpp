#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 800}), "SFML 수업 2");
    window.setFramerateLimit(60);

    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition({400.0f, 300.0f});

    int       color_index = 0;
    sf::Color colors[]    = {sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta};

    float speed = 5.0f;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            color_index = (color_index + 1) % 4;
            circle.setFillColor(colors[color_index]);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            circle.move({speed, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            circle.move({-speed, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            circle.move({0.f, -speed});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            circle.move({0.f, speed});

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}