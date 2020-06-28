
#ifndef __CARTRIDGE_H_
#define __CARTRIDGE_H_

#include <ncurses.h>
#include <iostream>
#include <cstdint>
#include "assert.h"
#include "CPU6502Disassembler.hpp"

class Cartridge {
       
        public:

                Cartridge(FILE * romFile);
                ~Cartridge();
                uint8_t *PGR;
                uint8_t *CHR;
                void printCode(WINDOW * codeWin,WINDOW * codePad, uint16_t PC);
                CPU6502Disassembler disassembler;


};

#endif // __CARTRIDGE_H_
