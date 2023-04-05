/**
* File: cell.c
*
* Author: Anjola Aina
* Last Modified: Thursday, March 30th, 2023
*
* This file implements the functions defined in the cell.h file.
*/
#include "cell.h"

/**
Creates a cell from the specified row, column and type of cell.
@param row_p - the x position of the cell
@param col_p - the y position of the cell
@param type_p - the type of the cell (EMPTY, FOOD OR SNAKE_NODE)
@return - a cell representing a point in the board or NULL if not enough memory exists to create a cell
*/
cell* create_cell(int row_p, int col_p, cell_type type_p) {
    cell* a_cell = malloc(sizeof(cell));
    if (a_cell != NULL) {
        a_cell->row = row_p;
        a_cell->col = col_p;
        a_cell->type = type_p;
        return a_cell;
    }
    return NULL;
} // create_cell

/**
Frees a cell from memory.
@param cell_p - the cell to be freed from memory
*/
void destroy_cell(cell* cell_p) {
    free(cell_p);
} // free_cell