##
# nes-emulator
#
# @file
# @version 0.1
#
SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)
CXXFlags=-g
BIN=nes-emu
LINKER_FLAGS=-lncurses

all: $(OBJ)

	@echo "all"
	g++ $(CXXFlags)  -o $(BIN) $^ $(LINKER_FLAGS)

compile:
	@echo "Compiling - Begin"
	@g++ $(CXXFlags) -O $(OBJ) $(LINKER_FLAGS) -o $(BIN)
	@echo "Compiling - Done"

%.o: %.c
	@echo "compilng"
	g++ $(CXXFlags) $@ -c $<

run:
	@./$(BIN)
# end
clean:
	@rm -f *.o
	@rm -f $(BIN)
