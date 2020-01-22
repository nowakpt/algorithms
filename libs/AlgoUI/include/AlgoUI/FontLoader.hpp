#pragma once
#include <SFML/Graphics/Font.hpp>

namespace algo {
namespace ui {

class FontLoader
{
public:
    static const sf::Font& getFont();

private:
    struct LoadedFont
    {
        LoadedFont();
        sf::Font _font;
    };
};

} // namespace ui
} // namespace algo

