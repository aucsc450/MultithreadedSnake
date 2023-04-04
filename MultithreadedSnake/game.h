/**
* File: game.h
*
* Author: Anjola Aina
* Last Modified: Sunday, April 2nd, 2023
*
* This file controls the execution of the game. Once completed, everything in this file and the main.c file will be transferred over to the
* game.h and game.c files respectively so that the main file will execute the program.
*/
#ifndef game_h
#define game_h

#include <allegro.h>
#include <time.h>
#include <stdbool.h>

// Constants //

// Screen Sizes
#define WIDTH 800
#define HEIGHT 850

// Colours
#define WHITE makecol(255, 255, 255)
#define GREY makecol(127, 127, 127) 
#define BLACK makecol(0, 0, 0)
#define KELLY_GREEN makecol(95, 195, 20)
#define DARK_LEMON_LIME makecol(121, 208, 33)
#define FOREST_BROWN makecol(63, 48, 29)
#define BROWN makecol(89, 63, 30)
#define DARK_BROWN makecol(26, 18, 6)
#define SIZE 15 // will be available in board.h (called BOARD_SIZE)

// Game Objects //
typedef struct game {
	BITMAP* buffer;
} game;

// Move to game.c
game* create_game();
void draw_game_board(BITMAP* buffer);
void update_screen(BITMAP* buffer);
void destroy_game(game* game_obj);

#endif