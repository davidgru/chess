
#include "ConsoleSession.h"

#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iostream>

#include "CommandParser.h"

ConsoleSession::ConsoleSession()
    : over(false)
{
}

void ConsoleSession::add_command(Command* command)
{
    this->commands[command->get_name()] = command;
}

void ConsoleSession::start()
{
    while (!this->over) {
        this->clear_screen();
        this->show();
        this->process_command();
    }
}

void ConsoleSession::on_update(const ChessState& state)
{
    std::vector<std::pair<std::string, std::string>> command_descs;
    for (const auto& [name, cmd] : this->commands) {
        std::pair<std::string, std::string> p = { name, cmd->get_description() };
        command_descs.push_back(p);
    }

    this->screenbuffer.redraw(state, command_descs);
}

void ConsoleSession::clear_screen()
{
#if defined(_WIN32)
    system("cls");
#elif defined(__unix__)
    std::cout << "\x1B[2J\x1B[H";
#else
#error Please implement your own console-clear function.
#endif
}

void ConsoleSession::show()
{
    auto frame = this->screenbuffer.get_frame();
    std::cout << frame;
}

void ConsoleSession::process_command()
{
    char input[1024];
    std::cout << "Your command: ";
    std::cin.getline(input, 1024);

    std::string input_str(input);

    std::string command_name;
    std::vector<std::string> param_strs;

    if (CommandParser::parse(input_str, command_name, param_strs))
        return;

    Command* command = this->commands[command_name];
    if (command == nullptr)
        return;
    Result result = command->apply(param_strs);
    if (result.quit)
        this->over = true;
}
