#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>


class Canvas
{
private:
    sf::RenderWindow _window;
    sf::View _view;

    bool _isMousePressed;
    sf::Vector2i _mousePos;
    float _zoomLevel;

public:
    Canvas(int width, int height, const std::string& title);

    bool isOpen() { return _window.isOpen(); }

    void handleEvents();

};

