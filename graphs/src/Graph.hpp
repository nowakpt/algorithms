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

    template <typename T>
    void addVertice(T&& value)
    {
        _vertices.emplace(std::forward<T>(value), edges_map_t{});
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

    // iterators
    typename vertices_map_t::iterator begin() { return _vertices.begin(); }
    typename vertices_map_t::iterator end() { return _vertices.end(); }


private:
    vertices_map_t _vertices;
};

