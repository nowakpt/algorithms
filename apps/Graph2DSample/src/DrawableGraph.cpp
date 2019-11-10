#include "DrawableGraph.hpp"


DrawableGraph::DrawableGraph()
{
    _font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf");
    //TODO: use fontconfig to load fonts
}


DrawableGraph::DrawableVertice::DrawableVertice(const sf::Vector2f& position, const sf::Font& font, char label) :
    _circle(radius)
{
    _circle.setOrigin(radius, radius);
    _circle.setPosition(position);

    _label.setString(sf::String(label));
    _label.setFont(font);
    _label.setFillColor(sf::Color::Black);
    _label.setCharacterSize(textSize);

    auto labelBounds = _label.getLocalBounds();
    _label.setOrigin(labelBounds.left + labelBounds.width/2, labelBounds.top + labelBounds.height/2);
    _label.setPosition(position);
}

DrawableGraph::DrawableEdge::DrawableEdge(const sf::Vector2f& from, const sf::Vector2f& to, double angle) :
    _arrowTip(3)
{
    float length = sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2)) - tipWidth + 1;

    _line.setOrigin(0, lineWidth/2);
    _line.setSize({length, lineWidth});
    _line.setPosition(from);
    _line.setRotation(angle);
    _line.setFillColor(sf::Color(color));

    _arrowTip.setPoint(0, sf::Vector2f(0, 0));
    _arrowTip.setPoint(1, sf::Vector2f(-tipLength, -tipWidth/2));
    _arrowTip.setPoint(2, sf::Vector2f(-tipLength, tipWidth/2));
    _arrowTip.setPosition(to);
    _arrowTip.setRotation(angle);
    _arrowTip.setFillColor(sf::Color(color));
}

void DrawableGraph::draw(Canvas& canvas)
{
    std::lock_guard<std::mutex> lock(_drawableItemsMutex);

    canvas.clear(sf::Color(40, 40, 40, 255));

    for (const DrawableEdge& de : _drawableEdges)
    {
        canvas.draw(de._line);
        canvas.draw(de._arrowTip);
        canvas.draw(de._label);
    }

    for (const DrawableVertice& dv : _drawableVertices)
    {
        canvas.draw(dv._circle);
        canvas.draw(dv._label);
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
        newVertices.emplace_back(position, getFont(), point.id);
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

            newEdges.emplace_back(startPoint, endPoint, angle * 180 / M_PI);
        }
    }

    {
        std::lock_guard<std::mutex> lock(_drawableItemsMutex);

        std::swap(_drawableVertices, newVertices);
        std::swap(_drawableEdges, newEdges);
    }
}

