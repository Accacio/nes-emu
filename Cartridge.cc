
#include "Cartridge.hpp"


Cartridge::Cartridge(FILE * romFile,CPU6502Disassembler * _disassembler){
    disassembler = _disassembler;
// https://wiki.nesdev.com/w/index.php/NES_2.0

    // NES HEADER
    // nes roms begin with 'NES 1a'
    // 0-3    Identification String. Must be "NES<EOF>".
    assert(fgetc(romFile)=='N' && fgetc(romFile)=='E' && fgetc(romFile)=='S' && fgetc(romFile)==26);
    // 4      PRG-ROM size LSB // Code
    uint8_t PRG_ROM_LSB = fgetc(romFile);
    // 5      CHR-ROM size LSB // Graphics
    uint8_t CHR_ROM_LSB = fgetc(romFile);

    // 6      Flags 6
    //    D~7654 3210
    //      ---------
    //      NNNN FTBM
    //      |||| |||+-- Hard-wired nametable mirroring type
    //      |||| |||     0: Horizontal or mapper-controlled
    //      |||| |||     1: Vertical
    //      |||| ||+--- "Battery" and other non-volatile memory
    //      |||| ||      0: Not present
    //      |||| ||      1: Present
    //      |||| |+--- 512-byte Trainer
    //      |||| |      0: Not present
    //      |||| |      1: Present between Header and PRG-ROM data
    //      |||| +---- Hard-wired four-screen mode
    //      ||||        0: No
    //      ||||        1: Yes
    //      ++++------ Mapper Number D0..D3
    uint8_t Flags6 = fgetc(romFile); // ignored for now

    // 7      Flags 7
    //    D~7654 3210
    //      ---------
    //      NNNN 10TT
    //      |||| ||++- Console type
    //      |||| ||     0: Nintendo Entertainment System/Family Computer
    //      |||| ||     1: Nintendo Vs. System
    //      |||| ||     2: Nintendo Playchoice 10
    //      |||| ||     3: Extended Console Type
    //      |||| ++--- NES 2.0 identifier
    //      ++++------ Mapper Number D4..D7
    uint8_t Flags7 = fgetc(romFile); // ignored for now

    // 8      Mapper MSB/Submapper
    //    D~7654 3210
    //      ---------
    //      SSSS NNNN
    //      |||| ++++- Mapper number D8..D11
    //      ++++------ Submapper number
    uint8_t Mapper_MSB__SUBMAPPER = fgetc(romFile); // ignored for now

    // 9      PRG-ROM/CHR-ROM size MSB
    // D~7654 3210
    //   ---------
    //   CCCC PPPP
    //   |||| ++++- PRG-ROM size MSB
    //   ++++------ CHR-ROM size MSB
    fgetc(romFile);// ignored for now

    // 10     PRG-RAM/EEPROM size
    //    D~7654 3210
    //      ---------
    //      pppp PPPP
    //      |||| ++++- PRG-RAM (volatile) shift count
    //      ++++------ PRG-NVRAM/EEPROM (non-volatile) shift count
    //    If the shift count is zero, there is no PRG-(NV)RAM.
    //    If the shift count is non-zero, the actual size is
    //    "64 << shift count" bytes, i.e. 8192 bytes for a shift count of 7.
    fgetc(romFile);// ignored for now

    // 11     CHR-RAM size
    //    D~7654 3210
    //      ---------
    //      cccc CCCC
    //      |||| ++++- CHR-RAM size (volatile) shift count
    //      ++++------ CHR-NVRAM size (non-volatile) shift count
    //    If the shift count is zero, there is no CHR-(NV)RAM.
    //    If the shift count is non-zero, the actual size is
    //    "64 << shift count" bytes, i.e. 8192 bytes for a shift count of 7.
    fgetc(romFile);// ignored for now

    // 12     CPU/PPU Timing
    //    D~7654 3210
    //      ---------
    //      .... ..VV
    //             ++- CPU/PPU timing mode
    //                  0: RP2C02 ("NTSC NES")
    //                  1: RP2C07 ("Licensed PAL NES")
    //                  2: Multiple-region
    //                  3: UMC 6527P ("Dendy")
    fgetc(romFile);// ignored for now

    // 13     When Byte 7 AND 3 =1: Vs. System Type
    //    D~7654 3210
    //      ---------
    //      MMMM PPPP
    //      |||| ++++- Vs. PPU Type
    //      ++++------ Vs. Hardware Type

    //    When Byte 7 AND 3 =3: Extended Console Type
    //    D~7654 3210
    //      ---------
    //      .... CCCC
    //           ++++- Extended Console Type
    fgetc(romFile);// ignored for now

    // 14     Miscellaneous ROMs
    //    D~7654 3210
    //      ---------
    //      .... ..RR
    //             ++- Number of miscellaneous ROMs present
    fgetc(romFile);// ignored for now

    // 15     Default Expansion Device
    //    D~7654 3210
    //      ---------
    //      ..DD DDDD
    //        ++-++++- Default Expansion Device
    fgetc(romFile);// ignored for now

    // printf("%d",fgetc(romFile));
    // fseek(romFile, 3L,SEEK_SET);
    // printf("%d",fgetc(romFile));
    //
    // print Header 
    // printf("%u * 16kB ROM, %u * 8kB VROM, mapper %u, ctrlbyte %02X\n", PRG_ROM_LSB , vrom8count, mappernum, ctrlbyte);
    printf("%u * 16kB ROM, %u * 8kB VROM\n", PRG_ROM_LSB , CHR_ROM_LSB);
    // resize arrays if needed
    PGR = new uint8_t[PRG_ROM_LSB*0x4000];
    CHR = new uint8_t[CHR_ROM_LSB*0x2000];
    // printf("size of PGR is %d",sizeof(PGR));
    // if(rom16count) GamePak::ROM.resize(rom16count * 0x4000); // ignored
    // if(vrom8count) GamePak::VRAM.resize(vrom8count * 0x2000); //ignored
    
    // Read the PGR data
    fread(&PGR[0], PRG_ROM_LSB, 0x4000, romFile);

    // Read the CHR data
    fread(&CHR[0], CHR_ROM_LSB, 0x2000, romFile);

    // int i = 0x1FFF;
    // printf("value in PGR[%d] is %0x",i,PGR[i]);

    // int j = 0x6f;
    // printf("value in CHR[%d] is %4x",j,CHR[j]);
    // fread(&GamePak::VRAM[0], vrom8count, 0x2000, fp);
    disassemblePGR();
}

Cartridge::~Cartridge(){
    delete PGR;
    delete CHR;
}

void Cartridge::disassemblePGR(){
    std::string line;
    for (int i = 0; i < 0x1000; i+=disassembler->instructionSet[PGR[i]].bytes) {
        const char *name=disassembler->instructionSet[PGR[i]].assembler;
        int bytes=disassembler->instructionSet[PGR[i]].bytes;
        std::string numbers = "";
        line =  "";
        char number[4];
        sprintf(number, "%04x",i);
        line += number ;
        line+=  ": ";
        line += name;
        line += " ";
        if(bytes>1){
            char number2[4];
            if (bytes==2) {
                sprintf(number, "%02x",PGR[i+1]);
                numbers += number;
            }
            else if (bytes==3) {
            sprintf(number, "%02x",PGR[i+1]);
            sprintf(number2, "%02x",PGR[i+2]);
                numbers += number2;
                numbers += number; }
        }
        line+=numbers;

        line += "\n";
        DISASSEMBLED_CODE.push_back(line);
        for (int j=0; j < bytes-1; j++) {
            DISASSEMBLED_CODE.push_back("");
        }
    }
}


void Cartridge::printCode(WINDOW *codeWin,WINDOW *codePad,uint16_t * PC)
{
    wclear(codePad);
    box(codeWin, 0,0);
    init_pair(2,COLOR_WHITE,COLOR_RED);
    init_pair(3,COLOR_WHITE,100);
    init_pair(4,COLOR_WHITE,COLOR_BLUE);
   
    use_default_colors();
    mvwprintw(codeWin,0,2, " Code ");

    for (int i = 0; i <DISASSEMBLED_CODE.size();i++)
    {
        if(i==*PC) wattron(codePad, COLOR_PAIR(4));
        wprintw(codePad, DISASSEMBLED_CODE[i].c_str());
        if(i==*PC) wattroff(codePad, COLOR_PAIR(4));
    }
    // wattron(codePad, COLOR_PAIR(4));
    // wprintw(codePad, disassembler->instructionSet[0x00].assembler);
    // wprintw(codePad, "\n");
    // wattroff(codePad, COLOR_PAIR(4));
    // wprintw(codePad, disassembler->instructionSet[PGR[*PC]].assembler);
    *PC+=disassembler->instructionSet[PGR[*PC]].bytes-1;
    // wprintw(codePad, "%d",PC);
    // char* text;

    // sprintf(text, "%x",newPC);
    // wprintw(codePad,text);
    mvwchgat(codePad, 1, 0, -1, A_NORMAL, 0, NULL);

    wrefresh(codeWin);
    prefresh(codePad, 0, 0, codeWin->_begy+1, codeWin->_begx+1, codeWin->_begy+codeWin->_maxy-1, codeWin->_begx+codeWin->_maxx-1);
}
