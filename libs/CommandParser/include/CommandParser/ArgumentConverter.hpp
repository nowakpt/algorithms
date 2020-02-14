#pragma once
#include <functional>
#include <tuple>
#include <iostream>
#include "CommandParser/CommandParser.hpp"


namespace algo {
namespace cmd {

template <typename... Ts>
class ArgumentConverter
{
public:
    // type might be simplified in C++20: std::remove_cvref_t
    using tuple_t = std::tuple<std::remove_cv_t<std::remove_reference_t<Ts> >... >;


    tuple_t convert(std::istream& input)
    {
        tuple_t parsedArgs;

        parseArguments(input, parsedArgs);

        if (!input)
        {
            throw CommandParser::ParseException {"invalid arguments provided"};
        }

        return parsedArgs;
    }

private:
    template <size_t INDEX>
    constexpr void parseArgument(std::istream& input, tuple_t& args)
    {
        input >> std::get<INDEX>(args);

        if constexpr ((INDEX+1) < std::tuple_size<tuple_t>::value)
        {
            parseArgument<INDEX+1>(input, args);
        }
    }

    void parseArguments(std::istream& input, tuple_t& args)
    {
        parseArgument<0>(input, args);
    }
};

} // namespace cmd
} // namespace algo

