#include "UI.h"
#include "CA.h"
#include "Rule.h"
#include <ctype.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

WINDOW *rulesWindow;
WINDOW *inputWindow;
WINDOW *CAWindow;
uint16_t rows, cols;
uint16_t currentRule = 90;
Rule_t *rules = NULL;

char inputBuffer[4] = "000";
uint8_t inputEnabled = 0;

#define BUFFER_SIZE 50
#define INPUT_BUFFER_SIZE 4
#define MAX_ROWS rows
#define MAX_COLS cols
#define RULES_ROWS (rows / 2)
#define RULES_COLS (cols * 3 / 4)
#define RULES_ROWS_START (rows / 8)
#define RULES_COLS_START (cols / 8)
#define INPUT_ROWS 8
#define INPUT_COLS (cols * 3 / 4)
#define INPUT_ROWS_START (rows * 3 / 5)
#define INPUT_COLS_START (cols / 8)
#define RULESLOT_WIDTH 7
#define RULESLOT_HEIGHT 5
#define RULESLOT_ROW_MARGIN (RULESLOT_HEIGHT + 5)
#define RULESLOT_COL_MARGIN (RULESLOT_WIDTH + 5)
#define RULESLOT_ROW_START (RULES_ROWS / 4)
#define RULESLOT_COL_START (RULES_COLS / 2 - RULESLOT_ROW_MARGIN * 2)
#define INPUT_LEFT 'h'
#define INPUT_RIGHT 'l'
#define INPUT_CONFIRM '\n'
#define INPUT_CANCEL 'c'
#define INPUT_QUIT 'q'

typedef struct
{
    uint16_t startRow;
    uint16_t startCol;
} RuleSlot_t;

RuleSlot_t ruleSlots[RULESET_SIZE];

static void refreshRuleset();
static void printRuleText();
static void createAndPrintRuleSlot(uint16_t row, uint16_t col, RuleSlot_t *ruleSlot);
static void printRule(RuleSlot_t *ruleSlot, Rule_t *rule);
static uint16_t getTextCenterCol(WINDOW *window, char *buffer);
static void handleInput(int ch);
static void runCA();

void UI_Init()
{
    initscr();
    cbreak();
    noecho();

    refresh();
    getmaxyx(stdscr, rows, cols);
    curs_set(0);

    rulesWindow = newwin(RULES_ROWS, RULES_COLS, RULES_ROWS_START, RULES_COLS_START);
    box(rulesWindow, 0, 0);
    for (int i = 0; i < RULESET_SIZE; i++)
    {
        if (i < RULESET_SIZE / 2)
        {
            createAndPrintRuleSlot(RULESLOT_ROW_START, RULESLOT_COL_START + (RULESLOT_COL_MARGIN * i), &ruleSlots[i]);
        }
        else
        {
            createAndPrintRuleSlot(RULESLOT_ROW_START + RULESLOT_ROW_MARGIN, RULESLOT_COL_START + (RULESLOT_COL_MARGIN * (i - (RULESET_SIZE / 2))), &ruleSlots[i]);
        }
    }
    refreshRuleset();
    wrefresh(rulesWindow);

    inputWindow = newwin(INPUT_ROWS, INPUT_COLS, INPUT_ROWS_START, INPUT_COLS_START);
    box(inputWindow, 0, 0);
    wmove(inputWindow, 1, 1);
    wprintw(inputWindow, "<--%c", INPUT_LEFT);
    wmove(inputWindow, 1, INPUT_COLS - 5);
    wprintw(inputWindow, "%c-->", INPUT_RIGHT);
    wmove(inputWindow, 2, 1);
    wprintw(inputWindow, "Controls:");
    wmove(inputWindow, 3, 1);
    wprintw(inputWindow, "%c - Simulation speed down", INPUT_LEFT);
    wmove(inputWindow, 4, 1);
    wprintw(inputWindow, "%c - Simulation speed up", INPUT_RIGHT);
    wmove(inputWindow, 5, 1);
    wprintw(inputWindow, "%c - Cancel rule input", INPUT_CANCEL);
    wmove(inputWindow, 6, 1);
    wprintw(inputWindow, "%c - Quit program/simulation", INPUT_QUIT);
    wrefresh(inputWindow);
}

void UI_Loop()
{
    int ch;
    while (1)
    {
        if ((ch = getch()) != ERR)
        {
            if (ch == INPUT_QUIT)
            {
                break;
            }
            handleInput(ch);
        }
    }
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
    rules = CA_CreateRuleset();
    CA_UpdateRulesetOutcome(rules, currentRule);
    for (uint8_t i = 0; i < RULESET_SIZE; i++)
    {
        printRule(&ruleSlots[i], &rules[i]);
    }
}

static void printRuleText()
{
    char buffer[BUFFER_SIZE] = {0};
    sprintf(buffer, "Rule %03d/255", currentRule);
    wmove(rulesWindow, getmaxy(rulesWindow) - 1, getTextCenterCol(rulesWindow, buffer));
    wprintw(rulesWindow, "Rule %03d/255", currentRule);
}

static void createAndPrintRuleSlot(uint16_t row, uint16_t col, RuleSlot_t *ruleSlot)
{
    ruleSlot->startRow = row;
    ruleSlot->startCol = col;
    mvwaddch(rulesWindow, row, col, ACS_ULCORNER);
    mvwhline(rulesWindow, row, col + 1, ACS_HLINE, 5);
    mvwaddch(rulesWindow, row, col + 6, ACS_URCORNER);
    mvwaddch(rulesWindow, row + 1, col, ACS_VLINE);
    mvwaddch(rulesWindow, row + 2, col, ACS_LLCORNER);
    mvwaddch(rulesWindow, row + 2, col + 1, ACS_HLINE);
    mvwaddch(rulesWindow, row + 2, col + 2, ACS_URCORNER);
    mvwaddch(rulesWindow, row + 3, col + 2, ACS_VLINE);
    mvwaddch(rulesWindow, row + 4, col + 2, ACS_LLCORNER);
    mvwaddch(rulesWindow, row + 4, col + 3, ACS_HLINE);
    mvwaddch(rulesWindow, row + 4, col + 4, ACS_LRCORNER);
    mvwaddch(rulesWindow, row + 3, col + 4, ACS_VLINE);
    mvwaddch(rulesWindow, row + 2, col + 4, ACS_ULCORNER);
    mvwaddch(rulesWindow, row + 2, col + 5, ACS_HLINE);
    mvwaddch(rulesWindow, row + 2, col + 6, ACS_LRCORNER);
    mvwaddch(rulesWindow, row + 1, col + 6, ACS_VLINE);
}

static void printRule(RuleSlot_t *ruleSlot, Rule_t *rule)
{
    char temp[4];
    temp[0] = rule->prevState ? CELL_STATE_1 : CELL_STATE_0;
    temp[1] = rule->state ? CELL_STATE_1 : CELL_STATE_0;
    temp[2] = rule->nextState ? CELL_STATE_1 : CELL_STATE_0;
    temp[3] = rule->outcome ? CELL_STATE_1 : CELL_STATE_0;
    mvwaddch(rulesWindow, ruleSlot->startRow + 1, ruleSlot->startCol + 4, temp[0]);
    mvwaddch(rulesWindow, ruleSlot->startRow + 1, ruleSlot->startCol + 3, temp[1]);
    mvwaddch(rulesWindow, ruleSlot->startRow + 1, ruleSlot->startCol + 2, temp[2]);
    mvwaddch(rulesWindow, ruleSlot->startRow + 3, ruleSlot->startCol + 3, temp[3]);
}

static uint16_t getTextCenterCol(WINDOW *window, char *buffer)
{
    uint16_t c = getmaxx(window);
    uint16_t len = strlen(buffer);

    return (uint16_t)((c / 2) - (len / 2));
}

static void handleInput(int ch)
{
    if (isdigit(ch))
    {
        inputEnabled = 1;
        for (int i = 0; i < INPUT_BUFFER_SIZE - 2; i++)
        {
            inputBuffer[i] = inputBuffer[i + 1];
        }
        inputBuffer[INPUT_BUFFER_SIZE - 2] = ch;
        inputBuffer[INPUT_BUFFER_SIZE - 1] = '\0';
        wmove(inputWindow, 1, INPUT_COLS / 2 - 1);
        wattron(inputWindow, A_REVERSE);
        wprintw(inputWindow, "%s", inputBuffer);
        wattroff(inputWindow, A_REVERSE);
    }
    switch (ch)
    {
    case INPUT_LEFT:
        if (currentRule == 0)
            break;
        currentRule--;
        break;
    case INPUT_RIGHT:
        if (currentRule == 255)
            break;
        currentRule++;
        break;
    case INPUT_CONFIRM:
        if (inputEnabled)
        {
            currentRule = atoi(inputBuffer);
            if (currentRule > 255)
            {
                currentRule = 255;
            }
            inputEnabled = 0;
            wmove(inputWindow, 1, INPUT_COLS / 2 - 1);
            wprintw(inputWindow, "   ");
            for (int i = 0; i < INPUT_BUFFER_SIZE - 1; i++)
            {
                inputBuffer[i] = '0';
            }
        }
        else
        {
            runCA();
            UI_Init();
        }
        break;
    case INPUT_CANCEL:
        inputEnabled = 0;
        wmove(inputWindow, 1, INPUT_COLS / 2 - 1);
        wprintw(inputWindow, "   ");
        for (int i = 0; i < INPUT_BUFFER_SIZE - 1; i++)
        {
            inputBuffer[i] = '0';
        }
        break;
    default:
        break;
    }
    refreshRuleset();
    wrefresh(rulesWindow);
    wrefresh(inputWindow);
}

static void runCA()
{
    wclear(inputWindow);
    wclear(rulesWindow);
    wrefresh(inputWindow);
    wrefresh(rulesWindow);
    delwin(inputWindow);
    delwin(rulesWindow);
    scrollok(stdscr, TRUE);
    timeout(250);
    CellRow_t crow1 = CellRow_Create(MAX_COLS);
    CellRow_t crow2 = CellRow_Create(MAX_COLS);
    char buffer[MAX_COLS + 1];
    CellRow_t *firstRow = &crow1;
    CellRow_t *secondRow = &crow2;
    Cell_ToggleState(CellRow_GetCellAtIndex(&crow1, MAX_COLS / 2));
    CellRow_GetString(firstRow, buffer);
    printw("%s", buffer);
    int quit = 0;
    int delay = 250;
    timeout(delay);
    int ch;
    while (1)
    {
        if ((ch = getch()) != ERR)
        {
            switch (ch)
            {
            case INPUT_QUIT:
                quit = 1;
                break;
            case INPUT_RIGHT:
                delay -= 50;
                if (delay < 100)
                {
                    delay = 100;
                }
                timeout(delay);
                break;
            case INPUT_LEFT:
                delay += 50;
                if (delay > 1000)
                {
                    delay = 1000;
                }
                timeout(delay);
                break;
            default:
                break;
            }
        }
        if (quit)
        {
            wclear(stdscr);
            refresh();
            timeout(0);
            break;
        }
        CA_Run(firstRow, secondRow, rules);
        CellRow_GetString(secondRow, buffer);
        printw("%s", buffer);
        CellRow_t *temp = firstRow;
        firstRow = secondRow;
        secondRow = temp;
        refresh();
    }
}
