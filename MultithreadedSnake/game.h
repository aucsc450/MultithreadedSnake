/**
* File: game.h
*
* Author: Anjola Aina
* Last Modified: Tuesday, April 4th, 2023
*
* This file defines the game struct, which contains the objects that are relevant to the game. The functions defined in this file control the execution of the game.
*/
#ifndef game_h
#define game_h

#include <allegro.h>
#include <time.h>
#include <stdbool.h>

// Constants
#define WIDTH 800
#define HEIGHT 850
#define WHITE makecol(255, 255, 255)
#define GREY makecol(127, 127, 127) 
#define BLACK makecol(0, 0, 0)
#define KELLY_GREEN makecol(95, 195, 20)
#define DARK_LEMON_LIME makecol(121, 208, 33)
#define FOREST_BROWN makecol(63, 48, 29)
#define BROWN makecol(89, 63, 30)
#define DARK_BROWN makecol(26, 18, 6)
#define SIZE 15 // in board.h (called BOARD_SIZE), here for testing purposes

// The game struct
typedef struct game {
	BITMAP* buffer;
} game;

// Function definitions
game* create_game();
void draw_game_board(BITMAP* buffer);
void update_screen(BITMAP* buffer);
void destroy_game(game* game_obj);

#endif