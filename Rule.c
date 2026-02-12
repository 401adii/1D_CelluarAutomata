#include "Rule.h"
#include "Cell.h"
#include <stdio.h>
#include <stdlib.h>

void Rule_Print(Rule_t rule)
{
    char chars[MAX_CHARS];
    chars[0] = rule.prevState ? CELL_STATE_1 : CELL_STATE_0;
    chars[1] = rule.state ? CELL_STATE_1 : CELL_STATE_0;
    chars[2] = rule.nextState ? CELL_STATE_1 : CELL_STATE_0;
    chars[3] = rule.outcome ? CELL_STATE_1 : CELL_STATE_0;
    printf("%c%c%c\n %c \n", chars[0], chars[1], chars[2], chars[3]);
}

RuleStatus_t Rule_Check(Rule_t *rule, Cell_t *cell)
{
    if ((*(cell->pNext)).state == rule->nextState && (*(cell->pPrev)).state == rule->prevState && cell->state == rule->state)
    {
        return RULE_OK;
    }
    return RULE_ERROR;
}
