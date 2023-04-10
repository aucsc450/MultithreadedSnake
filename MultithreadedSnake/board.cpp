/**
* File: board.cpp
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
*
* This file implements the Board class defined in its respective .h file.
*/
#include "board.h"

/**
Creates a new board of cells that are all empty.
*/
Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			cells[i][j] = new Cell(i, j);
		}
	}
} // constructor

/**
Destroys the board.
*/
Board::~Board() {
	delete[] *cells;
} // destructor

/**
Gets a specific cell in the board.
@param row - row index of cell to obtain
@param col - col index of cell to obtain
@return - the cell in the board indicated by the row and column indices
*/
Cell* Board::get_specific_cell(int row, int col) {
	return cells[row][col];
} // get_specific_cell

/**
Sets the type for a specific cell.
@param row - row index
@param col - col index
@param type_p - new type of the cell at the specificed row and column
*/
void Board::set_type_for_specific_cell(int row, int col, cell_type type_p) {
	cells[row][col]->set_type(type_p);
} // set_type_for_specific_cell

/**
Generates an apple at a random location.
*/
void Board::generate_apple() {
	int rand_row = 0;
	int rand_col = 0;
	while (true) {
		rand_row = rand() % BOARD_SIZE;
		rand_col = rand() % BOARD_SIZE;
		if (cells[rand_row][rand_col]->get_type() != SNAKE) {
			break; // found an empty cell
		}
	} // while
	cells[rand_row][rand_col]->set_type(APPLE);
} // generate_food

/**
Resets the board by making every cell empty.
*/
void Board::reset() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			set_type_for_specific_cell(i, j, EMPTY);
		}
	}
} // reset