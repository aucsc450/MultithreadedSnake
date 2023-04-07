/**
* File: board.h
*
* Author: Anjola Aina
* Last Modified: Thursday, April 6th, 2023
*
* This file contains the board struct, which represents the game board of snake.
* It is BOARD_SIZE * BOARD_SIZE large (a square), and consists of cells defined in the cell.h file and implemented in its respective .c file.
* There are functions to create and destroy the board, as well as a function to change a cell in the board.
* Initially, the board is empty.
*/
#ifndef board_h
#define board_h
#include "cell.h"

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
};

#endif