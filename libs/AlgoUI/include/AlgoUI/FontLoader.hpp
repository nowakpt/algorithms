#pragma once
#include <SFML/Graphics/Font.hpp>


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

