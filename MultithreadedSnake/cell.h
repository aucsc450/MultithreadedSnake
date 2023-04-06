/**
* File: cell.h
*
* Author: Anjola Aina
* Last Modified: Friday, March 31st, 2023
*
* This file contains the cell struct, which represents a point in the game board.
* There contains two methods, one to create a cell and another to free a cell.
* There also exists an enum called cell_type, which determines what "object" is occupying the cell.
* To map the enum to its equivalent string, the following source was used to help achieve this: https://www.linkedin.com/pulse/mapping-enum-string-c-language-sathishkumar-duraisamy/
*/
#ifndef cell_h
#define cell_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// The types that a cell can take
typedef enum cell_type {
    EMPTY,
    APPLE,
    SNAKE
} cell_type; // the types that cells can take

static const char* const cell_type_names[] = {
    [EMPTY] = "EMPTY",
    [APPLE] = "APPLE",
    [SNAKE] = "SNAKE",
};

// The cell struct (used for the queue and board files)
typedef struct cell {
    int row;
    int col;
    cell_type type;
} cell;

// Function definitions
cell* create_cell(int row_p, int col_p, cell_type type_p);
void destroy_cell(cell* cell_p);

#endif