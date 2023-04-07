/**
* File: node.cpp
*
* Author: Anjola Aina
* Last Modified: Thursday, April 6th, 2023
*
* This file contains the cell struct, which represents a point in the game board.
* There contains two methods, one to create a cell and another to free a cell.
* There also exists an enum called cell_type, which determines what "object" is occupying the cell.
* To map the enum to its equivalent string, the following source was used to help achieve this: https://www.linkedin.com/pulse/mapping-enum-string-c-language-sathishkumar-duraisamy/
*/
#include "node.h"

Node::Node(int row_p, int col_p, cell_type type_p) {
	data = new Cell(row_p, col_p, type_p);
	next = NULL;
} // constructor #1

Node::Node(Cell* cell_p) {
	data = new Cell(cell_p->get_row(), cell_p->get_col(), cell_p->get_type());
	next = NULL;
} // constructor #2

Node::Node() {
	data = new Cell();
	next = NULL;
} // default constructor

Node::~Node() {
	data->set_cell(-1, -1, EMPTY);
	next = NULL;
} // destructor

Cell* Node::get_data() {
	return data;
} // get_data

Node* Node::get_next() {
	return next;
} // get_next

void Node::set_data(Cell* data_p) {
	data->set_cell(data_p->get_row(), data_p->get_col(), data_p->get_type());
} // set_data

void Node::set_next(Node* next_p) {
	next = next_p;
} // set_next