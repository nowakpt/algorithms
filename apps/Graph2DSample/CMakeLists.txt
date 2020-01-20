add_executable(Graph2DSample
    src/main.cpp
    src/DrawableGraph.cpp
    src/DrawableVertice.cpp
    src/DrawableEdge.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(Graph2DSample
    PRIVATE
    Graph
    AlgoUI
    Threads::Threads
)

