
#include "CPU6502Disassembler.hpp"

#define Op(opcode,name,function,mode,bytes,cycles) instructionSet[opcode]={name,function,mode,bytes,cycles}


CPU6502Disassembler::CPU6502Disassembler(){
    std::cout << "Disassembler Constructor";

    for (int i = 0; i < 256; i++) {
        Op(i,"???",NULL,IMMEDIATE,1,2); // equal to nop
    }
    // *  add 1 to cycles if page boundery is crossed
    // ** add 1 to cycles if branch occurs on same page
    //    add 2 to cycles if branch occurs to different page

    // ADC https://www.masswerk.at/6502/6502_instruction_set.html#ADC
    Op(0x69, "ADC", NULL, IMMEDIATE, 2, 2); //
    Op(0x65, "ADC", NULL, ZEROPAGE, 2, 3); //
    Op(0x75, "ADC", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0x6D, "ADC", NULL, ABSOLUTE, 3, 4); //
    Op(0x7D, "ADC", NULL, ABSOLUTE_X_INDEXED, 3, 4); // *
    Op(0x79, "ADC", NULL, ABSOLUTE_Y_INDEXED, 3, 4); // *
    Op(0x61, "ADC", NULL, INDIRECT_X_INDEXED, 2, 6); //
    Op(0x71, "ADC", NULL, INDIRECT_Y_INDEXED, 2, 5); // *

    // AND https://www.masswerk.at/6502/6502_instruction_set.html#AND
    Op(0x29, "AND", NULL, IMMEDIATE, 2, 2); //
    Op(0x25, "AND", NULL, ZEROPAGE, 2, 3); //
    Op(0x35, "AND", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0x2D, "AND", NULL, ABSOLUTE, 3, 4); //
    Op(0x3D, "AND", NULL, ABSOLUTE_X_INDEXED, 3, 4); // *
    Op(0x39, "AND", NULL, ABSOLUTE_Y_INDEXED, 3, 4); // *
    Op(0x21, "AND", NULL, INDIRECT_X_INDEXED, 2, 6); //
    Op(0x31, "AND", NULL, INDIRECT_Y_INDEXED, 2, 5); // *


    // ASL https://www.masswerk.at/6502/6502_instruction_set.html#ASL
    Op(0x0A, "ASL", NULL, ACCUMULATOR, 1, 2); //
    Op(0x06, "ASL", NULL, ZEROPAGE, 2, 5); //
    Op(0x16, "ASL", NULL, ZEROPAGE_X_INDEXED, 2, 6); //
    Op(0x0E, "ASL", NULL, ABSOLUTE, 3, 6); //
    Op(0x1E, "ASL", NULL, ABSOLUTE_X_INDEXED, 3, 7); //


    // BCC https://www.masswerk.at/6502/6502_instruction_set.html#BCC
    Op(0x90, "BCC", NULL, RELATIVE, 2, 2); // **


    // BCS https://www.masswerk.at/6502/6502_instruction_set.html#BCS
    Op(0xB0, "BCS", NULL, RELATIVE, 2, 2); // **

    // BEQ https://www.masswerk.at/6502/6502_instruction_set.html#BEQ
    Op(0xF0, "BEQ", NULL, RELATIVE, 2, 2); // **


    // BIT https://www.masswerk.at/6502/6502_instruction_set.html#BIT
    Op(0x24, "BIT", NULL, ZEROPAGE, 2, 3); //
    Op(0x2C, "BIT", NULL, ABSOLUTE, 3, 4); //


    // BMI https://www.masswerk.at/6502/6502_instruction_set.html#BMI
    Op(0x30, "BMI", NULL, RELATIVE, 2, 2); // **

    // BNE https://www.masswerk.at/6502/6502_instruction_set.html#BNE
    Op(0xD0, "BNE", NULL, RELATIVE, 2, 2); // **

    // BPL https://www.masswerk.at/6502/6502_instruction_set.html#BPL
    Op(0x10, "BPL", NULL, RELATIVE, 2, 2); // **

    // BRK https://www.masswerk.at/6502/6502_instruction_set.html#BRK
    Op(0x00, "BRK", NULL, IMPLIED, 1, 7); //

    // BVC https://www.masswerk.at/6502/6502_instruction_set.html#BVC
    Op(0x50, "BVC", NULL, RELATIVE, 2, 2); // **

    // BVS https://www.masswerk.at/6502/6502_instruction_set.html#BVS
    Op(0x70, "BVS", NULL, RELATIVE, 2, 2); // **

    // CLC https://www.masswerk.at/6502/6502_instruction_set.html#CLC
    Op(0x18, "CLC", NULL, IMPLIED, 1, 2); //


    // CLD https://www.masswerk.at/6502/6502_instruction_set.html#CLD
    Op(0xD8, "CLD", NULL, IMPLIED, 1, 2); //


    // CLI https://www.masswerk.at/6502/6502_instruction_set.html#CLI
    Op(0x58, "CLI", NULL, IMPLIED, 1, 2); //

    // CLV https://www.masswerk.at/6502/6502_instruction_set.html#CLV
    Op(0xB8, "CLV", NULL, IMPLIED, 1, 2); //

    // CMP https://www.masswerk.at/6502/6502_instruction_set.html#CMP
    Op(0xC9, "CMP", NULL, IMMEDIATE, 2, 2); //
    Op(0xC5, "CMP", NULL, ZEROPAGE, 2, 3); //
    Op(0xD5, "CMP", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0xCD, "CMP", NULL, ABSOLUTE, 3, 4); //
    Op(0xDD, "CMP", NULL, ABSOLUTE_X_INDEXED, 3, 4); // *
    Op(0xD9, "CMP", NULL, ABSOLUTE_Y_INDEXED, 3, 4); // *
    Op(0xC1, "CMP", NULL, INDIRECT_X_INDEXED, 2, 6); //
    Op(0xD1, "CMP", NULL, INDIRECT_Y_INDEXED, 2, 5); // *

    // CPX https://www.masswerk.at/6502/6502_instruction_set.html#CPX
    Op(0xE0, "CPX", NULL, IMMEDIATE, 2, 2); //
    Op(0xE4, "CPX", NULL, ZEROPAGE, 2, 3); //
    Op(0xEC, "CPX", NULL, ABSOLUTE, 3, 4); //

    // CPY https://www.masswerk.at/6502/6502_instruction_set.html#CPY
    Op(0xC0, "CPY", NULL, IMMEDIATE, 2, 2); //
    Op(0xC4, "CPY", NULL, ZEROPAGE, 2, 3); //
    Op(0xCC, "CPY", NULL, ABSOLUTE, 3, 4); //

    // DEC https://www.masswerk.at/6502/6502_instruction_set.html#DEC
    Op(0xC6, "DEC", NULL, ZEROPAGE, 2, 5); //
    Op(0xD6, "DEC", NULL, ZEROPAGE_X_INDEXED, 2, 6); //
    Op(0xCE, "DEC", NULL, ABSOLUTE, 3, 6); //
    Op(0xDE, "DEC", NULL, ABSOLUTE_X_INDEXED, 3, 7); //

    // DEX https://www.masswerk.at/6502/6502_instruction_set.html#DEX
    Op(0xCA, "DEX", NULL, IMPLIED, 1, 2); //

    // DEY https://www.masswerk.at/6502/6502_instruction_set.html#DEY
    Op(0x88, "DEY", NULL, IMPLIED, 1, 2); //

    // EOR https://www.masswerk.at/6502/6502_instruction_set.html#EOR
    Op(0x49, "EOR", NULL, IMMEDIATE, 2, 2); //
    Op(0x45, "EOR", NULL, ZEROPAGE, 2, 3); //
    Op(0x55, "EOR", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0x4D, "EOR", NULL, ABSOLUTE, 3, 4); //
    Op(0x5D, "EOR", NULL, ABSOLUTE_X_INDEXED, 3, 4); // *
    Op(0x59, "EOR", NULL, ABSOLUTE_Y_INDEXED, 3, 4); // *
    Op(0x41, "EOR", NULL, INDIRECT_X_INDEXED, 2, 6); //
    Op(0x51, "EOR", NULL, INDIRECT_Y_INDEXED, 2, 5); // *

    // INC https://www.masswerk.at/6502/6502_instruction_set.html#INC
    Op(0xE6, "INC", NULL, ZEROPAGE, 2, 5); //
    Op(0xF6, "INC", NULL, ZEROPAGE_X_INDEXED, 2, 6); //
    Op(0xEE, "INC", NULL, ABSOLUTE, 3, 6); //
    Op(0xFE, "INC", NULL, ABSOLUTE_X_INDEXED, 3, 7); //

    // INX https://www.masswerk.at/6502/6502_instruction_set.html#INX
    Op(0xE8, "INX", NULL, IMPLIED, 1, 2); //

    // INY https://www.masswerk.at/6502/6502_instruction_set.html#INY
    Op(0xC8, "INY", NULL, IMPLIED, 1, 2); //

    // JMP https://www.masswerk.at/6502/6502_instruction_set.html#JMP
    Op(0x4C, "JMP", NULL, ABSOLUTE, 3, 3); //
    Op(0x6C, "JMP", NULL, INDIRECT, 3, 5); //

    // JSR https://www.masswerk.at/6502/6502_instruction_set.html#JSR
    Op(0x20, "JSR", NULL, ABSOLUTE, 3, 6); //


    // LDA https://www.masswerk.at/6502/6502_instruction_set.html#LDA
    Op(0xA9, "LDA", NULL, IMMEDIATE, 2, 2); //
    Op(0xA5, "LDA", NULL, ZEROPAGE, 2, 3); //
    Op(0xB5, "LDA", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0xAD, "LDA", NULL, ABSOLUTE, 3, 4); //
    Op(0xBD, "LDA", NULL, ABSOLUTE_X_INDEXED, 3, 4); // *
    Op(0xB9, "LDA", NULL, ABSOLUTE_Y_INDEXED, 3, 4); // *
    Op(0xA1, "LDA", NULL, INDIRECT_X_INDEXED, 2, 6); //
    Op(0xB1, "LDA", NULL, INDIRECT_Y_INDEXED, 2, 5); // *


    // LDX https://www.masswerk.at/6502/6502_instruction_set.html#LDX
    Op(0xA2, "LDX", NULL, IMMEDIATE, 2, 2); //
    Op(0xA6, "LDX", NULL, ZEROPAGE, 2, 3); //
    Op(0xB6, "LDX", NULL, ZEROPAGE_Y_INDEXED, 2, 4); //
    Op(0xAE, "LDX", NULL, ABSOLUTE, 3, 4); //
    Op(0xBE, "LDX", NULL, ABSOLUTE_Y_INDEXED, 3, 4); // *

    // LDY https://www.masswerk.at/6502/6502_instruction_set.html#LDY
    Op(0xA0, "LDY", NULL, IMMEDIATE, 2, 2); //
    Op(0xA4, "LDY", NULL, ZEROPAGE, 2, 3); //
    Op(0xB4, "LDY", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0xAC, "LDY", NULL, ABSOLUTE, 3, 4); //
    Op(0xBC, "LDY", NULL, ABSOLUTE_X_INDEXED, 3, 4); // *


    // LSR https://www.masswerk.at/6502/6502_instruction_set.html#LSR
    Op(0x4A, "LSR", NULL, ACCUMULATOR, 1, 2); //
    Op(0x46, "LSR", NULL, ZEROPAGE, 2, 5); //
    Op(0x56, "LSR", NULL, ZEROPAGE_X_INDEXED, 2, 6); //
    Op(0x4E, "LSR", NULL, ABSOLUTE, 3, 6); //
    Op(0x5E, "LSR", NULL, ABSOLUTE_X_INDEXED, 3, 7); //

    // NOP https://www.masswerk.at/6502/6502_instruction_set.html#NOP
    Op(0xEA, "NOP", NULL, IMPLIED, 1, 2);

    // ORA https://www.masswerk.at/6502/6502_instruction_set.html#ORA
    Op(0x09, "ORA", NULL, IMMEDIATE, 2, 2); //
    Op(0x05, "ORA", NULL, ZEROPAGE, 2, 3); //
    Op(0x15, "ORA", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0x0D, "ORA", NULL, ABSOLUTE, 3, 4); //
    Op(0x1D, "ORA", NULL, ABSOLUTE_X_INDEXED, 3, 4); // *
    Op(0x19, "ORA", NULL, ABSOLUTE_Y_INDEXED, 3, 4); // *
    Op(0x01, "ORA", NULL, INDIRECT_X_INDEXED, 2, 6); //
    Op(0x11, "ORA", NULL, INDIRECT_Y_INDEXED, 2, 5); // *

    // PHA https://www.masswerk.at/6502/6502_instruction_set.html#PHA
    Op(0x48, "PHA", NULL, IMPLIED, 1, 3);

    // PHP https://www.masswerk.at/6502/6502_instruction_set.html#PHP
    Op(0x08, "PHP", NULL, IMPLIED, 1, 3);

    // PLA https://www.masswerk.at/6502/6502_instruction_set.html#PLA
    Op(0x68, "PLA", NULL, IMPLIED, 1, 4);

    // PLP https://www.masswerk.at/6502/6502_instruction_set.html#PLP
    Op(0x28, "PLP", NULL, IMPLIED, 1, 4);

    // ROL https://www.masswerk.at/6502/6502_instruction_set.html#ROL
    Op(0x2A, "ROL", NULL, ACCUMULATOR, 1, 2); //
    Op(0x26, "ROL", NULL, ZEROPAGE, 2, 5); //
    Op(0x36, "ROL", NULL, ZEROPAGE_X_INDEXED, 2, 6); //
    Op(0x2E, "ROL", NULL, ABSOLUTE, 3, 6); //
    Op(0x3E, "ROL", NULL, ABSOLUTE_X_INDEXED, 3, 7); //

    // ROR https://www.masswerk.at/6502/6502_instruction_set.html#ROR
    Op(0x6A, "ROR", NULL, ACCUMULATOR, 1, 2); //
    Op(0x66, "ROR", NULL, ZEROPAGE, 2, 5); //
    Op(0x76, "ROR", NULL, ZEROPAGE_X_INDEXED, 2, 6); //
    Op(0x6E, "ROR", NULL, ABSOLUTE, 3, 6); //
    Op(0x7E, "ROR", NULL, ABSOLUTE_X_INDEXED, 3, 7); //

    // RTI https://www.masswerk.at/6502/6502_instruction_set.html#RTI
    Op(0x40, "RTI", NULL, IMPLIED, 1, 6);

    // RTS https://www.masswerk.at/6502/6502_instruction_set.html#RTS
    Op(0x60, "RTS", NULL, IMPLIED, 1, 6);

    // SBC https://www.masswerk.at/6502/6502_instruction_set.html#SBC
    Op(0xE9, "SBC", NULL, IMMEDIATE, 2, 2); //
    Op(0xE5, "SBC", NULL, ZEROPAGE, 2, 3); //
    Op(0xF5, "SBC", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0xED, "SBC", NULL, ABSOLUTE, 3, 4); //
    Op(0xFD, "SBC", NULL, ABSOLUTE_X_INDEXED, 3, 4); // *
    Op(0xF9, "SBC", NULL, ABSOLUTE_Y_INDEXED, 3, 4); // *
    Op(0xE1, "SBC", NULL, INDIRECT_X_INDEXED, 2, 6); //
    Op(0xF1, "SBC", NULL, INDIRECT_Y_INDEXED, 2, 5); // *


    // SEC https://www.masswerk.at/6502/6502_instruction_set.html#SEC
    Op(0x38, "SEC", NULL, IMPLIED, 1, 2); //

    // SED https://www.masswerk.at/6502/6502_instruction_set.html#SED
    Op(0xF8, "SED", NULL, IMPLIED, 1, 2); //

    // SEI https://www.masswerk.at/6502/6502_instruction_set.html#SEI
    Op(0x78, "SEI", NULL, IMPLIED, 1, 2); //

    // STA https://www.masswerk.at/6502/6502_instruction_set.html#STA
    Op(0x85, "STA", NULL, ZEROPAGE, 2, 3); //
    Op(0x95, "STA", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0x8D, "STA", NULL, ABSOLUTE, 3, 4); //
    Op(0x9D, "STA", NULL, ABSOLUTE_X_INDEXED, 3, 5); //
    Op(0x99, "STA", NULL, ABSOLUTE_Y_INDEXED, 3, 5); //
    Op(0x81, "STA", NULL, INDIRECT_X_INDEXED, 2, 6); //
    Op(0x91, "STA", NULL, INDIRECT_Y_INDEXED, 2, 6); //

    // STX https://www.masswerk.at/6502/6502_instruction_set.html#STX
    Op(0x86, "STX", NULL, ZEROPAGE, 2, 3); //
    Op(0x96, "STX", NULL, ZEROPAGE_Y_INDEXED, 2, 4); //
    Op(0x8E, "STX", NULL, ABSOLUTE, 3, 4); //

    // STY https://www.masswerk.at/6502/6502_instruction_set.html#STY
    Op(0x84, "STY", NULL, ZEROPAGE, 2, 3); //
    Op(0x94, "STY", NULL, ZEROPAGE_X_INDEXED, 2, 4); //
    Op(0x8C, "STY", NULL, ABSOLUTE, 3, 4); //

    // TAX https://www.masswerk.at/6502/6502_instruction_set.html#TAX
    Op(0xAA, "TAX", NULL, IMPLIED, 1, 2); //

    // TAY https://www.masswerk.at/6502/6502_instruction_set.html#TAY
    Op(0xA8, "TAY", NULL, IMPLIED, 1, 2); //

    // TSX https://www.masswerk.at/6502/6502_instruction_set.html#TSX
    Op(0xBA, "TSX", NULL, IMPLIED, 1, 2); //

    // TXA https://www.masswerk.at/6502/6502_instruction_set.html#TXA
    Op(0x8A, "TXA", NULL, IMPLIED, 1, 2); //

    // TXS https://www.masswerk.at/6502/6502_instruction_set.html#TXS
    Op(0x9A, "TXS", NULL, IMPLIED, 1, 2); //

    // TYA https://www.masswerk.at/6502/6502_instruction_set.html#TYA
    Op(0x98, "TYA", NULL, IMPLIED, 1, 2); //

}



CPU6502Disassembler::~CPU6502Disassembler(){
    delete []instructionSet;
}
