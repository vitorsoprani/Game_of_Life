#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "table.h"

struct Table {
    Cell*** cells;
    int width;
    int height;
};

Table* Table_Create(int width, int height, char aliveSymbol, char deadSymbol) {
    Table* t = (Table*)malloc(sizeof(Table));
    assert(t != NULL);

    t->width = width;
    t->height = height;

    t->cells = (Cell***)malloc(sizeof(Cell**) * height);
    assert(t->cells != NULL);

    for (int i = 0; i < height; i++) {
        t->cells[i] = (Cell**)malloc(sizeof(Cell*) * width);
        assert(t->cells[i] != NULL);

        for (int j = 0; j < width; j++)
            t->cells[i][j] = Cell_Create(aliveSymbol, deadSymbol, DEAD);
    }

    return t;
}
    

void Table_Destroy(Table* t) {
    if (t != NULL) {
        for (int i = 0; i < t->height; i++) {
            for (int j = 0; j < t->width; j++)
                Cell_Destroy(t->cells[i][j]);

            free(t->cells[i]);
        }

        free(t->cells);
        free(t);
    }
}

void Table_SetCellNextState(Table* t, int i, int j, State s) {
    assert(t != NULL);
    assert(i < t->height && i >= 0);
    assert(j < t->width && j >= 0);

    Cell_SetNextState(t->cells[i][j], s);
}

void Table_SetCellCurrentState(Table* t, int i, int j, State s) {
    assert(t != NULL);
    assert(i < t->height && i >= 0);
    assert(j < t->width && j >= 0);

    Cell_SetCurrentState(t->cells[i][j], s);
}

void Table_Update(Table* t, int goArround) {
    assert(t != NULL);

    for (int i = 0; i < t->height; i++) {
        for (int j = 0; j < t->width; j++) {
            int nNeighbours = Table_GetNumNeighbours(t, i, j, goArround);
            
            Cell_SetNextState(t->cells[i][j], ALIVE);

            if (nNeighbours < 2 || nNeighbours > 3)
                Cell_SetNextState(t->cells[i][j], DEAD);
            else if (nNeighbours != 3 && !Cell_IsAlive(t->cells[i][j]))
                Cell_SetNextState(t->cells[i][j], DEAD);
        }
    }

    for (int i = 0; i < t->height; i++) {
        for (int j = 0; j < t->width; j++) {
            Cell_Update(t->cells[i][j]);
        }
    }
}

void Table_Print(Table* t) {
    assert(t != NULL);

    printf("+");
    for (int i = 0; i < t->width; i++)
        printf("--");
    printf("+\n");

    for(int i = 0; i < t->height; i++) {
        printf("|");
        for (int j = 0; j < t->width; j++) {
            Cell_Print(t->cells[i][j]);
        }
        printf("|\n");
    }
    
    printf("+");
    for (int i = 0; i < t->width; i++)
        printf("--");
    printf("+\n");
}

int Table_GetNumNeighbours(Table* t, int i, int j, int goArround) {
    assert(t != NULL);
    assert(i < t->height && i >= 0);
    assert(j < t->width && j >= 0);
    
    int n = 0;
   
    /*
    [i-1][j-1] | [i-1][j-0] | [i-1][j+1]
    [i-0][j-1] | [i-0][j-0] | [i-0][j+1]
    [i+1][j-1] | [i+1][j-0] | [i+1][j+1]
    */
    
    if (goArround) {
        for (int a = -1; a <= 1; a++) {
            for (int b = -1; b <= 1; b++) {
                if (a == 0 && b == 0)
                    continue;
                
                int ni = (i + a) % t->height;
                int nj = (j + b) % t->width;
                
                if (ni < 0) ni = t->height + ni;
                if (nj < 0) nj = t->width + nj;

                if (Cell_IsAlive(t->cells[ni][nj]))
                    n++;
            }
        }
    } else {
        for (int a = -1; a <= 1; a++) {
            for (int b = -1; b <= 1; b++) {
                if (a == 0 && b == 0)
                    continue;
                
                int ni = i + a;
                int nj = j + b;

                if (ni < 0 || ni >= t->height)
                    continue;
                if (nj < 0 || nj >= t->width)
                    continue;

                if (Cell_IsAlive(t->cells[ni][nj]))
                    n++;
            }
        }
    }
    return n;
}
