#pragma once
#include "Drawable.hpp"
#include <SFML/Graphics.hpp>


class DrawableVertice : public Drawable
{
    sf::CircleShape _circle;
    sf::Text _label;

public:
    static constexpr int radius = 20;
    static constexpr int textSize = 26;

    DrawableVertice(const sf::Vector2f& position, char label);

    void draw(Canvas& canvas) override
    {
        canvas.draw(_circle);
        canvas.draw(_label);
    }
};

