#include "CA.h"
#include "Cell.h"
#include "CellRow.h"
#include "Rule.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Rule_t *rules = CA_CreateRuleset();
    CA_UpdateRulesetOutcome(rules, 102);
    for (int i = 0; i < 8; i++)
    {
        Rule_Print(rules[i]);
    }
    CellRow_t row1 = CellRow_Create(100);
    CellRow_t row2 = CellRow_Create(100);
    CellRow_t *firstRow = &row1;
    CellRow_t *secondRow = &row2;
    Cell_ToggleState(CellRow_GetCellAtIndex(&row1, 3));
    uint8_t state = 1;
    while (1)
    {
        CA_Run(firstRow, secondRow, rules);
        CellRow_Print(secondRow);
        if (state)
        {
            firstRow = &row2;
            secondRow = &row1;
        }
        else
        {
            firstRow = &row1;
            secondRow = &row2;
        }
        state = !state;
    }
    CA_DeleteRuleset(rules);
    CellRow_Delete(&row1);
    CellRow_Delete(&row2);
    return 0;
}
