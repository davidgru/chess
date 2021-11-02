#pragma once

#include <map>

#include "../../model/events/EventListener.h"
#include "PieceTextures.h"
#include "Screenbuffer.h"

#include "../../controller/Command.h"

#include "../../model/ChessState.h"

class ConsoleSession : public EventListener<ChessState>
{
public:
    ConsoleSession();

    void add_command(Command *command);

    void start();

    void on_update(const ChessState &state) override;

private:
    void clear_screen();
    void show();
    void process_command();

private:
    bool over;
    Screenbuffer screenbuffer;
    std::map<std::string, Command *> commands;
};
