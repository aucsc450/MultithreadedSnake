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
@param cell_row - the x position of the cell
@param cell_col - the y position of the cell
@param type_cell - the type of the cell (EMPTY, FOOD OR SNAKE_NODE)
@return - a cell representing a point in the board
*/
cell* create_cell(int cell_row, int cell_col, cell_type type_cell) {
    cell* a_cell = malloc(sizeof(cell));
    a_cell->row = cell_row;
    a_cell->col = cell_col;
    a_cell->type = type_cell;
    return a_cell;
} // create_cell

/**
Frees a cell from memory.
@param a_cell - the cell to be freed from memory
*/
void free_cell(cell* a_cell) {
    free(a_cell);
} // free_cell