add_library(AlgoUI STATIC
    src/Window.cpp
    src/FontLoader.cpp
)

target_include_directories(AlgoUI PUBLIC include)

target_link_libraries(AlgoUI
    PUBLIC
    sfml-graphics
    sfmlFont
)

