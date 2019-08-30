#include <iostream>
#include "Graph.hpp"


void printGraph(const Graph<>& graph)
{
    std::cout << std::endl;

    for (Graph<>::Vertice vert : graph)
    {
        std::cout << "vertice: " << vert.value() << std::endl;
        for (Graph<>::Edge edge : vert.edges())
        {
            std::cout
                << "  edge: "
                << vert.value() << " -> " << edge.target()
                << ": " << edge.value() << std::endl;
        }
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Hello world!" << std::endl;

    Graph<> gr;

    std::cout << " * Adding vertices and edges" << std::endl;
    gr.addVertice(1);
    gr.addVertice(100);
    gr.addVertice(10);
    gr.addVertice(20);

    gr.addEdge(1, 100, 5);
    gr.addEdge(100, 1, -5);
    gr.addEdge(1, 1, 20); // to == from; should not be added
    gr.addEdge(1, 10, 123);
    gr.addEdge(1, 10, 125); // edge already exists; should not be added

    printGraph(gr);

    std::cout << " * Deleting edge 1 -> 10" << std::endl;
    gr.deleteEdge(1, 10);

    printGraph(gr);

    std::cout << " * Deleting vertice 20" << std::endl;
    gr.deleteVertice(20);

    printGraph(gr);

    std::cout << " * Trying to delete non-existing vertices/edges" << std::endl;
    gr.deleteVertice(25);
    gr.deleteEdge(98, 99);

    printGraph(gr);

    std::cout << " * Clearing the graph" << std::endl;
    gr.clear();

    printGraph(gr);
}

