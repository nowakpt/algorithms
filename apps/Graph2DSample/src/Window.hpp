#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>
#include "Drawable.hpp"


class Window
{
private:
    sf::RenderWindow _window;
    sf::View _view;

    std::shared_ptr<Drawable> _drawable;

    bool _isMousePressed;
    sf::Vector2i _mousePos;
    float _zoomLevel;

    void handleEvents();

public:
    Window(int width, int height, const std::string& title);

    bool isOpen() { return _window.isOpen(); }

    void startEventHandling();

    void setDrawable(std::shared_ptr<Drawable> drawable)
    {
        _drawable = std::move(drawable);
    }

};

