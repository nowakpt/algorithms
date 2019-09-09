add_library(Graph INTERFACE)

target_include_directories(Graph INTERFACE include)

add_executable(GraphTest test/GraphTest.cpp)
target_link_libraries(GraphTest Graph gtest_main gmock)
add_test(
    NAME Graph
    COMMAND GraphTest
)

