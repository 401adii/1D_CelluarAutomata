#ifndef CELL_H
#define CELL_H

#include <stdint.h>

typedef struct Cell_tag
{
    uint8_t state;
    struct Cell_tag *pPrev;
    struct Cell_tag *pNext;
} Cell_t;

uint8_t Cell_GetCellState(Cell_t *cell);
uint8_t Cell_GetNextCellState(Cell_t *cell);
uint8_t Cell_GetPrevCellState(Cell_t *cell);

#endif
