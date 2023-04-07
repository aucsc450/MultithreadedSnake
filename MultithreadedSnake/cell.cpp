/**
* File: cell.cpp
*
* Author: Anjola Aina
* Last Modified: Thursday, April 6th, 2023
*
* This file implements the functions defined in the cell.h file.
*/
#include "cell.h"

Cell::Cell(int row_p, int col_p, cell_type type_p) {
	row = row_p;
	col = col_p;
	type = type_p;
} // constructor #1

Cell::Cell(int row_p, int col_p) {
	row = row_p;
	col = col_p;
	type = EMPTY;
} // constructor #2

Cell::Cell() {
	row = -1;
	col = -1;
	type = EMPTY;
} // default constructor

Cell::~Cell() {
	row = -1;
	col = -1;
	type = EMPTY;
} // destructor

int Cell::get_row() {
	return row;
} // get_row

int Cell::get_col() {
	return col;
} // get_col

cell_type Cell::get_type() {
	return type;
} // get_type

void Cell::set_type(cell_type new_type) {
	type = new_type;
} // set_type

void Cell::set_cell(int new_row, int new_col, cell_type new_type) {
	row = new_row;
	col = new_col;
	type = new_type;
} // set_cell

bool Cell::same_cell(Cell* cell_p) {
	if (row == cell_p->get_row() && col == cell_p->get_col() && type == cell_p->get_type()) {
		return true;
	}
	return false;
} // same_cell