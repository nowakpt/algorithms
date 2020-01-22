#include <iostream>
#include <thread>
#include <chrono>
#include <array>
#include <AlgoUI/Window.hpp>
#include "DrawableGraph.hpp"

using Graph2D = DrawableGraph::Graph2D;
using Vertice = DrawableGraph::Point;
using UDGraph = algo::ui::UpdatableDrawable<DrawableGraph>;
using algo::ui::Window;


void sleep()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}


void addElementsToGraph(std::shared_ptr<UDGraph> dg)
{
    Graph2D graph;

    std::array<const Vertice, 5> vertices = {{
        {100, 100, 'A'},
        {100, 500, 'B'},
        {400, 550, 'C'},
        {700, 500, 'D'},
        {700, 100, 'E'}
    }};

    for (const auto& v : vertices) {
        graph.addVertice(v);
        dg->update(graph);
        sleep();
    }

    int value = 10;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == j) continue;

            graph.addEdge(vertices[i], vertices[j], value++);
            dg->update(graph);
            sleep();
        }

    }
}


int main()
{

    std::cout << "Hello world!" << std::endl;

    Window window(800, 600, "2D Window");

    std::shared_ptr<UDGraph> dg = std::make_shared<UDGraph>();

    window.setDrawable(dg);

    std::thread updater(addElementsToGraph, dg);

    window.startEventHandling();

    updater.join();

    return 0;
}

