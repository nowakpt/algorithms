#pragma once
#include "DrawableVertice.hpp"
#include "DrawableEdge.hpp"
#include <Graph/Graph.hpp>



class DrawableGraph : public algo::ui::Drawable
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

    using Graph2D = algo::Graph<Point, int>;


    DrawableGraph();
    DrawableGraph(const Graph2D& graph);

    void draw(algo::ui::Canvas& canvas) override;

private:
    std::vector<DrawableVertice> _drawableVertices;
    std::vector<DrawableEdge> _drawableEdges;

    static constexpr double deltaAngle = 0.52;

    void addDrawableElements(const Graph2D& graph);
};

