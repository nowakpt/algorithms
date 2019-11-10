#pragma once
#include "Window.hpp"
#include <Graph/Graph.hpp>
#include <cmath>
#include <mutex>



class DrawableGraph : public Drawable
{
public:
    struct Point
    {
        int x;
        int y;
        char id;

        bool operator < (const Point& other) const
        {
            return this->id < other.id;
        }
    };

    using Graph2D = Graph<Point, int>;


    DrawableGraph();

    void draw(Canvas& canvas) override;

    void update(const Graph2D& graph);

private:
    struct DrawableVertice
    {
        sf::CircleShape _circle;
        sf::Text _label;

        static constexpr int radius = 20;
        static constexpr int textSize = 26;

        DrawableVertice(const sf::Vector2f& position, const sf::Font& font, char label);
    };

    struct DrawableEdge
    {
        sf::RectangleShape _line;
        sf::ConvexShape _arrowTip;
        sf::Text _label;

        static constexpr int lineWidth = 2;
        static constexpr int tipWidth = 10;
        static constexpr int tipLength = 14;
        static constexpr unsigned int color = 0x888888FF;

        DrawableEdge(const sf::Vector2f& from, const sf::Vector2f& to, double angle);
    };

    static constexpr double deltaAngle = 0.52;
    sf::Font _font;
    std::vector<DrawableVertice> _drawableVertices;
    std::vector<DrawableEdge> _drawableEdges;
    std::mutex _drawableItemsMutex;

    const sf::Font& getFont() const { return _font; }
};

