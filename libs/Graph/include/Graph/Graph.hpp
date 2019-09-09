#pragma once
#include <set>
#include <map>
#include <memory>


template <typename Tv = int, typename Te = int>
class Graph
{
public:
    typedef std::map<const Tv*, Te> edges_map_t;
    typedef std::map<Tv, edges_map_t> vertices_map_t;

    Graph() {}


    void clear()
    {
        _vertices.clear();
    }

    template <typename T>
    void addVertice(T&& value)
    {
        _vertices.emplace(std::forward<T>(value), edges_map_t{});
    }

    void deleteVertice(const Tv& value)
    {
        auto toBeRemoved = _vertices.find(value);

        if (toBeRemoved != _vertices.end())
        {
            for (auto& v : _vertices)
            {
                auto& edges = v.second;
                edges.erase(&toBeRemoved->first);
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
            iterFrom->second.emplace(&iterTo->first, std::forward<T>(value));
        }
    }

    void deleteEdge(const Tv& from, const Tv& to)
    {
        auto iterFrom = _vertices.find(from);
        auto iterTo = _vertices.find(to);

        if (iterFrom != _vertices.end() &&
            iterTo != _vertices.end())
        {
            auto& edges = iterFrom->second;
            auto toBeRemoved = edges.find(&iterTo->first);

            if (toBeRemoved != edges.end())
            {
                edges.erase(toBeRemoved);
            }
        }
    }

    // accessing vertices/edges
    /**
    * Classes Vertice and Edge are wrappers for std::pair<...> objects returned
    * by map iterators. They allow to use explicictly named getter methods
    * instead of accessing them by fields `first` & `second` of the std::pair.
    *
    * They can be used in range-based for loops, e.g.:
    *
    *   for (Graph<>::Vertice v : graph) {
    *     for (Graph<>::Edge e : v.edges()) {
    *         // ...
    *     }
    *   }
    *
    */
    class Vertice
    {
        using data_t = typename vertices_map_t::value_type;
        const data_t& _data;

    public:
        Vertice(const data_t& data) : _data(data) {}

        const Tv& value() const { return _data.first; }
        const edges_map_t& edges() const { return _data.second; }
    };

    class Edge
    {
        using data_t = typename edges_map_t::value_type;
        const data_t& _data;

    public:
        Edge(const data_t& data) : _data(data) {}

        const Tv& target() const { return *_data.first; }
        const Te& value() const { return _data.second; }
    };

    // iterators
    using size_type = typename vertices_map_t::size_type;
    using difference_type = typename vertices_map_t::difference_type;
    using value_type = typename vertices_map_t::value_type;
    using reference = typename vertices_map_t::reference;
    using const_reference = typename vertices_map_t::const_reference;
    using iterator = typename vertices_map_t::iterator;
    using const_iterator = typename vertices_map_t::const_iterator;
    using pointer = typename vertices_map_t::pointer;
    using const_pointer = typename vertices_map_t::const_pointer;

    const_iterator begin() const { return _vertices.begin(); }
    const_iterator end() const { return _vertices.end(); }

    iterator begin() { return _vertices.begin(); }
    iterator end() { return _vertices.end(); }


private:
    vertices_map_t _vertices;
};

