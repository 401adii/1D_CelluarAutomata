#include "Cell.h"
#include "CellRow.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 8

int main(void)
{
    CellRow_t row = CellRow_Create(ROW_SIZE);
    Cell_ToggleState(CellRow_GetCellAtIndex(&row, 2));
    CellRow_Print(&row);
    CellRow_Delete(&row);
    return 0;
}
