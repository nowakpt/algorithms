#pragma once
#include <set>
#include <map>
#include <memory>


template <typename Tv, typename Te>
class Vertice
{
public:
    std::map<const std::weak_ptr<Vertice>, Te> _edges;
    Tv _value;

    template <typename T>
    Vertice(T&& value) : _value(std::forward<T>(value)) {}
};


template <typename Tv = int, typename Te = int>
class Graph
{
private:
    typedef Vertice<Tv, Te> vertice_type;

    std::set<std::shared_ptr<vertice_type> > _vertices;

public:
    Graph() {}

    template <typename T>
    void addVertice(T&& verticeValue)
    {
        auto v = std::make_shared<vertice_type>(std::forward<T>(verticeValue));
        _vertices.insert(v);
    }

};

