BIN = main.exe

CFLAGS = -g -O0 -std=c++1z  -Wall -Wextra -Wconversion
LDFLAGS = 
SRC = \
	controller/Command.cpp controller/command/MoveCommand.cpp controller/command/QuitCommand.cpp \
	controller/command/SelectCommand.cpp \
	\
	model/Chess.cpp \
	model/misc/DirectionSpecSupplier.cpp \
	model/position/Position.cpp model/Position/CastlingRights.cpp \
	model/color/ColorSpecSupplier.cpp \
	model/piece/PieceHandler.cpp model/piece/PieceHandlerSupplier.cpp \
	model/piece/piecehandler/BishopHandler.cpp model/piece/piecehandler/KingHandler.cpp model/piece/piecehandler/KnightHandler.cpp \
	model/piece/piecehandler/NullHandler.cpp model/piece/piecehandler/PawnHandler.cpp model/piece/piecehandler/QueenHandler.cpp \
	model/piece/piecehandler/RookHandler.cpp model/piece/piecehandler/StraightMovingPieceHandler.cpp \
	\
	view/console_view/CommandParser.cpp view/console_view/ConsoleSession.cpp \
	view/console_view/PieceTextures.cpp view/console_view/Screenbuffer.cpp \
	\
	main.cpp

$(BIN): $(SRC)
	g++ $(CFLAGS) $(LDFLAGS) -o $@ $^ 

clean:
	del $(BIN)

rebuild:
	make clean && make