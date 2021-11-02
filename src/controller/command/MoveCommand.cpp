
#include "MoveCommand.h"

static const std::string _name("move");
static const std::string _description =
"Arguments: {column_index}{row_index}\n"
"Example: " +
_name + " e4\n"
"Description: Moves the selected piece to the specified square if legal.";

MoveCommand::MoveCommand(Chess& chess)
    : Command(chess, _name, _description)
{
}

Result MoveCommand::apply(const std::vector<std::string>& params)
{
    if (params.size() != 1 || params[0].length() != 2)
        return { true, false };

    int row = params[0][1] - '1';
    int column = params[0][0] - 'a';

    Chess& chess = this->get_chess();
    bool error = chess.move({ row, column });
    return { error, false };
}
