#include "Cell.h"
#include <stdlib.h>

uint8_t Cell_GetState(Cell_t *cell)
{
    return cell->state;
}

uint8_t Cell_GetNextCellState(Cell_t *cell)
{
    return (*(cell->pNext)).state;
}

uint8_t Cell_GetPrevCellState(Cell_t *cell)
{
    return (*(cell->pPrev)).state;
}

CellStatus_t Cell_ToggleState(Cell_t *cell)
{
    if (cell == NULL)
    {
        return CELL_ERROR;
    }
    cell->state = !(cell->state);
    return CELL_OK;
}
