/**
* File: cell.cpp
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
*
* This file implements the Cell class defined in its respective file.
*/
#include "cell.h"

/**
Creates a new cell from the specified row, column, and type parameters.
@param row_p - the row of the new cell
@param col_p - the col of the new cell
@param type_p - the type of the new cell
*/
Cell::Cell(int row_p, int col_p, cell_type type_p) {
	row = row_p;
	col = col_p;
	type = type_p;
} // constructor #1

/**
Creates a new cell from the specified row and column, and sets the type of the cell to be empty.
@param row_p - the row of the new cell
@param col_p - the col of the new cell
*/
Cell::Cell(int row_p, int col_p) {
	row = row_p;
	col = col_p;
	type = EMPTY;
} // constructor #2

/**
Creates a new cell and sets the cell to its default values. The default constructor.
*/
Cell::Cell() {
	row = -1;
	col = -1;
	type = EMPTY;
} // default constructor

/**
Destroys a cell by resetting the row, column and the type.
*/
Cell::~Cell() {
	row = -1;
	col = -1;
	type = EMPTY;
} // destructor

/**
Gets the row of the cell.
@return - row value
*/
int Cell::get_row() {
	return row;
} // get_row

/**
Gets the column of the cell.
@return - col value
*/
int Cell::get_col() {
	return col;
} // get_col

/**
Gets the type of the cell.
@return - cell type
*/
cell_type Cell::get_type() {
	return type;
} // get_type

/**
Sets the type of the cell to be the type specified in the parameter of the function.
@param new_type - new type of the cell
*/
void Cell::set_type(cell_type new_type) {
	type = new_type;
} // set_type

/**
Changes the row, column and type of the cell.
@param new_row - the new row value
@param new_col - the new col value
@param new_type - new type of the cell
*/
void Cell::set_cell(int new_row, int new_col, cell_type new_type) {
	row = new_row;
	col = new_col;
	type = new_type;
} // set_cell

/**
Checks whether two cells are the same.
@param cell_p - the cell to be compared
*/
bool Cell::same_cell(Cell* cell_p) {
	if (row == cell_p->get_row() && col == cell_p->get_col() && type == cell_p->get_type()) {
		return true;
	}
	return false;
} // same_cell