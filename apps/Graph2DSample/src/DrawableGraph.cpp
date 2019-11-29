#include "DrawableGraph.hpp"
#include "FontLoader.hpp"


DrawableGraph::DrawableGraph()
{
}


DrawableGraph::DrawableVertice::DrawableVertice(const sf::Vector2f& position, char label) :
    _circle(radius)
{
    _circle.setOrigin(radius, radius);
    _circle.setPosition(position);

    _label.setString(sf::String(label));
    _label.setFont(FontLoader::getFont());
    _label.setFillColor(sf::Color::Black);
    _label.setCharacterSize(textSize);

    auto labelBounds = _label.getLocalBounds();
    _label.setOrigin(labelBounds.left + labelBounds.width/2, labelBounds.top + labelBounds.height/2);
    _label.setPosition(position);
}

DrawableGraph::DrawableEdge::DrawableEdge(const sf::Vector2f& from, const sf::Vector2f& to, double angle, int value) :
    _arrowTip(3)
{
    float length = sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2)) - tipWidth + 1;
    double angleDegrees = angle * 180.0 / M_PI;

    _line.setOrigin(0, lineWidth/2);
    _line.setSize({length, lineWidth});
    _line.setPosition(from);
    _line.setRotation(angleDegrees);
    _line.setFillColor(sf::Color(color));

    _arrowTip.setPoint(0, sf::Vector2f(0, 0));
    _arrowTip.setPoint(1, sf::Vector2f(-tipLength, -tipWidth/2));
    _arrowTip.setPoint(2, sf::Vector2f(-tipLength, tipWidth/2));
    _arrowTip.setPosition(to);
    _arrowTip.setRotation(angleDegrees);
    _arrowTip.setFillColor(sf::Color(color));

    float labelPosX = 0.20 * from.x + 0.80 * to.x - labelDistance * sin(angle);
    float labelPosY = 0.20 * from.y + 0.80 * to.y + labelDistance * cos(angle);
    _label.setString(std::to_string(value));
    _label.setFont(FontLoader::getFont());
    _label.setCharacterSize(textSize);

    auto labelBounds = _label.getLocalBounds();
    _label.setOrigin(labelBounds.left + labelBounds.width/2, labelBounds.top + labelBounds.height/2);
    _label.setPosition({labelPosX, labelPosY});
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

