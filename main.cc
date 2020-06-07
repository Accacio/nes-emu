
#include <iostream>
#include <ncurses.h>
#include "cpu6502.hpp"

int main(void)
{
    cpu6502 cpu = cpu6502();
    initscr();
    int height, width, startX,startY;
    height = 8;
    width = 20;
    startX = 10;
    startY = 10;
    int yMax,xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW * regWin = newwin(height, xMax/4, 1, xMax*3/4-1);
    refresh();
    box(regWin, 0,0);
    wmove(regWin, 0, 2);
    wrefresh(regWin);
    start_color();
    getch();
    endwin();
    return(0);
}
