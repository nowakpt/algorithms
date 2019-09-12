#include <iostream>
#include "Canvas.hpp"

int main()
{
    std::cout << "Hello world!" << std::endl;

    Canvas canvas(800, 600, "2D Canvas");
/*
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    canvas.draw(shape);
*/
    while (canvas.isOpen())
    {
        canvas.handleEvents();
    }

    return 0;
}

