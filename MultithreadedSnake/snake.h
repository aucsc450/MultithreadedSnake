/**
* File: snake.h
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
* 
* This file defines the snake class, which is implemented in its respective .cpp file.
* The following website was used as a reference to create the queue abstract data type: https://www.codesdope.com/blog/article/making-a-queue-using-linked-list-in-c/
*/
#ifndef snake_h
#define snake_h
#include "queue.h"
#include "direction.h"

#define EMPTY_SNAKE 0

class Snake {
private:
	Queue* snake;
public:
	Snake();
	~Snake();
	Queue* get_snake();
	void grow(Cell* cell_p);
	void move(Cell* next_cell);
	bool collided(Cell* next_cell);
	void reset();
};

#endif