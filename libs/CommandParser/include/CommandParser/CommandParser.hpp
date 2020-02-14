#pragma once
#include <functional>
#include <iostream>
#include <sstream>
#include <map>


namespace algo {
namespace cmd {

class CommandParser
{
public:
    using CommandHandler = std::function<void(std::istringstream&)>;
    using CommandsMap = std::map<std::string, CommandHandler>;

    CommandParser(const CommandsMap& commands);

    void parse(std::istream& input, std::ostream& output) const;

    struct ParseException
    {
        std::string message;
    };

private:
    const CommandsMap& _commands;

    void parseLine(const std::string& line) const;
};

} // namespace cmd
} // namespace algo

