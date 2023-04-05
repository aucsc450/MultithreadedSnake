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
void change_cell_in_board(board* game_board, cell* new_cell) {
    int row = new_cell->row;
    int col = new_cell->col;
    game_board->cells[row][col]->type = new_cell->type;
    destroy_cell(new_cell); // we don't need the new cell anymore
} // change_cell_in_board

/**
Generates an apple in the board.
@param game_board - the board to generate an apple in
@returns - true if the function was able to generate an apple, false otherwise
*/
boolean generate_apple(board* game_board) {
    int row = 0;
    int col = 0;
    while (TRUE) {
        row = rand() % BOARD_SIZE;
        col = rand() % BOARD_SIZE;
        if (game_board->cells[row][col]->type != SNAKE) {
            break;
        }
    }
    if (game_board->cells[row][col]->type != APPLE) {
        change_cell_in_board(game_board, create_cell(row, col, APPLE));
        return TRUE;
    }
    else {
        return FALSE; // there exists an apple in the board already
    }
} // generate_apple

/**
Prints the board. Used for testing purposes.
*/
void print_board(board* game_board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cell_type cell_var = game_board->cells[i][j]->type;
            printf("%s ", cell_type_names[cell_var]);
        }
        printf("\n");
    }
} // print_board

/**
Frees the board from memory, by freeing the individual cells in the board, and the board itself.
@param game_board - the board to be freed from memory
*/
void free_board(board* game_board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            destroy_cell(game_board->cells[i][j]);
        }
    }
    free(game_board);
} // free_board