#pragma once

#include <vector>
#include <string>

class CommandParser
{
public:
    // Returns true on error.
    static bool parse(const std::string &command_str, std::string &out_command_name, std::vector<std::string> &out_str_params);

private:
    CommandParser();

    static const std::string COMMAND_NAME_PATTERN;
    static const std::string PARAMETER_PATTERN;
    static const std::string MULTIPLE_PARAMETER_PATTERN;
    static const std::string COMMAND_PATTERN;
};
