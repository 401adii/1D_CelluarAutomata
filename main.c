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
    CA_UpdateRulesetOutcome(rules, 2);
    for (int i = 0; i < 8; i++)
    {
        Rule_Print(rules[i]);
    }
    CellRow_t row1 = CellRow_Create(8);
    CellRow_t row2 = CellRow_Create(8);
    CellRow_Print(&row1);
    CA_Run(&row1, &row2, rules);
    CellRow_Print(&row2);
    CA_DeleteRuleset(rules);
    CellRow_Delete(&row1);
    CellRow_Delete(&row2);
    return 0;
}
