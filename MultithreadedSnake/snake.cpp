/**
* File: snake.cpp
*
* Author: Anjola Aina
* Last Modified: Thursday, April 6th, 2023
*
* This file contains the board struct, which represents the game board of snake.
* It is BOARD_SIZE * BOARD_SIZE large (a square), and consists of cells defined in the cell.h file and implemented in its respective .c file.
* There are functions to create and destroy the board, as well as a function to change a cell in the board.
* Initially, the board is empty.
*/
#include "snake.h"

Snake::Snake() {
	snake = new Queue();
} // constructor

Snake::~Snake() {
} // destructor

Queue* Snake::get_snake() {
	return snake;
} // get_snake

void Snake::grow(Cell* cell_p) {
	snake->enqueue(cell_p);
} // grow

void Snake::move(Cell* next_cell) {
	int num_passes = 0;
	while (true) {
		Cell* front_cell = snake->dequeue()->get_data();
		if (num_passes < 1) {
			snake->enqueue(next_cell);
		}
		num_passes++;
		if (snake->get_size() <= 1 || num_passes >= snake->get_size()) {
			front_cell->set_type(EMPTY);
			break;
		}
		snake->enqueue(front_cell);
	} // while
} // move

bool Snake::collided(Cell* next_cell) {
	Node* temp = snake->get_front();
	Cell* cell_t;
	while (temp != NULL) {
		cell_t = temp->get_data();
		if (cell_t->same_cell(next_cell)) {
			return true;
		}
		temp = temp->get_next();
	} // while
	return false;
} // collided 

void Snake::reset() {
	Node* temp;
	while (!snake->is_empty()) {
		temp = snake->dequeue();
	} // while
} // reset