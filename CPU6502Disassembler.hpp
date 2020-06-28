
#ifndef __CPU6502DISASSEMBLER_H_
#define __CPU6502DISASSEMBLER_H_

#include <iostream>
#include <cstdint>

class CPU6502Disassembler {
    public:
        CPU6502Disassembler();
        virtual ~CPU6502Disassembler();

        // https://www.masswerk.at/6502/6502_instruction_set.html#LDA
        // addressing    assembler    opc  bytes  cyles
        struct Instruction{
            char const * assembler;
            uint8_t * function;
            Addressing addressing;
            uint8_t bytes;
            uint8_t cycles;
        };
        Instruction * instructionList= new Instruction[256];

};

#endif // __CPU6502DISASSEMBLER_H_
