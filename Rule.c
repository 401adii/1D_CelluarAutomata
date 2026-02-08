#include "Rule.h"
#include <stdio.h>
#include <stdlib.h>

void Rule_Print(Rule_t rule)
{
    printf("%d%d%d\n", rule.prevState, rule.state, rule.nextState);
}

RuleStatus_t Rule_Check(Rule_t *rule, Cell_t *cell)
{
    if (cell == NULL)
    {
        return RULE_ERROR;
    }
    if ((*(cell->pNext)).state == rule->nextState && (*(cell->pPrev)).state == rule->prevState && cell->state == rule->state)
    {
        cell->state = rule->outcome;
    }
    return RULE_OK;
}
