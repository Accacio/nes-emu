##
# nes-emulator
#
# @file
# @version 0.1
#
OBJ=main.cc cpu6502.cc
CXXFlags=-g
BIN=nes-emu
LINKER_FLAGS=-lncurses

all: $(OBJ)

	@echo "all"
	g++ $(CXXFlags)  -o $(BIN) $(LINKER_FLAGS) $^

compile:
	@echo "Compiling - Begin"
	@g++ $(CXXFlags) -O $(OBJ) $(LINKER_FLAGS) -o $(BIN)
	@echo "Compiling - Done"

%.o: %.c
	@echo "compilng"
	g++ $(CXXFlags) $(LINKER_FLAGS) $@ -c $<

run:
	@./$(BIN)
# end
clean:
	@rm -f *.o
	@rm -f $(BIN)
