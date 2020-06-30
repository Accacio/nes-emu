
#ifndef __CARTRIDGE_H_
#define __CARTRIDGE_H_

#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include "assert.h"
#include "CPU6502Disassembler.hpp"

class Cartridge {
       
        public:

                Cartridge(FILE * romFile,CPU6502Disassembler * _disassembler);
                ~Cartridge();
                uint8_t *PGR;
                uint8_t *CHR;
                void printCode(WINDOW * codeWin,WINDOW * codePad, uint16_t * PC);
                CPU6502Disassembler * disassembler;
                void disassemblePGR(); // only as test
        private:
                std::vector<std::string> DISASSEMBLED_CODE;
};

#endif // __CARTRIDGE_H_
