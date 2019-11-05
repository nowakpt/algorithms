#include <iostream>
#include "Window.hpp"


class Circle : public Drawable
{
    sf::Color calculateColor() const
    {
        return sf::Color::Green;
    }

    void draw(Canvas& canvas) override
    {
        canvas.clear(sf::Color(40, 40, 40, 255));
        sf::CircleShape shape(100.f);
        shape.setFillColor(calculateColor());
        canvas.draw(shape);
    }
};


int main()
{
    std::cout << "Hello world!" << std::endl;

    Window window(800, 600, "2D Window");

    auto circle = std::make_shared<Circle>();
    window.setDrawable(circle);

    window.startEventHandling();

    return 0;
}

