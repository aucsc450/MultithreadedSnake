/**
* File: board.c
*
* Author: Anjola Aina
* Last Modified: Friday, March 31st, 2023
*
* This file implements the functions defined in the board.h file.
*/
#include "board.h"

/**
Creates a board of empty cells.
@return - the board containing empty cells
*/
board* create_board() {
    board* game_board = malloc(sizeof(board));
    if (game_board != NULL) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                game_board->cells[i][j] = create_cell(i, j, EMPTY);
            }
        }
        return game_board;
    }
    return NULL; // not enough space in memory to create a board struct
} // create_board

/**
Changes a cell in the board.
@param game_board - the board containing the cell to change/update
@param new_cell - the cell containing the new information to be updated in the board
*/
void change_cell_in_board(board* board_p, cell* cell_p) {
    int row = cell_p->row;
    int col = cell_p->col;
    board_p->cells[row][col]->type = cell_p->type;
    destroy_cell(cell_p); // we don't need the new cell anymore
} // change_cell_in_board

/**
Generates an apple in the board.
@param game_board - the board to generate an apple in
@returns - true if the function was able to generate an apple, false otherwise
*/
bool generate_apple(board* board_p) {
    int row = 0;
    int col = 0;
    while (true) {
        row = rand() % BOARD_SIZE;
        col = rand() % BOARD_SIZE;
        if (board_p->cells[row][col]->type != SNAKE) {
            break;
        }
    }
    if (board_p->cells[row][col]->type != APPLE) {
        change_cell_in_board(board_p, create_cell(row, col, APPLE));
        return true;
    }
    else {
        return false; // there exists an apple in the board already
    }
} // generate_apple

/**
Frees the board from memory, by freeing the individual cells in the board, and the board itself.
@param game_board - the board to be freed from memory
*/
void destroy_board(board* board_p) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            destroy_cell(board_p->cells[i][j]);
        }
    }
    free(board_p);
} // free_board