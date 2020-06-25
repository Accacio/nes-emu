
#ifndef __CPU6502_H_
#define __CPU6502_H_


#include <cstdint>
#include <array>
#include <ncurses.h>

#include "macros.h"
// #include "bus.hpp"

//http://archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
class CPU6502 {
    public:
        CPU6502(uint16_t * _addressBus,uint8_t * _dataBus,bool * _readWrite);
        ~CPU6502();

        void exOp();

        // void ConnectBus(Bus *_bus);
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t data);
        void printRegistersAndFlags(WINDOW * regWin);
        void testRegistersAndFlags();
        // Bus *bus = nullptr;
        // https://atadiat.com/en/e-embedded-c-struct-union-part-2/
        // https://www.tutorialspoint.com/cprogramming/c_bit_fields.htm
        // Page 8
        union {
            uint_least8_t raw;
            struct {
                bool C :1; // carry
                bool Z :1; // zero
                bool I :1; // interrupt enable/disable
                bool D :1; // decimal mode (unsupported on NES, but flag exists)
                bool B :1; //
                bool Unused :1; //
                bool V :1; // overflow
                bool N :1; // negative
            };
        } status;

        union {
            uint16_t raw;
            struct {
            uint8_t PCL;
            uint8_t PCH;
            };
        } PC;

        uint8_t A;
        uint8_t X;
        uint8_t Y;
        uint8_t S;

        //IO
        uint16_t * addressBus;
        uint8_t * dataBus;
        uint8_t * R; // Read R=true, Write R=false;
    private:
};

#endif // __CPU6502_H_
