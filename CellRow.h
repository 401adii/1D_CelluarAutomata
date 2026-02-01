#ifndef CELL_ROW_H
#define CELL_ROW_H

#include "Cell.h"
#include <stddef.h>

typedef struct
{
    Cell_t *pFirst;
    size_t size;
} CellRow_t;

CellRow_t CellRow_Create(size_t rowSize);
void CellRow_Delete(CellRow_t *row);
void CellRow_Print(CellRow_t *row);

#endif
