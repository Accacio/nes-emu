
#include "CPU6502Disassembler.hpp"

#define Op(opcode,name,function,mode,bytes,cycles) instructionSet[opcode]={name,function,mode,bytes,cycles}


CPU6502Disassembler::CPU6502Disassembler(){
    for (int i = 0; i < 256; i++) {
        instructionSet[i]={"???",NULL,IMMEDIATE,1,2}; // equal to nop
    }

    instructionList[0x00]={"BRK",1,7};
    instructionList[0x78]={"SEI",1,3};


    std::cout << "hello from disassembler const " << instructionList[1].assembler << std::endl;
}



CPU6502Disassembler::~CPU6502Disassembler(){
    std::cout << "hello from disassembler dst " << instructionList[0].assembler << std::endl;
    delete []instructionList;
}
