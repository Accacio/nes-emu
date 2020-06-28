
#include "CPU6502Disassembler.hpp"

#define Op(opcode,name,function,mode,bytes,cycles) instructionSet[opcode]={name,function,mode,bytes,cycles}


CPU6502Disassembler::CPU6502Disassembler(){
    for (int i = 0; i < 256; i++) {
        instructionSet[i]={"???",NULL,IMMEDIATE,1,2}; // equal to nop
    }
    // *  add 1 to cycles if page boundery is crossed
    // ** add 1 to cycles if branch occurs on same page
    //    add 2 to cycles if branch occurs to different page

    // ADC https://www.masswerk.at/6502/6502_instruction_set.html#ADC
    Op(0x29, "ADC", NULL, IMMEDIATE, 2, 2); //
    Op(0x25, "ADC", NULL, ZEROPAGE, 2, 3); //
    Op(0x25, "ADC", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0x2D, "ADC", NULL, ABSOLUTE, 3, 4); //
    Op(0x3D, "ADC", NULL, ABSOLUTE_X_INDEXED, 3, 4); // *
    Op(0x39, "ADC", NULL, ABSOLUTE_Y_INDEXED, 3, 4); // *
    Op(0x21, "ADC", NULL, INDIRECT_X_INDEXED, 2, 6); //
    Op(0x31, "ADC", NULL, INDIRECT_Y_INDEXED, 2, 5); // *
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
