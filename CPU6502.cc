
#include "CPU6502.hpp"

CPU6502:: CPU6502(uint16_t * _addressBus,uint8_t * _dataBus,bool * readWrite)
{
    PC.raw=0x0000;
    addressBus = _addressBus;
    dataBus = _dataBus;
    R = (uint8_t*) readWrite;
    // X=Y=A=0;
}

CPU6502::~CPU6502(){

}

// void CPU6502::ConnectBus(Bus *_bus) { bus = _bus;}
void CPU6502::write(uint16_t address, uint8_t data){
    // bus->write(address, data);
}

uint8_t CPU6502::read(uint16_t address){
    // return bus->read(address);
    return 0x00;
}

void CPU6502::exOp(){
    // return bus->read(address);
}

void CPU6502::printRegistersAndFlags(WINDOW * regWin) {
    box(regWin, 0,0);
    init_pair(2,COLOR_WHITE,COLOR_RED);
    init_pair(3,COLOR_WHITE,100);
    init_pair(4,COLOR_WHITE,COLOR_BLUE);
    mvwprintw(regWin,0,2, " CPU Registers ");
    mvwprintw(regWin, 1, 2, "STATUS:  ");
    if (status.N) wattron(regWin, COLOR_PAIR(2));
    mvwprintw(regWin, 1, 11, "M",status.N);
    wattroff(regWin, COLOR_PAIR(2));
    use_default_colors();
    mvwprintw(regWin, 1, 12, " ");
    if (status.V) wattron(regWin, COLOR_PAIR(2));
    mvwprintw(regWin, 1, 13, "V",status.V);
    wattroff(regWin, COLOR_PAIR(2));
    use_default_colors();
    mvwprintw(regWin, 1, 14, " ");
    // if (U) wattron(regWin, COLOR_PAIR(2));
    mvwprintw(regWin, 1, 15, "-");
    // wattroff(regWin, COLOR_PAIR(2));
    // use_default_colors();
    mvwprintw(regWin, 1, 16, " ");
    if (status.B) wattron(regWin, COLOR_PAIR(2));
    mvwprintw(regWin, 1, 17, "B",status.B);
    wattroff(regWin, COLOR_PAIR(2));
    use_default_colors();
    mvwprintw(regWin, 1, 18, " ");
    if (status.D) wattron(regWin, COLOR_PAIR(2));
    mvwprintw(regWin, 1, 19, "D",status.D);
    wattroff(regWin, COLOR_PAIR(2));
    use_default_colors();
    mvwprintw(regWin, 1, 20, " ");
    if (status.I) wattron(regWin, COLOR_PAIR(2));
    mvwprintw(regWin, 1, 21, "I",status.I);
    wattroff(regWin, COLOR_PAIR(2));
    use_default_colors();
    mvwprintw(regWin, 1, 22, " ");
    if (status.Z) wattron(regWin, COLOR_PAIR(2));
    mvwprintw(regWin, 1, 23, "Z",status.Z);
    wattroff(regWin, COLOR_PAIR(2));
    use_default_colors();
    mvwprintw(regWin, 1, 24, " ");
    if (status.C) wattron(regWin, COLOR_PAIR(2));
    mvwprintw(regWin, 1, 25, "C",status.C);
    wattroff(regWin, COLOR_PAIR(2));
    use_default_colors();

    mvwprintw(regWin, 2, 2, "PC:      0x%04x",PC.raw);
    mvwprintw(regWin, 3, 2, "A:         0x%02x",A);
    mvwprintw(regWin, 4, 2, "X:         0x%02x",X);
    mvwprintw(regWin, 5, 2, "Y:         0x%02x",Y);
    mvwprintw(regWin, 6, 2, "Stack P:   0x%02x",S);
    wrefresh(regWin);
    // refresh();
}
void CPU6502::testRegistersAndFlags(){
        A++;
        X++;
        Y++;
        S++;
        PC.raw++;
        status.raw++;

}
