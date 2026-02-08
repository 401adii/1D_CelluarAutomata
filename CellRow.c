#include "CellRow.h"
#include <stdio.h>
#include <stdlib.h>

CellRow_t CellRow_Create(size_t rowSize)
{
    CellRow_t newRow;
    newRow.size = rowSize;
    newRow.pFirst = NULL;

    if (rowSize == 0)
    {
        return newRow;
    }

    Cell_t *prev = NULL;
    Cell_t *first = NULL;

    for (uint8_t i = 0; i < rowSize; i++)
    {
        Cell_t *cell = malloc(sizeof(Cell_t));
        cell->state = 0;
        if (prev != NULL)
        {
            cell->pPrev = prev;
            prev->pNext = cell;
        }
        else
        {
            first = cell;
            cell->pPrev = NULL;
        }
        prev = cell;
    }

    prev->pNext = first;
    first->pPrev = prev;

    newRow.pFirst = first;
    return newRow;
}

void CellRow_Delete(CellRow_t *row)
{
    Cell_t *cell = row->pFirst;
    for (uint8_t i = 0; i < row->size; i++)
    {
        Cell_t *next_cell = cell->pNext;
        cell->state = 0;
        cell->pNext = NULL;
        cell->pPrev = NULL;
        free(cell);
        cell = next_cell;
    }
    row->pFirst = NULL;
    row->size = 0;
}

void CellRow_Print(CellRow_t *row)
{
    Cell_t *currentCell = row->pFirst;
    for (uint8_t i = 0; i < row->size; i++)
    {
        putchar(currentCell->state ? CELL_STATE_1 : CELL_STATE_0);
        currentCell = currentCell->pNext;
    }
    putchar('\n');
}

Cell_t *CellRow_GetCellAtIndex(CellRow_t *row, uint8_t index)
{
    if (row == NULL || row->pFirst == NULL)
    {
        return NULL;
    }

    if (index >= row->size)
    {
        return NULL;
    }

    Cell_t *pCell = row->pFirst;
    for (int i = 0; i < index; i++)
    {
        pCell = pCell->pNext;
    }

    return pCell;
}
