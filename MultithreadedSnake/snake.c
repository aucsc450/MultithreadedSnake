/**
* File: snake.c
*
* Author: Anjola Aina
* Last Modified: Tuesday, April 4th, 2023
*
* This file implements the functions defined in the snake.h file.
*/
#include "snake.h"

/**
Creates a new snake by setting the front and rear pointers initially to null, and the size of the snake initially to 0.
@return - a new snake with no elements in it
*/
snake* create_snake() {
    snake* snake_t = malloc(sizeof(snake));
    if (snake_t != NULL) {
        snake_t->front = NULL;
        snake_t->rear = NULL;
        snake_t->size = 0;
        return snake_t;
    }
    return NULL; // not enough space in memory to allocate space for the snake struct
} // create_snake

/**
Checks whether the snake is empty or not.
@param snake_p - the snake
@return - true if the snake is empty, false otherwise
*/
bool is_empty(snake* snake_p) {
    if (snake_p->size <= EMPTY_SNAKE) {
        return true; // the snake has no elements in it
    }
    return false; // the snake is NOT empty
} // is_empty

/**
Adds a snake node to the rear of the snake.
@param snake_p - the snake to perform the operation on
@param cell_p - the cell of the new snake node
@return - true if a snake node was successfully added to the snake, false otherwise
*/
bool enqueue(snake* snake_p, cell* cell_p) {
    snake_node* new_node = malloc(sizeof(snake_node));
    if (new_node != NULL) {
        new_node->cell->row = cell_p->row;
        new_node->cell->col = cell_p->col;
        new_node->cell->type = cell_p->type;
        destroy_cell(cell_p); // we don't need the new cell anymore
        if (is_empty(snake_p)) {
            snake_p->front = new_node;
            snake_p->rear = new_node;
        }
        else {
            snake_p->rear->next = new_node;
            snake_p->rear = new_node;
        }
        snake_p->size++; // increase the size of the snake
        return true; // successfully added a snake_node to the snake
    } // if
    return false; // not enough space in memory to create a new snake node to add to the snake
} // enqueue

/**
Removes and returns a snake node from the front of the snake.
@param snake_p - the snake to perform the operation on
@return - the snake node that was at the front of the snake
*/
snake_node* dequeue(snake* snake_p) {
    snake_node* temp = malloc(sizeof(snake_node));
    temp = snake_p->front;
    snake_p->front = snake_p->front->next;
    snake_p->size--; // decrease the size of the queue
    return temp;
} // dequeue

/**
Frees a snake from memory.
@param a_queue - the snake to be removed from memory
*/
void destroy_snake(snake* snake_p) {
    snake_node* temp;
    while (!is_empty(snake_p)) {
        temp = dequeue(snake_p);
        temp->next = NULL;
        temp->cell->row = -1;
        temp->cell->col = -1;
        temp->cell->type = EMPTY;
        free(temp);
    }
    free(snake_p);
} // destroy_snake