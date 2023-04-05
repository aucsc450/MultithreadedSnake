///**
//* File: queue.c
//*
//* Author: Anjola Aina
//* Last Modified: Tuesday, April 4th, 2023
//*
//* This file implements the functions defined in the queue.h file.
//*/
//#include "queue.h"
//
///**
//Creates a new queue by setting the front and rear pointers initially to null, and the size of the queue initially to 0.
//@return a new queue
//*/
//queue* create_queue() {
//    queue* a_queue = malloc(sizeof(queue));
//    if (a_queue == NULL) {
//        return NULL; // an error has occured when creating the queue
//    }
//    a_queue->front = NULL;
//    a_queue->rear = NULL;
//    a_queue->size = 0;
//    return a_queue;
//} // create_queue
//
///**
//Checks whether the queue is empty or not.
//@param a_queue - the queue
//@return - true if the queue is empty, false otherwise
//*/
//boolean is_empty(queue* a_queue) {
//    if (a_queue->size <= EMPTY_QUEUE) {
//        return TRUE; // the queue is empty
//    }
//    return FALSE; // the queue is NOT empty
//} // is_empty
//
///**
//Adds a node to the rear of the queue.
//@param a_queue - the queue to perform the operation on
//@param a_cell - the cell of the new node
//*/
//void enqueue(queue* a_queue, cell* a_cell) {
//    node* new_node = malloc(sizeof(node));
//    new_node->cell.row = a_cell->row;
//    new_node->cell.col = a_cell->col;
//    new_node->cell.type = a_cell->type;
//    free_cell(a_cell); // we don't need the new cell anymore
//    if (is_empty(a_queue)) {
//        a_queue->front = new_node;
//        a_queue->rear = new_node;
//    }
//    else {
//        a_queue->rear->next = new_node;
//        a_queue->rear = new_node;
//    }
//    a_queue->size++; // increase the size of the queue
//} // enqueue
//
///**
//Removes and returns a node from the front of the queue.
//@param a_queue - the queue to perform the operation on
//@return - the node that was at the front of the queue
//*/
//node* dequeue(queue* a_queue) {
//    node* temp = malloc(sizeof(node));
//    temp = a_queue->front;
//    a_queue->front = a_queue->front->next;
//    a_queue->size--; // decrease the size of the queue
//    return temp;
//} // dequeue
//
///**
//Changes a cell in the snake.
//@param a_queue - the board containing the cell to change/update
//@param new_cell - the cell containing the new information to be updated in the snake
//*/
//void change_cells_in_queue(queue* a_queue, direction dir) {
//    node* temp = a_queue->front;
//    while (temp != NULL) {
//        switch (dir) {
//        case LEFT:
//            temp->cell.col--;
//            break;
//        case RIGHT:
//            temp->cell.col++;
//            break;
//        case UP:
//            temp->cell.row--;
//            break;
//        case DOWN:
//            temp->cell.row++;
//            break;
//        } // switch
//        temp = temp->next;
//    } // while
//    free(temp);
//} // change_cells_in_queue
//
///**
//Frees a queue from memory.
//@param a_queue - the queue to be removed from memory
//*/
//void free_queue(queue* a_queue) {
//    node* temp;
//    while (!is_empty(a_queue)) {
//        temp = dequeue(a_queue);
//        temp->next = NULL;
//        temp->cell.row = -1;
//        temp->cell.col = -1;
//        temp->cell.type = EMPTY;
//        free(temp);
//    }
//    free(a_queue);
//} // free_queue