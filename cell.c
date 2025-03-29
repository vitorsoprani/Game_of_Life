#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cell.h"

struct Cell {
    char aliveSymbol;
    char deadSymbol;
    State currentState;
    State nextState;
};

Cell* Cell_Create(char aliveSymbol, char deadSymbol, State currentState) {
    Cell* c = (Cell*)malloc(sizeof(Cell));
    assert(c != NULL);

    c->aliveSymbol = aliveSymbol;
    c->deadSymbol = deadSymbol;
    c->currentState = currentState;
    c->nextState = DEAD;

    return c;
}

void Cell_Destroy(Cell* c) {
    free(c);
}

int Cell_IsAlive(Cell* c) {
    assert(c != NULL);

    return c->currentState == ALIVE;
}

void Cell_Print(Cell* c) {
    assert(c != NULL);
    
    char ch;

    if(Cell_IsAlive(c)) {
        ch = c->aliveSymbol;
    } else {
        ch = c->deadSymbol;
    }
    printf("%c%c", ch, ch);
}

void Cell_SetNextState(Cell* c, State s) {
    assert(c != NULL);

    c->nextState = s;
}

void Cell_SetCurrentState(Cell* c, State s) {
    assert(c != NULL);

    c->currentState = s;
}

void Cell_Update(Cell* c) {
    assert(c != NULL);

    c->currentState = c->nextState;
}
