
#include "CommandParser.h"

#include <regex>

const std::string CommandParser::COMMAND_NAME_PATTERN = "[a-z]+";
const std::string CommandParser::PARAMETER_PATTERN = "[a-z0-9]+";
const std::string CommandParser::MULTIPLE_PARAMETER_PATTERN = PARAMETER_PATTERN + "(?: " + PARAMETER_PATTERN + ")*";
const std::string CommandParser::COMMAND_PATTERN = "(" + COMMAND_NAME_PATTERN + ")(?: (" + MULTIPLE_PARAMETER_PATTERN + "))?";

/*static*/ bool CommandParser::parse(const std::string &command_str, std::string &out_command_name, std::vector<std::string> &out_str_params)
{
    static const std::regex command_name_regex(COMMAND_NAME_PATTERN);
    static const std::regex parameter_regex(PARAMETER_PATTERN);
    static const std::regex command_regex(COMMAND_PATTERN);

    // Check if command has the correct pattern.
    if (!std::regex_match(command_str, command_regex))
        return true;

    std::smatch m;

    // Extract command name.
    std::regex_search(command_str, m, command_name_regex);
    out_command_name = m.str();

    // Extract params.
    std::string param_str = m.suffix().str();
    while (std::regex_search(param_str, m, parameter_regex))
    {
        out_str_params.emplace_back(m.str());
        param_str = m.suffix().str();
    }
    return false;
}

CommandParser::CommandParser()
{
}