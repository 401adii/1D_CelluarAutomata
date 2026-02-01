#include "Cell.h"
#include "CellRow.h"
#include "Rule.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 8

int main(void)
{
    CellRow_t row = CellRow_Create(ROW_SIZE);
    Rule_t rule1;
    rule1.state = 0;
    rule1.nextState = 0;
    rule1.prevState = 1;
    rule1.outcome = 1;
    Rule_t rule2;
    rule2.state = 1;
    rule2.nextState = 0;
    rule2.prevState = 0;
    rule2.outcome = 0;
    Cell_t *pCell = CellRow_GetCellAtIndex(&row, 3);
    Cell_ToggleState(pCell);
    CellRow_Print(&row);
    pCell = CellRow_GetCellAtIndex(&row, 4);
    Rule_Check(&rule1, pCell);
    pCell = CellRow_GetCellAtIndex(&row, 3);
    Rule_Check(&rule2, pCell);
    CellRow_Print(&row);
    CellRow_Delete(&row);
    return 0;
}
