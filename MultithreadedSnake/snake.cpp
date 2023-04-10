/**
* File: snake.cpp
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
*
* This file implements the snake class defined in its respective .h file.
*/
#include "snake.h"

/**
Creates a new snake that is initially empty.
*/
Snake::Snake() {
	snake = new Queue();
} // constructor

/**
Destroys a snake. It relies on the queue destructor to destroy the snake.
*/
Snake::~Snake() {
} // destructor

/**
Gets the snake (represented as a queue).
@return - the queue representing the snake
*/
Queue* Snake::get_snake() {
	return snake;
} // get_snake

/**
Grows the snake by enqueuing a new node.
@param cell_p - the data of the new node to be enqueued to the snake.
*/
void Snake::grow(Cell* cell_p) {
	snake->enqueue(cell_p);
} // grow

/**
Moves all nodes in the snake.
@param next_cell - the cell containing the new row and column values of the snake's head
*/
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

/**
Checks whether the snake has collided with itself.
@param next_cell - the cell containing the new row and column values of the snake's head
@return - true if the snake has collided with its body, false otherwise
*/
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

/**
Resets the snake by dequeueing every current node in the snake.
*/
void Snake::reset() {
	Node* temp;
	while (!snake->is_empty()) {
		temp = snake->dequeue();
	} // while
} // reset