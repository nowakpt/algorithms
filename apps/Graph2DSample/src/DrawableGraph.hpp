#pragma once
#include <AlgoUI/Window.hpp>
#include "DrawableVertice.hpp"
#include "DrawableEdge.hpp"
#include <Graph/Graph.hpp>



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
    DrawableGraph(const Graph2D& graph);

    void draw(Canvas& canvas) override;

private:
/*
    struct DrawableVertice
    {
        sf::CircleShape _circle;
        sf::Text _label;

        static constexpr int radius = 20;
        static constexpr int textSize = 26;

        DrawableVertice(const sf::Vector2f& position, char label);
    };

    struct DrawableEdge
    {
        sf::RectangleShape _line;
        sf::ConvexShape _arrowTip;
        sf::Text _label;

        static constexpr int lineWidth = 2;
        static constexpr int tipWidth = 10;
        static constexpr int tipLength = 14;
        static constexpr int textSize = 14;
        static constexpr double labelDistance = 15.0;
        static constexpr unsigned int color = 0x888888FF;

        DrawableEdge(const sf::Vector2f& from, const sf::Vector2f& to, double angle, int value);
    };
*/
    static constexpr double deltaAngle = 0.52;
    std::vector<DrawableVertice> _drawableVertices;
    std::vector<DrawableEdge> _drawableEdges;

    void addDrawableElements(const Graph2D& graph);
};

