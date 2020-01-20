#include <AlgoUI/Window.hpp>
#include <thread>
#include <chrono>

namespace
{
static sf::ContextSettings getContextSettings()
{
    sf::ContextSettings settings {};
    settings.antialiasingLevel = 4;
    return settings;
}

} // namespace


Window::Window(int width, int height, const std::string& title) :
    _window(sf::VideoMode(width, height), title, sf::Style::Default, getContextSettings()),
    _view(sf::FloatRect(0.f, 0.f, width, height)),
    _drawable(nullptr),
    _isMousePressed(false),
    _zoomLevel(1.f)
{
    _window.setFramerateLimit(60);
}


void Window::handleEvents()
{
    _window.setView(_view);

    auto localDrawable = _drawable;
    if (localDrawable)
    {
        Canvas canvas(_window);
        localDrawable->draw(canvas);
    }

    _window.display();

    sf::Event event;
    while (_window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                _window.close();
                break;

            case sf::Event::MouseWheelScrolled:
                {
                    float zoom = 1.f - 0.05f * event.mouseWheelScroll.delta;
                    _zoomLevel *= zoom;
                    _view.zoom(zoom);
                }
                break;

            case sf::Event::MouseButtonPressed:
                _mousePos = sf::Mouse::getPosition(_window);
                _isMousePressed = true;
                break;

            case sf::Event::MouseButtonReleased:
                _isMousePressed = false;
                break;

            case sf::Event::MouseMoved:
                if (_isMousePressed)
                {
                    sf::Vector2i newMousePos(event.mouseMove.x, event.mouseMove.y);
                    sf::Vector2f delta = sf::Vector2f(_mousePos - newMousePos) * _zoomLevel;

                    _view.move(delta);
                    _mousePos = newMousePos;
                }
                break;

            case sf::Event::Resized:
                {
                    sf::Vector2f newSize(event.size.width * _zoomLevel, event.size.height * _zoomLevel);
                    _view.setSize(newSize);
                }
                break;
        }
    }
}


void Window::startEventHandling()
{
    while (isOpen())
    {
        handleEvents();
    }
}

