/**
* File: node.h
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
*
* This file defines the Node class, which is implemented in its respective .cpp file.
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