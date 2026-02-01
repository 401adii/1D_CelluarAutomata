#include "Cell.h"

uint8_t Cell_GetCellState(Cell_t *cell)
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
