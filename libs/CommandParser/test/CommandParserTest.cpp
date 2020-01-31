#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <CommandParser/CommandParser.hpp>
#include <vector>

using ::testing::HasSubstr;

using algo::cmd::CommandParser;


TEST(CommandParserTest, parseAndExecuteCommand)
{
    int callCount = 0;
    CommandParser::CommandsMap map
    {{
        "test", [&](std::istringstream& args) {
            callCount++;
            EXPECT_EQ("hello world", args.str());
        }
    }};

    std::stringstream input {"test hello world"};
    std::stringstream output;

    CommandParser cp(map);
    cp.parse(input, output);

    EXPECT_EQ(1, callCount);
    EXPECT_EQ("> ", output.str());
}


TEST(CommandParserTest, invalidCommand)
{
    int callCount = 0;
    CommandParser::CommandsMap map
    {{
        "test", [&](std::istringstream& args) {
            callCount++;
        }
    }};

    std::stringstream input {"nottest hello world"};
    std::stringstream output;

    CommandParser cp(map);
    cp.parse(input, output);

    EXPECT_EQ(0, callCount);
    EXPECT_THAT(output.str(), HasSubstr("error: invalid command"));
}


TEST(CommandParserTest, multipleCallsWithDifferentArguments)
{
    std::vector<std::string> receivedArguments;
    int callCount = 0;
    CommandParser::CommandsMap map
    {{
        "test", [&](std::istringstream& args) {
            callCount++;
            receivedArguments.push_back(args.str());
        }
    }};

    std::stringstream input {"test\ntest abc\ntest  123 45 \ntest hello world"};
    std::stringstream output;

    CommandParser cp(map);
    cp.parse(input, output);

    EXPECT_EQ("> > > > ", output.str());
    EXPECT_EQ(4, callCount);
    ASSERT_EQ(4, receivedArguments.size());
    EXPECT_EQ("", receivedArguments[0]);
    EXPECT_EQ("abc", receivedArguments[1]);
    EXPECT_EQ(" 123 45 ", receivedArguments[2]);
    EXPECT_EQ("hello world", receivedArguments[3]);
}


TEST(CommandParserTest, handleEmptyLine)
{
    int callCount = 0;
    CommandParser::CommandsMap map
    {{
        "", [&](std::istringstream& args) {
            // should not be called, even if provided keyword is an empty string
            callCount++;
        }
    }};

    std::stringstream input {"\n"};
    std::stringstream output;

    CommandParser cp(map);
    cp.parse(input, output);

    EXPECT_EQ(0, callCount);
    EXPECT_EQ("> > ", output.str()); // double prompt expected
}

