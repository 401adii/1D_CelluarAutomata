#include "UI.h"
#include "CA.h"
#include "Rule.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

WINDOW *rulesWindow;
WINDOW *inputWindow;
WINDOW *CAWindow;
uint16_t rows, cols;
uint16_t currentRule = 0;
Rule_t *rules = NULL;

#define BUFFER_SIZE 50
#define MAX_ROWS rows
#define MAX_COLS cols
#define RULES_ROWS (rows / 2)
#define RULES_COLS (cols * 3 / 4)
#define RULES_ROWS_START (rows / 8)
#define RULES_COLS_START (cols / 8)
#define INPUT_ROWS 2
#define INPUT_COLS (cols * 3 / 4)
#define INPUT_ROWS_START (rows * 3 / 5)
#define INPUT_COLS_START (cols / 8)

static void refreshRuleset();
static void printRuleText();
static void printRuleSlot(uint16_t row, uint16_t col);
static uint16_t getTextCenterCol(WINDOW *window, char *buffer);

void UI_Init()
{
    initscr();
    cbreak();
    noecho();

    refresh();
    getmaxyx(stdscr, rows, cols);

    rulesWindow = newwin(RULES_ROWS, RULES_COLS, RULES_ROWS_START, RULES_COLS_START);
    box(rulesWindow, 0, 0);
    refreshRuleset();
    wrefresh(rulesWindow);

    inputWindow = newwin(INPUT_ROWS, INPUT_COLS, INPUT_ROWS_START, INPUT_COLS_START);
    box(inputWindow, 0, 0);
    wrefresh(inputWindow);

    getch();
}

void UI_Loop()
{
    refreshRuleset();
}

void UI_Deinit()
{
    endwin();
}

static void refreshRuleset()
{
    if (rules != NULL)
    {
        CA_DeleteRuleset(rules);
    }
    printRuleText();
    printRuleSlot(10, 10);
    rules = CA_CreateRuleset();
    CA_UpdateRulesetOutcome(rules, currentRule);

    for (uint8_t i = 0; i < RULESET_SIZE; i++)
    {
    }
}

static void printRuleText()
{
    char buffer[BUFFER_SIZE] = {0};
    sprintf(buffer, "Rule %03d/255", currentRule);
    wmove(rulesWindow, getmaxy(rulesWindow) - 1, getTextCenterCol(rulesWindow, buffer));
    wprintw(rulesWindow, "Rule %03d/255", currentRule);
}

static void printRuleSlot(uint16_t row, uint16_t col)
{
}

static uint16_t getTextCenterCol(WINDOW *window, char *buffer)
{
    uint16_t c = getmaxx(window);
    uint16_t len = strlen(buffer);

    return (uint16_t)((c / 2) - (len / 2));
}
