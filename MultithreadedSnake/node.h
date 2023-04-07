/**
* File: node.h
*
* Author: Anjola Aina
* Last Modified: Thursday, April 6th, 2023
*
* This file contains the cell struct, which represents a point in the game board.
* There contains two methods, one to create a cell and another to free a cell.
* There also exists an enum called cell_type, which determines what "object" is occupying the cell.
* To map the enum to its equivalent string, the following source was used to help achieve this: https://www.linkedin.com/pulse/mapping-enum-string-c-language-sathishkumar-duraisamy/
*/
#ifndef node_h
#define node_h
#include <stdlib.h>
#include <stdio.h>
#include "cell.h"


class Node {
private:
    Cell* data;
    Node* next;
public:
    Node(int row_p, int col_p, cell_type type_p);
    Node(Cell* cell_p);
    Node();
    ~Node();
    Cell* get_data();
    Node* get_next();
    void set_data(Cell* data_p);
    void set_next(Node* next_p);
};

#endif