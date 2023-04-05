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
#include "boolean.h"

// Constants
#define BOARD_SIZE 5

// The board struct
typedef struct board {
    cell* cells[BOARD_SIZE][BOARD_SIZE];
} board;

// Function definitions
board* create_board();
void change_cell_in_board(board* game_board, cell* new_cell);
boolean generate_apple(board* game_board); // will be called in a specific thread
void print_board(board* game_board);
void free_board(board* game_board);

#endif