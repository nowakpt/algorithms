#pragma once
#include <set>
#include <map>
#include <memory>


template <typename Tv = int, typename Te = int>
class Graph
{
public:
    class Vertice;
    typedef std::set<Vertice> vertices_set_t;
    typedef std::map<const Vertice* const, const Te> edges_map_t;


    class Vertice
    {
        const Tv _value;
        edges_map_t _edges;

    public:
        template <typename T>
        Vertice(T&& value) : _value(std::forward<T>(value)), _edges() {}

        bool operator==(const Tv& rhs) const { return _value == rhs; }
        bool operator==(const Vertice& rhs) const { return _value == rhs._value; }

        bool operator <(const Vertice& rhs) const { return _value < rhs._value; }

        const Tv& value() const { return _value; }
        const edges_map_t& edges() const { return _edges; }
        edges_map_t& edges() { return _edges; }
    };


    Graph() {}

    void clear()
    {
        _vertices.clear();
    }

    template <typename T>
    void addVertice(T&& value)
    {
        _vertices.emplace(std::forward<T>(value));
    }

    void deleteVertice(const Tv& value)
    {
        auto toBeRemoved = _vertices.find(value);

        if (toBeRemoved != _vertices.end())
        {
            for (auto& v : _vertices)
            {
                auto& edges = const_cast<edges_map_t&>(v.edges());
                edges.erase(&*toBeRemoved);
            }

            _vertices.erase(toBeRemoved);
        }
    }

    template <typename T>
    void addEdge(const Tv& from, const Tv& to, T&& value)
    {
        auto iterFrom = _vertices.find(from);
        auto iterTo = _vertices.find(to);

        if (iterFrom != _vertices.end() &&
            iterTo != _vertices.end() &&
            iterFrom != iterTo)
        {
            auto& edges = const_cast<edges_map_t&>(iterFrom->edges());
            edges.emplace(&*iterTo, std::forward<T>(value));
        }
    }

    void deleteEdge(const Tv& from, const Tv& to)
    {
        auto iterFrom = _vertices.find(from);
        auto iterTo = _vertices.find(to);

        if (iterFrom != _vertices.end() &&
            iterTo != _vertices.end())
        {
            auto& edges = const_cast<edges_map_t&>(iterFrom->edges());
            edges.erase(&*iterTo);
        }
    }


    class Edge
    {
        using data_t = typename edges_map_t::value_type;
        const data_t& _data;

    public:
        Edge(const data_t& data) : _data(data) {}

        const Vertice& target() const { return *_data.first; }
        const Te& value() const { return _data.second; }
    };

    // iterators
    using size_type = typename vertices_set_t::size_type;
    using difference_type = typename vertices_set_t::difference_type;
    using value_type = typename vertices_set_t::value_type;
    using reference = typename vertices_set_t::reference;
    using const_reference = typename vertices_set_t::const_reference;
    using iterator = typename vertices_set_t::iterator;
    using const_iterator = typename vertices_set_t::const_iterator;
    using pointer = typename vertices_set_t::pointer;
    using const_pointer = typename vertices_set_t::const_pointer;

    iterator begin() { return _vertices.begin(); }
    iterator end() { return _vertices.end(); }

    const_iterator begin() const { return _vertices.begin(); }
    const_iterator end() const { return _vertices.end(); }

    const_iterator find(const Tv& vertice) const
    {
        return _vertices.find(vertice);
    }

    iterator find(const Tv& vertice)
    {
        return _vertices.find(vertice);
    }

private:
    vertices_set_t _vertices;
};

