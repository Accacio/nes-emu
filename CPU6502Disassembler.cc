
#include "CPU6502Disassembler.hpp"

#define Op(opcode,name,function,mode,bytes,cycles) instructionSet[opcode]={name,function,mode,bytes,cycles}


CPU6502Disassembler::CPU6502Disassembler(){
    for (int i = 0; i < 256; i++) {
        instructionSet[i]={"???",NULL,IMMEDIATE,1,2}; // equal to nop
    }
    //HI 0
    Op(0x00, "BRK", NULL, IMPLIED, 1, 7); //https://www.masswerk.at/6502/6502_instruction_set.html#BRK

    //HI 0

    //HI 1

    //HI 2

    //HI 3

    //HI 4

    //HI 5

    //HI 6

    //HI 7
    Op(0x78, "SEI", NULL, IMPLIED, 1, 3); //https://www.masswerk.at/6502/6502_instruction_set.html#SEI
                                         
    //HI 8

    //HI 9

    //HI A

    //HI B

    //HI C

    //HI D

    //HI E

    //HI F

   


}



CPU6502Disassembler::~CPU6502Disassembler(){
    delete []instructionSet;
}
