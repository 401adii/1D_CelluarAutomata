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
    for (int i = 0; i < 8; i++)
    {
        Rule_Print(rules[i]);
    }
    CA_DeleteRuleset(rules);
    return 0;
}
