
#ifndef __CPU6502_H_
#define __CPU6502_H_


#include <cstdint>
#include <ncurses.h>
class cpu6502 {
    public:
        cpu6502();
        ~cpu6502();

        void printRegistersAndFlags(WINDOW * regWin);
// https://www.tutorialspoint.com/cprogramming/c_bit_fields.htm
    typedef union {
        uint_least8_t all;
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
    } StatusFlags;
        StatusFlags status;
        uint8_t pc;
        uint8_t a;
        uint8_t x;
        uint8_t y;
        uint16_t stack;

    private:
};

#endif // __CPU6502_H_
