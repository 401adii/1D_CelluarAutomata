#include "CA.h"
#include "Cell.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RULESET_SIZE 8

Rule_t *CA_CreateRuleset()
{
    Rule_t *rules = malloc(RULESET_SIZE * sizeof(Rule_t));
    for (uint8_t i = 0; i < RULESET_SIZE; i++)
    {
        rules[i].prevState = (i >> 2) & 1;
        rules[i].state = (i >> 1) & 1;
        rules[i].nextState = i & 1;
    }
    return rules;
}

void CA_UpdateRulesetOutcome(Rule_t *rules, uint8_t ruleNum)
{
    for (int16_t i = 0; i < RULESET_SIZE; i++)
    {
        rules[i].outcome = ruleNum & 1;
        ruleNum = ruleNum >> 1;
    }
}

void CA_Run(CellRow_t *row1, CellRow_t *row2, Rule_t *rules)
{
    Cell_t *cell1 = row1->pFirst;
    Cell_t *cell2 = row2->pFirst;
    for (uint8_t i = 0; i < row1->size; i++)
    {
        for (uint8_t j = 0; j < RULESET_SIZE; j++)
        {
            if (RULE_OK == Rule_Check(&rules[j], cell1))
            {
                cell2->state = rules[j].outcome;
                break;
            }
        }
        cell1 = cell1->pNext;
        cell2 = cell2->pNext;
    }
}

void CA_DeleteRuleset(Rule_t *rules)
{
    free(rules);
}
