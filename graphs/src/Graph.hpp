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

    // iterators
    typename vertices_map_t::const_iterator begin() const { return _vertices.begin(); }
    typename vertices_map_t::const_iterator end() const { return _vertices.end(); }

    typename vertices_map_t::iterator begin() { return _vertices.begin(); }
    typename vertices_map_t::iterator end() { return _vertices.end(); }


private:
    vertices_map_t _vertices;
};

