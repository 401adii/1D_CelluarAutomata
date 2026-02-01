#include "Rule.h"
#include <stdlib.h>

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
