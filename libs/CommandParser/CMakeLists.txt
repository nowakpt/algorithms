add_library(CommandParser STATIC
    src/CommandParser.cpp
)

target_include_directories(CommandParser PUBLIC include)


add_executable(CommandParserTest
    test/CommandParserTest.cpp
    test/ArgumentConverterTest.cpp
)

target_link_libraries(CommandParserTest
    CommandParser
    gtest_main
    gmock
)

add_test(
    NAME CommandParser
    COMMAND CommandParserTest
)

