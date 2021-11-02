
#include "QuitCommand.h"

static const std::string _name = "quit";
static const std::string _description =
"Arguments: [None]\n"
"Description: Quits the game.";

QuitCommand::QuitCommand(Chess& chess)
    : Command(chess, _name, _description)
{
}

Result QuitCommand::apply(const std::vector<std::string>& params)
{
    bool error = !params.empty();
    bool quit = true;
    return { error, quit };
}
