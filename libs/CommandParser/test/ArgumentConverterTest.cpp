#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <CommandParser/ArgumentConverter.hpp>
#include <CommandParser/CommandParser.hpp>


using algo::cmd::ArgumentConverter;
using algo::cmd::CommandParser;


TEST(ArgumentConverterTest, handleValidArguments)
{
    std::istringstream input {"hello 123 4.5"};

    ArgumentConverter<const std::string&, int, double> ac;
    auto output = ac.convert(input);

    EXPECT_EQ("hello", std::get<0>(output));
    EXPECT_EQ(123, std::get<1>(output));
    EXPECT_EQ(4.5, std::get<2>(output));
}


TEST(ArgumentConverterTest, handleInvalidArguments)
{
    std::istringstream input {"hello world 4.5"}; // "world" not convertable to int

    ArgumentConverter<const std::string&, int, double> ac;
    EXPECT_THROW(ac.convert(input), CommandParser::ParseException);
}


TEST(ArgumentConverterTest, tooManyArguments)
{
    // additional arguments should be ignored
    std::istringstream input {"hello 123 4.5 678 world"};

    ArgumentConverter<const std::string&, int, double> ac;
    auto output = ac.convert(input);

    EXPECT_EQ("hello", std::get<0>(output));
    EXPECT_EQ(123, std::get<1>(output));
    EXPECT_EQ(4.5, std::get<2>(output));
}


TEST(ArgumentConverterTest, tooFewArguments)
{
    std::istringstream input {"hello 123"};

    ArgumentConverter<const std::string&, int, double> ac;
    EXPECT_THROW(ac.convert(input), CommandParser::ParseException);
}


