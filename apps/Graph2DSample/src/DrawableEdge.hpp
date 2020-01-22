#pragma once
#include <AlgoUI/Drawable.hpp>


class DrawableEdge : public algo::ui::Drawable
{
    sf::RectangleShape _line;
    sf::ConvexShape _arrowTip;
    sf::Text _label;

public:
    static constexpr int lineWidth = 2;
    static constexpr int tipWidth = 10;
    static constexpr int tipLength = 14;
    static constexpr int textSize = 14;
    static constexpr double labelDistance = 15.0;
    static constexpr unsigned int color = 0x888888FF;

    DrawableEdge(const sf::Vector2f& from, const sf::Vector2f& to, double angle, int value);

    void draw(algo::ui::Canvas& canvas) override
    {
        canvas.draw(_line);
        canvas.draw(_arrowTip);
        canvas.draw(_label);
    }
};

