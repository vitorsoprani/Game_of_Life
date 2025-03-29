#ifndef _TABLE_H
#define _TABLE_H

#include "cell.h"

typedef struct Table Table;

Table* Table_Create(int width, int height, char aliveSymbol, char deadSymbol);

void Table_Destroy(Table* t);

void Table_SetCellNextState(Table* t, int i, int j, State s);

void Table_SetCellCurrentState(Table* t, int i, int j, State s);

void Table_Update(Table* t, int goArround);

void Table_Print(Table* t);

int Table_GetNumNeighbours(Table* t, int i, int j, int goArround);

#endif
