#include "UI.h"
#include <ncurses.h>
#include <stdint.h>

WINDOW *rulesWindow;
WINDOW *inputWindow;
uint16_t rows, cols;

static uint16_t getCenterPosX(uint16_t offset);

void UI_Init()
{
    refresh();
    getmaxyx(stdscr, rows, cols);

    box(rulesWindow, 0, 0);
    wrefresh(rulesWindow);

    getch();
}

void UI_Loop()
{
}
