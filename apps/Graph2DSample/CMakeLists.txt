add_executable(Graph2DSample
    src/main.cpp
)

target_link_libraries(Graph2DSample
    PRIVATE
    Graph
    sfml-graphics
)

