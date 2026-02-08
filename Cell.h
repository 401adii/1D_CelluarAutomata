#ifndef CELL_H
#define CELL_H

#include <stdint.h>

#define CELL_STATE_0 '.'
#define CELL_STATE_1 '#'

typedef struct Cell_tag
{
    uint8_t state;
    struct Cell_tag *pPrev;
    struct Cell_tag *pNext;
} Cell_t;

typedef enum
{
    CELL_OK = 0,
    CELL_ERROR
} CellStatus_t;

uint8_t Cell_GetState(Cell_t *cell);
uint8_t Cell_GetNextCellState(Cell_t *cell);
uint8_t Cell_GetPrevCellState(Cell_t *cell);
CellStatus_t Cell_ToggleState(Cell_t *cell);
CellStatus_t Cell_WriteState(Cell_t *cell, uint8_t state);

#endif
