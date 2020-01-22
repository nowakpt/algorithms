#include "DrawableEdge.hpp"
#include <AlgoUI/FontLoader.hpp>
#include <cmath>


DrawableEdge::DrawableEdge(const sf::Vector2f& from, const sf::Vector2f& to, double angle, int value) :
    _arrowTip(3)
{
    float length = sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2)) - tipWidth + 1;
    double angleDegrees = angle * 180.0 / M_PI;

    _line.setOrigin(0, lineWidth/2);
    _line.setSize({length, lineWidth});
    _line.setPosition(from);
    _line.setRotation(angleDegrees);
    _line.setFillColor(sf::Color(color));

    _arrowTip.setPoint(0, sf::Vector2f(0, 0));
    _arrowTip.setPoint(1, sf::Vector2f(-tipLength, -tipWidth/2));
    _arrowTip.setPoint(2, sf::Vector2f(-tipLength, tipWidth/2));
    _arrowTip.setPosition(to);
    _arrowTip.setRotation(angleDegrees);
    _arrowTip.setFillColor(sf::Color(color));

    float labelPosX = 0.20 * from.x + 0.80 * to.x - labelDistance * sin(angle);
    float labelPosY = 0.20 * from.y + 0.80 * to.y + labelDistance * cos(angle);
    _label.setString(std::to_string(value));
    _label.setFont(algo::ui::FontLoader::getFont());
    _label.setCharacterSize(textSize);

    auto labelBounds = _label.getLocalBounds();
    _label.setOrigin(labelBounds.left + labelBounds.width/2, labelBounds.top + labelBounds.height/2);
    _label.setPosition({labelPosX, labelPosY});
}

