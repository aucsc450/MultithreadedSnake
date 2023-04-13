/**
* File: queue.cpp
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
*
* This file implements the Queue class defined in its respective .h file.
*/
#include "queue.h"

/**
Creates a new queue that is empty.
*/
Queue::Queue() {
	front = NULL;
	rear = NULL;
	size = 0;
} // constructor

/**
Destroys the queue by dequeuing all elements in the queue and deleting it from memory.
*/
Queue::~Queue() {
    Node* temp;
    while (!is_empty()) {
        temp = dequeue();
        delete temp;
    }
} // destructor

/**
Gets the front of the queue.
@return - front of the queue
*/
Node* Queue::get_front() {
	return front;
} // get_front

/**
Gets the rear of the queue.
@return - rear of the queue
*/
Node* Queue::get_rear() {
	return rear;
} // get_rear

/**
Gets the size of the queue.
@return - size of the queue
*/
int Queue::get_size() {
	return size;
} // get_size

/**
Checks whether the queue is empty.
@return - true if the queue is empty, false otherwise
*/
bool Queue::is_empty() {
	if (size <= 0) {
		return true;
	}
	return false;
} // is_empty

/**
Adds a node to the rear of the queue.
@param cell_p - the cell to be added to the new node
*/
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

/**
Removes a node from the front of the queue.
@return - the front of the queue
*/
Node* Queue::dequeue() {
    Node* temp = front;
    front = front->get_next();
    size--;
    return temp;
} // dequeue

/**
Checks whether the specified node is the front node.
@param node_p - the node to compare to the front node
@return - true if node_p is equal to the front node, false otherwise
*/
bool Queue::is_front(Node* node_p) {
    if (node_p == front) {
        return true;
    }
    return false;
} // is_front

/**
Checks whether the specified node is the rear node.
@param node_p - the node to compare to the rear node
@return - true if node_p is equal to the rear node, false otherwise
*/
bool Queue::is_rear(Node* node_p) {
    if (node_p == rear) {
        return true;
    }
    return false;
} // is_rear