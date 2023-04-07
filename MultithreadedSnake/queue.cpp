/**
* File: queue.cpp
*
* Author: Anjola Aina
* Last Modified: April, March 30th, 2023
*
* This file implements the functions defined in the cell.h file.
*/
#include "queue.h"

Queue::Queue() {
	front = NULL;
	rear = NULL;
	size = 0;
} // constructor

Queue::~Queue() {
    Node* temp;
    while (!is_empty()) {
        temp = dequeue();
        delete temp;
    }
} // destructor

Node* Queue::get_front() {
	return front;
} // get_front

Node* Queue::get_rear() {
	return rear;
} // get_rear

int Queue::get_size() {
	return size;
} // get_size

bool Queue::is_empty() {
	if (size <= 0) {
		return true;
	}
	return false;
} // is_empty

void Queue::enqueue(Cell* cell_p) {
    Node* new_node = new Node(cell_p);
    if (is_empty()) {
        front = new_node;
    }
    else {
        rear->set_next(new_node);
    }
    rear = new_node;
    size++;
} // enqueue

Node* Queue::dequeue() {
    Node* temp = front;
    front = front->get_next();
    size--;
    return temp;
} // dequeue