#include "DrawableGraph.hpp"
#include <cmath>


DrawableGraph::DrawableGraph()
{
}


DrawableGraph::DrawableGraph(const Graph2D& graph)
{
    addDrawableElements(graph);
}


void DrawableGraph::draw(algo::ui::Canvas& canvas)
{
    canvas.clear(sf::Color(40, 40, 40, 255));

    for (DrawableEdge& de : _drawableEdges)
    {
        de.draw(canvas);
    }

    for (DrawableVertice& dv : _drawableVertices)
    {
        dv.draw(canvas);
    }
}

void DrawableGraph::addDrawableElements(const Graph2D& graph)
{
    for (const Graph2D::Vertice& v : graph)
    {
        const auto& point = v.value();
        sf::Vector2f position(point.x, point.y);
        // add DrawableVertice to the collection
        _drawableVertices.emplace_back(position, point.id);
    }

    for (const Graph2D::Vertice& v : graph)
    {
        for (Graph2D::Edge e : v.edges())
        {
            auto& from = v.value();
            auto& to = e.target().value();

            bool isTwoWayEdge = e.target().edges().count(&v) > 0;

            constexpr auto r = DrawableVertice::radius;
            double d = isTwoWayEdge ? deltaAngle : 0.0;
            double angle = atan2(to.y - from.y, to.x - from.x);

            sf::Vector2f startPoint(from.x + r * cos(angle + d), from.y + r * sin(angle + d));
            sf::Vector2f endPoint(to.x - r * cos(angle - d), to.y - r * sin(angle - d));

            _drawableEdges.emplace_back(startPoint, endPoint, angle, e.value());
        }
    }
}

