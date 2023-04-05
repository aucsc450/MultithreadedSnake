/**
* File: game.c
*
* Author: Anjola Aina
* Last Modified: Tuesday, April 4th, 2023
*
* This file implements the game struct and its associated functions.
*/
#include "game.h"

/**
Creates a new game.
@return - the game struct in memory, or NULL if not enough memory is available to create a new game
*/
game_state* create_game() {
	game_state* game_obj = malloc(sizeof(game_state));
	if (game_obj != NULL) {
		game_obj->buffer = create_bitmap(WIDTH, HEIGHT);
		game_obj->game_font = NULL;
		return game_obj;
	}
	return NULL; // not enough memory to create a new game
} // create_game

bool load_game_font(game_state* game_obj) {
	game_obj->game_font = load_font("graphics\\franklin_gothic_heavy_font.pcx", NULL, NULL);
	if (game_obj->game_font == NULL) {
		return false; // an error occured when loading the fonts
	}
	return true; // 
}

/**
Draws the game board to the specified buffer.
@param buffer - the double buffer specified in the game object (drawn to the screen in a subsequent call to update_screen)
*/
void draw_game_board(BITMAP* buffer, FONT* game_font) {
	int start_x = 25;
	int start_y = 75;
	int end_x = 75;
	int end_y = 125;
	clear_bitmap(buffer);
	rectfill(buffer, 0, 0, WIDTH, HEIGHT, BROWN);
	rectfill(buffer, start_x, start_y, end_x, end_y, KELLY_GREEN);
	bool swap_colour = false;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (!swap_colour) {
				rectfill(buffer, start_x, start_y, end_x, end_y, KELLY_GREEN);
				swap_colour = true;
			}
			else {
				rectfill(buffer, start_x, start_y, end_x, end_y, DARK_LEMON_LIME);
				swap_colour = false;
			}
			start_x += 50;
			end_x += 50;
		} // inner for
		start_x = 25;
		end_x = 75;
		start_y += 50;
		end_y += 50;
		if (i % 2 != 0) {
			swap_colour = false;
		}
		else {
			swap_colour = true;
		}
	} // outer for
	textout_right_ex(buffer, font, "Made by Anjola Aina", WIDTH - 20, HEIGHT - 15, WHITE, -1);
	textprintf_ex(buffer, game_font, 25, 25, WHITE, -1, "Score: %d", 0);
	textout_right_ex(buffer, game_font, "Stop - ESC", WIDTH - 25, 25, WHITE, -1);
	textprintf_centre_ex(buffer, game_font, WIDTH / 2, 25, WHITE, -1, "%d : %d%d", 0, 0, 0);


} // draw_game_board

/**
Updates the game screen, by blitting the double buffer to the screen.
@param buffer - the double buffer specified in the game object
*/
void update_screen(BITMAP* buffer) {
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
	release_screen();
} // update_screen

/**
Destroys all game objects, and frees the game from memory.
@param game_obj - the game object to be freed from memory
*/
void destroy_game(game_state* game_obj) {
	destroy_bitmap(game_obj->buffer);
	destroy_font(game_obj->game_font);
	free(game_obj);
} // destroy_game