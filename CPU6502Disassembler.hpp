
#ifndef __CPU6502DISASSEMBLER_H_
#define __CPU6502DISASSEMBLER_H_

#include <iostream>
#include <cstdint>

class CPU6502Disassembler {
    public:
        CPU6502Disassembler();
        virtual ~CPU6502Disassembler();

        // https://www.masswerk.at/6502/6502_instruction_set.html#BNE
        enum Addressing{
        ACCUMULATOR,        // A       OPC A        operand is AC (implied single byte instruction)
        ABSOLUTE,           // abs     OPC $LLHH    operand is address $HHLL *
        ABSOLUTE_X_INDEXED, // abs,X   OPC $LLHH,X  operand is address; effective address is address incremented by X with carry **
        ABSOLUTE_Y_INDEXED, // abs,Y   OPC $LLHH,Y  operand is address; effective address is address incremented by Y with carry **
        IMMEDIATE,          // #       OPC #$BB     operand is byte BB
        IMPLIED,            // impl.   OPC          operand implied
        INDIRECT,           // ind     OPC ($LLHH)  operand is address; effective address is contents of word at address: C.w($HHLL)
        INDIRECT_X_INDEXED, // X,ind   OPC ($LL,X)  operand is zeropage address; effective address is word in (LL + X, LL + X + 1), inc. without carry: C.w($00LL + X)
        INDIRECT_Y_INDEXED, // ind,Y   OPC ($LL),Y  operand is zeropage address; effective address is word in (LL, LL + 1) incremented by Y with carry: C.w($00LL) + Y
        RELATIVE,           // rel     OPC $BB      branch target is PC + signed offset BB ***
        ZEROPAGE,           // zpg     OPC $LL      operand is zeropage address (hi-byte is zero, address = $00LL)
        ZEROPAGE_X_INDEXED, // zpg,X   OPC $LL,X    operand is zeropage address; effective address is address incremented by X without carry **
        ZEROPAGE_Y_INDEXED, // zpg,Y   OPC $LL,Y    operand is zeropage address; effective address is address incremented by Y without carry **
    };

        // addressing    assembler    opc  bytes  cyles
        struct Instruction{
            char const * assembler;
            uint8_t * function;
            Addressing addressing;
            uint8_t bytes;
            uint8_t cycles;
        };
        Instruction * instructionSet= new Instruction[256];

};

#endif // __CPU6502DISASSEMBLER_H_
