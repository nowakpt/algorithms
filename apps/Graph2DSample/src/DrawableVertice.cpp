#include "DrawableVertice.hpp"
#include <AlgoUI/FontLoader.hpp>


DrawableVertice::DrawableVertice(const sf::Vector2f& position, char label) :
    _circle(radius)
{
    _circle.setOrigin(radius, radius);
    _circle.setPosition(position);

    _label.setString(sf::String(label));
    _label.setFont(FontLoader::getFont());
    _label.setFillColor(sf::Color::Black);
    _label.setCharacterSize(textSize);

    auto labelBounds = _label.getLocalBounds();
    _label.setOrigin(labelBounds.left + labelBounds.width/2, labelBounds.top + labelBounds.height/2);
    _label.setPosition(position);
}

