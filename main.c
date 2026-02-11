#include "CA.h"
#include "Cell.h"
#include "CellRow.h"
#include "Rule.h"
#include "UI.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    initscr();
    cbreak();
    noecho();
    UI_Init();
    endwin();
    return 0;
}
