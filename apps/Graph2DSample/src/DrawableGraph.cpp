#include "DrawableGraph.hpp"
#include "FontLoader.hpp"
#include <cmath>


DrawableGraph::DrawableGraph()
{
}


void DrawableGraph::draw(Canvas& canvas)
{
    std::lock_guard<std::mutex> lock(_drawableItemsMutex);
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

void DrawableGraph::update(const Graph2D& graph)
{
    std::vector<DrawableVertice> newVertices;
    std::vector<DrawableEdge> newEdges;
    //TODO: initialize vectors with proper capacity

    for (Graph2D::Vertice v : graph)
    {
        const auto& point = v.value();
        sf::Vector2f position(point.x, point.y);
        // add DrawableVertice to the collection
        newVertices.emplace_back(position, point.id);
    }

    for (Graph2D::Vertice v : graph)
    {
        for (Graph2D::Edge e : v.edges())
        {
            auto& from = v.value();
            auto& to = e.target();
            bool isTwoWayEdge = false;
            auto targetVertice = graph.find(e.target());
            if (targetVertice != graph.end())
            {
                Graph2D::Vertice vert(*targetVertice);
                isTwoWayEdge = vert.edges().find(&v.value()) != vert.edges().end();
            }

            constexpr auto r = DrawableVertice::radius;
            double d = isTwoWayEdge ? deltaAngle : 0.0;
            double angle = atan2(to.y - from.y, to.x - from.x);

            sf::Vector2f startPoint(from.x + r * cos(angle + d), from.y + r * sin(angle + d));
            sf::Vector2f endPoint(to.x - r * cos(angle - d), to.y - r * sin(angle - d));

            newEdges.emplace_back(startPoint, endPoint, angle, e.value());
        }
    }

    {
        std::lock_guard<std::mutex> lock(_drawableItemsMutex);

        std::swap(_drawableVertices, newVertices);
        std::swap(_drawableEdges, newEdges);
    }
}

