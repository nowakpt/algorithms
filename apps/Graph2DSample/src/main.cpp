#include <iostream>
#include <thread>
#include <chrono>
#include <array>
#include <AlgoUI/Window.hpp>
#include <CommandParser/CommandParser.hpp>
#include "DrawableGraph.hpp"

using Graph2D = DrawableGraph::Graph2D;
using Vertice = DrawableGraph::Point;
using UDGraph = algo::ui::UpdatableDrawable<DrawableGraph>;
using algo::ui::Window;
using algo::cmd::CommandParser;


void parseInput(std::shared_ptr<UDGraph> dg)
{
    Graph2D gr;

    CommandParser::CommandsMap commands {
        {
            "addVertice", [&](std::istringstream& args)
            {
                Vertice v;
                args >> v.x >> v.y >> v.id;
                if (!args)
                {
                    std::cout << "invalid parameters" << std::endl;
                    return;
                }
                gr.addVertice(v);
                dg->update(gr);
                std::cout << "addVertice complete" << std::endl;
            }
        },
        {
            "addEdge", [&](std::istringstream& args)
            {
                Vertice from, to;
                int value;
                args >> from.id >> to.id >> value;
                if (!args)
                {
                    std::cout << "invalid parameters" << std::endl;
                    return;
                }
                gr.addEdge(from, to, value);
                dg->update(gr);
                std::cout << "addEdge complete" << std::endl;
            }
        },
        {
            "deleteVertice", [&](std::istringstream& args)
            {
                Vertice v;
                args >> v.id;
                if (!args)
                {
                    std::cout << "invalid parameters" << std::endl;
                    return;
                }
                gr.deleteVertice(v);
                dg->update(gr);
                std::cout << "deleteVertice complete" << std::endl;
            }
        },
        {
            "deleteEdge", [&](std::istringstream& args)
            {
                Vertice from, to;
                args >> from.id >> to.id;
                if (!args)
                {
                    std::cout << "invalid parameters" << std::endl;
                    return;
                }
                gr.deleteEdge(from, to);
                dg->update(gr);
                std::cout << "deleteEdge complete" << std::endl;
            }
        },
    };

    CommandParser parser(commands);
    parser.parse(std::cin, std::cout);
}


int main()
{

    std::cout << "Hello world!" << std::endl;

    Window window(800, 600, "2D Window");

    std::shared_ptr<UDGraph> dg = std::make_shared<UDGraph>();

    window.setDrawable(dg);

    std::thread parserThread(parseInput, std::move(dg));

    window.startEventHandling();

    parserThread.join();

    return 0;
}

