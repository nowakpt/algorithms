#include <CommandParser/CommandParser.hpp>

using namespace algo::cmd;


CommandParser::CommandParser(const CommandsMap& commands) :
    _commands(commands)
{}


void CommandParser::parse(std::istream& input, std::ostream& output) const
{
    std::string line;

    while (!input.eof())
    {
        output << "> ";
        std::getline(input, line);
        if (line.empty())
        {
            continue;
        }

        try
        {
            parseLine(line);
        }
        catch (const ParseException& ex)
        {
            output << "error: " << ex.message << std::endl;
        }
    }
}


void CommandParser::parseLine(const std::string& line) const
{
    auto firstSpaceIndex = line.find(' ');
    std::string command = line.substr(0, firstSpaceIndex);

    auto searchResult = _commands.find(command);

    if (searchResult == _commands.end()) throw ParseException {"invalid command"};

    std::istringstream commandParams;
    if (firstSpaceIndex != std::string::npos)
    {
        commandParams.str(line.substr(firstSpaceIndex+1));
    }

    searchResult->second(commandParams);
}

