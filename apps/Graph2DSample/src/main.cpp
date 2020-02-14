#include <iostream>
#include <thread>
#include <AlgoUI/Window.hpp>
#include <CommandParser/ArgumentConverter.hpp>
#include <CommandParser/CommandParser.hpp>
#include "DrawableGraph.hpp"

using Graph2D = DrawableGraph::Graph2D;
using Vertice = DrawableGraph::Point;
using UDGraph = algo::ui::UpdatableDrawable<DrawableGraph>;
using algo::ui::Window;
using algo::cmd::CommandParser;
using algo::cmd::ArgumentConverter;


void parseInput(std::shared_ptr<UDGraph> dg)
{
    Graph2D gr;

    CommandParser::CommandsMap commands {
        {
            "addVertice", [&](std::istringstream& args)
            {
                ArgumentConverter<int, int, char> ac;
                auto tuple = ac.convert(args);
                Vertice v { std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple) };

                gr.addVertice(v);
                dg->update(gr);
                std::cout << "addVertice complete" << std::endl;
            }
        },
        {
            "addEdge", [&](std::istringstream& args)
            {
                ArgumentConverter<char, char, int> ac;
                auto tuple = ac.convert(args);

                Vertice from, to;
                from.id = std::get<0>(tuple);
                to.id = std::get<1>(tuple);

                gr.addEdge(from, to, std::get<2>(tuple));
                dg->update(gr);
                std::cout << "addEdge complete" << std::endl;
            }
        },
        {
            "deleteVertice", [&](std::istringstream& args)
            {
                ArgumentConverter<char> ac;
                auto tuple = ac.convert(args);

                Vertice v;
                v.id = std::get<0>(tuple);

                gr.deleteVertice(v);
                dg->update(gr);
                std::cout << "deleteVertice complete" << std::endl;
            }
        },
        {
            "deleteEdge", [&](std::istringstream& args)
            {
                ArgumentConverter<char, char> ac;
                auto tuple = ac.convert(args);

                Vertice from, to;
                from.id = std::get<0>(tuple);
                to.id = std::get<1>(tuple);

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

