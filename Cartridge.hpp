
#ifndef __CARTRIDGE_H_
#define __CARTRIDGE_H_

#include <ncurses.h>
#include <iostream>
#include "assert.h"

class Cartridge {
    public:
        Cartridge(FILE * romFile);
        ~Cartridge();
        uint8_t *PGR;
        uint8_t *CHR;
        // uint16_t *CHR[0x2000];
        void printCode(WINDOW * codeWin, uint16_t PC);
};

#endif // __CARTRIDGE_H_
