
#include <memory>

#include "controller/Command.h"
#include "controller/command/MoveCommand.h"
#include "controller/command/QuitCommand.h"
#include "controller/command/SelectCommand.h"

#include "model/Chess.h"

#include "view/console_view/ConsoleSession.h"

int main() {
  Chess chess;

  std::unique_ptr<Command> select_command =
      std::make_unique<SelectCommand>(chess);
  std::unique_ptr<Command> move_command = std::make_unique<MoveCommand>(chess);
  std::unique_ptr<Command> quit_command = std::make_unique<QuitCommand>(chess);

  ConsoleSession session;
  session.add_command(select_command.get());
  session.add_command(move_command.get());
  session.add_command(quit_command.get());

  chess.add_event_listener(&session);
  chess.request_update();

  session.start();
}
