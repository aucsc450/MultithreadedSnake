/**
* File: board.h
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
*
* This file defines the Board class, which is implemented in its respective .cpp file.
*/
#ifndef board_h
#define board_h
#include "cell.h"
#include <time.h>
#include <stdio.h>

// Constants
#define BOARD_SIZE 15

class Board {
private:
    Cell* cells[BOARD_SIZE][BOARD_SIZE];
public:
    Board();
    ~Board();
    Cell* get_specific_cell(int row, int col);
    void set_type_for_specific_cell(int row, int col, cell_type type_p);
    void generate_apple();
};

#endif