#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>

class Canvas
{
    sf::RenderWindow& _window;

public:
    Canvas(sf::RenderWindow& window) : _window(window) {}

    void clear(const sf::Color& color = sf::Color(0, 0, 0, 255))
    {
        _window.clear(color);
    }

    template <typename... Args>
    void draw(Args... args)
    {
        _window.draw(args...);
    }

};

