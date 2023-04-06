/**
* File: board.h
*
* Author: Anjola Aina
* Last Modified: Friday, March 31st, 2023
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

// The board struct
typedef struct board {
    cell* cells[BOARD_SIZE][BOARD_SIZE];
} board;

// Function definitions
board* create_board();
void change_cell_in_board(board* board_p, cell* cell_p);
bool generate_apple(board* board_p); // will be called in a specific thread
void destroy_board(board* board_p);

#endif