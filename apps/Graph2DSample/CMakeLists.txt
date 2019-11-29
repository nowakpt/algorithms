add_executable(Graph2DSample
    src/main.cpp
    src/Window.cpp
    src/DrawableGraph.cpp
    src/FontLoader.cpp
)

target_link_libraries(Graph2DSample
    PRIVATE
    Graph
    sfml-graphics
)

