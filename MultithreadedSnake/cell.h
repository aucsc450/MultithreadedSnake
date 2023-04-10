/**
* File: cell.h
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
*
* This file defines the cell_type enum and the Cell class, which is implemented in its respective .cpp file.
*/
#ifndef cell_h
#define cell_h
#include <stdlib.h>
#include <stdio.h>

typedef enum cell_type {
    EMPTY,
    APPLE,
    SNAKE
} cell_type; 

class Cell {
private:
    int row;
    int col;
    cell_type type;
public:
    Cell(int row_p, int col_p, cell_type type_p);
    Cell(int row_p, int col_p);
    Cell();
    ~Cell();
    int get_row();
    int get_col();
    cell_type get_type();
    void set_type(cell_type new_type);
    void set_cell(int new_row, int new_col, cell_type new_type);
    bool same_cell(Cell* cell_p);
};

#endif