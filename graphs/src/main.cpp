#include <iostream>
#include "Graph.hpp"


int main()
{
    std::cout << "Hello world!" << std::endl;


    Graph<> gr;

    gr.addVertice(1);
    gr.addVertice(100);
    gr.addVertice(10);
    gr.addVertice(20);

    gr.addEdge(1, 100, 5);
    gr.addEdge(100, 1, -5);

    gr.addEdge(1, 1, 20);
    gr.addEdge(1, 10, 123);
    gr.addEdge(1, 10, 125);

    for (const auto& v : gr)
    {
        std::cout << "gr value: " << v.first << std::endl;
        for (const auto& e : v.second)
        {
            std::cout << " edge: " << v.first << " -> " << *e.first << ": " << e.second << std::endl;
        }
    }
}

