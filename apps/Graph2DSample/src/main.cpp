#include <iostream>
#include "Window.hpp"
#include <Graph/Graph.hpp>
#include "DrawableGraph.hpp"


using Graph2D = DrawableGraph::Graph2D;
using Vertice = DrawableGraph::Point;


int main()
{

    std::cout << "Hello world!" << std::endl;

    Window window(800, 600, "2D Window");

    std::shared_ptr<DrawableGraph> dg = std::make_shared<DrawableGraph>();
    DrawableGraph::Graph2D graph;

    Vertice v1{100, 100, 'A'};
    Vertice v2{100, 500, 'B'};
    Vertice v3{400, 550, 'C'};
    Vertice v4{700, 500, 'D'};
    Vertice v5{700, 100, 'E'};

    graph.addVertice(v1);
    graph.addVertice(v2);
    graph.addVertice(v3);
    graph.addVertice(v4);
    graph.addVertice(v5);
    graph.addEdge(v1, v2, 10);
    graph.addEdge(v2, v3, 10);
    graph.addEdge(v3, v2, 10);
    graph.addEdge(v3, v4, 10);
    graph.addEdge(v4, v5, 10);
    graph.addEdge(v5, v4, 10);
    graph.addEdge(v1, v5, 10);

    dg->update(graph);

    window.setDrawable(dg);

    window.startEventHandling();

    return 0;
}

