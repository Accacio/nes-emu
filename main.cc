
#include <iostream>
#include <cstdint>
#include <ncurses.h>
#include "CPU6502.hpp"

int main(int argc, char ** argv)
{
    if (argc<=1){
        std::cout << argv[0] << ": missing ROM operand" << std::endl;
        return -1;
    }
    FILE * romFile;
    // open file as read-only and binary
    romFile = fopen(argv[1], "rb");
    if (romFile==NULL){
        std::cout << argv[0] << ": ROM file does not exist" << std::endl;
        return -1;
    }
    uint16_t addressBus;
    uint8_t dataBus;
    bool readWrite;

    CPU6502 cpu = CPU6502(&addressBus, &dataBus, &readWrite);
    initscr();
    start_color();
    noecho();
    int height, width, startX,startY;
    height = 8;
    width = 20;
    startX = 10;
    startY = 10;
    int yMax,xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW * regWin = newwin(height, xMax/4, 1, xMax*3/4-1);
    refresh();
    while (true){
        cpu.printRegistersAndFlags(regWin);
        refresh();
        cpu.testRegistersAndFlags();
        getch();
    }
    endwin();
    return(0);
}
