/**
* File: snake.h
*
* Author: Anjola Aina
* Last Modified: Tuesday, April 4th, 2023
* The following website was used as a reference to create the queue abstract data type: https://www.codesdope.com/blog/article/making-a-queue-using-linked-list-in-c/
*/
#ifndef snake_h
#define snake_h
#include "cell.h"
#include "direction.h"

#define EMPTY_SNAKE 0

// The node struct containing data
typedef struct snake_node {
    cell* cell;
    struct snake_node* next;
} snake_node;

// The queue struct (the snake will be a queue)
typedef struct snake {
    snake_node* front;
    snake_node* rear;
    int size;
} snake;

// Function definitions
snake* create_snake();
bool is_empty(snake* snake_p);
bool enqueue(snake* snake_p, cell* cell_p);
snake_node* dequeue(snake* snake_p);
void destroy_snake(snake* snake_p);

#endif