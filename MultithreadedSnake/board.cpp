/**
* File: board.cpp
*
* Author: Anjola Aina
* Last Modified: Thursday, April 6th, 2023
*
* This file contains the board struct, which represents the game board of snake.
* It is BOARD_SIZE * BOARD_SIZE large (a square), and consists of cells defined in the cell.h file and implemented in its respective .c file.
* There are functions to create and destroy the board, as well as a function to change a cell in the board.
* Initially, the board is empty.
*/
#include "board.h"

Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			cells[i][j] = new Cell(i, j);
		}
	}
} // constructor

Board::~Board() {
	delete[] *cells;
} // destructor

Cell* Board::get_specific_cell(int row, int col) {
	return cells[row][col];
} // get_specific_cell

void Board::set_type_for_specific_cell(int row, int col, cell_type type_p) {
	cells[row][col]->set_type(type_p);
} // set_type_for_specific_cell
