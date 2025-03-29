#ifndef _CELL_H
#define _CELL_H

/**
 * Enum that indicates the state of the cell (dead or alive)
 */
typedef enum{
    ALIVE,
    DEAD
}State;

/**
 * Struct that represents our cell;
 */
typedef struct Cell Cell;

Cell* Cell_Create(char aliveSymbol, char deadSymbol, State currentstate);

void Cell_Destroy(Cell* c);

int Cell_IsAlive(Cell* c);

void Cell_Print(Cell* c);

void Cell_SetNextState(Cell* c, State s);

void Cell_SetCurrentState(Cell* c, State s);

void Cell_Update(Cell* c);

#endif
