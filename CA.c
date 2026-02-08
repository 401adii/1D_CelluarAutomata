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
        uint8_t k = i;
        rules[i].prevState = k & 1;
        k = k >> 1;
        rules[i].state = k & 1;
        k = k >> 1;
        rules[i].nextState = k & 1;
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
    for (uint8_t i = 0; i < row1->size; i++)
    {
        Cell_t *cell1 = CellRow_GetCellAtIndex(row1, i);
        Cell_t *cell2 = CellRow_GetCellAtIndex(row2, i);
        for (uint8_t j = 0; j < RULESET_SIZE; j++)
        {
            if (RULE_OK == Rule_Check(&rules[j], cell1))
            {
                Cell_WriteState(cell2, 1);
            }
            else
            {
                Cell_WriteState(cell2, 0);
            }
        }
    }
}

void CA_DeleteRuleset(Rule_t *rules)
{
    free(rules);
}
