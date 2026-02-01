#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Cell_tag
{
    uint8_t state;
    struct Cell_tag *pPrev;
    struct Cell_tag *pNext;
} Cell_t;

typedef struct
{
    Cell_t *pFirst;
    size_t size;
} CellRow_t;

static uint8_t getCellState(Cell_t *cell);
static uint8_t getNextCellState(Cell_t *cell);
static uint8_t getPrevCellState(Cell_t *cell);
static CellRow_t createCellRow(size_t rowSize);
static void deleteCellRow(CellRow_t *row);
static void printRow(CellRow_t *row);

int main(void)
{
    CellRow_t row = createCellRow(8);
    printRow(&row);
    deleteCellRow(&row);
    return 0;
}

static uint8_t getCellState(Cell_t *cell)
{
    return cell->state;
}

static uint8_t getNextCellState(Cell_t *cell)
{
    return (*(cell->pNext)).state;
}

static uint8_t getPrevCellState(Cell_t *cell)
{
    return (*(cell->pPrev)).state;
}

static CellRow_t createCellRow(size_t rowSize)
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

static void deleteCellRow(CellRow_t *row)
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

static void printRow(CellRow_t *row)
{
    Cell_t *currentCell = row->pFirst;
    for (uint8_t i = 0; i < row->size; i++)
    {
        putchar(currentCell->state ? '#' : '.');
        currentCell = currentCell->pNext;
    }
    putchar('\n');
}
