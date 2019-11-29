#include "FontLoader.hpp"

FontLoader::LoadedFont::LoadedFont()
{
    //TODO: use fontconfig to load fonts
    _font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf");
}

const sf::Font& FontLoader::getFont()
{
    static LoadedFont loadedFont;
    return loadedFont._font;
}


