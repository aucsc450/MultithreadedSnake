/**
* File: node.cpp
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
*
* This file implements the Node class, defined in its respective .h file.
*/
#include "node.h"

/**
Creates a new node from the specified row, column and type parameters.
@param row_p - the row of the new cell
@param col_p - the col of the new cell
@param type_p - the type of the new cell
*/
Node::Node(int row_p, int col_p, cell_type type_p) {
	data = new Cell(row_p, col_p, type_p);
	next = NULL;
} // constructor #1

/**
Creates a new node from the specified cell.
@param cell_p - the new cell (data) of the node
*/
Node::Node(Cell* cell_p) {
	data = new Cell(cell_p->get_row(), cell_p->get_col(), cell_p->get_type());
	next = NULL;
} // constructor #2

/**
Creates a new node with default values.
*/
Node::Node() {
	data = new Cell();
	next = NULL;
} // default constructor

/**
Destroys a node from memory.
*/
Node::~Node() {
	data->set_cell(-1, -1, EMPTY);
	next = NULL;
} // destructor

/**
Gets a node's data.
@return - cell (data) of the node
*/
Cell* Node::get_data() {
	return data;
} // get_data

/**
Gets the next link of the node.
@return - the next node (or NULL if it doesn't exist)
*/
Node* Node::get_next() {
	return next;
} // get_next

/**
Sets the data for the node.
@param data_p - the new data of the node
*/
void Node::set_data(Cell* data_p) {
	data->set_cell(data_p->get_row(), data_p->get_col(), data_p->get_type());
} // set_data

/**
Sets the next link of the node.
@param next_p - the next node
*/
void Node::set_next(Node* next_p) {
	next = next_p;
} // set_next