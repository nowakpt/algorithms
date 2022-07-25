#include <AlgoUI/FontLoader.hpp>

using namespace algo::ui;


FontLoader::LoadedFont::LoadedFont()
{
#ifdef SFML_FONT_PATH
	const char fontPath[] = SFML_FONT_PATH;
#else
	const char fontPath[] = "/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf";
#endif

    _font.loadFromFile(fontPath);
}

const sf::Font& FontLoader::getFont()
{
    static LoadedFont loadedFont;
    return loadedFont._font;
}


