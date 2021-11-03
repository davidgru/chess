CXX := clang++

BIN := chess.exe

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

TARGET := $(BIN_DIR)/$(BIN)

SRC_EXT := cpp

_SRC := \
	main.cpp \
	\
	controller/Command.cpp \
	controller/command/MoveCommand.cpp controller/command/QuitCommand.cpp controller/command/SelectCommand.cpp \
	\
	model/Chess.cpp \
	model/color/ColorSpecSupplier.cpp \
	model/misc/DirectionSpecSupplier.cpp \
	model/piece/PieceHandler.cpp model/piece/PieceHandlerSupplier.cpp \
	model/piece/piecehandler/BishopHandler.cpp model/piece/piecehandler/KingHandler.cpp model/piece/piecehandler/KnightHandler.cpp model/piece/piecehandler/PawnHandler.cpp \
	model/piece/piecehandler/QueenHandler.cpp model/piece/piecehandler/RookHandler.cpp model/piece/piecehandler/StraightMovingPieceHandler.cpp \
	model/position/CastlingRights.cpp model/position/Position.cpp \
	\
	view/console_view/CommandParser.cpp view/console_view/ConsoleSession.cpp view/console_view/PieceTextures.cpp view/console_view/Screenbuffer.cpp

SRC := $(addprefix $(SRC_DIR)/, $(_SRC))
OBJ := $(addprefix $(OBJ_DIR)/, $(_SRC:.$(SRC_EXT)=.o))

CPPFLAGS :=
CFLAGS := -std=c++17 -O3 -Werror -Wall -Wextra
LDFLAGS :=
LDLIBS :=

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all: $(TARGET)

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

rebuild:
	make clean && make

.PHONY: all clean rebuild

-include $(OBJ:.o=.d)
