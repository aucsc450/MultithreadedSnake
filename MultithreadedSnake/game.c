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
	game_state* game_state_t = malloc(sizeof(game_state));
	if (game_state_t != NULL) {
		game_state_t->buffer = create_bitmap(WIDTH, HEIGHT);
		game_state_t->game_font = NULL;
		game_state_t->player = create_snake();
		enqueue(game_state_t->player, create_cell(SIZE / 2, SIZE / 2, SNAKE));
		return game_state_t;
	}
	return NULL; // not enough memory to create a new game
} // create_game

bool load_game_font(game_state* game_state_p) {
	game_state_p->game_font = load_font("graphics\\franklin_gothic_heavy_font.pcx", NULL, NULL);
	if (game_state_p->game_font == NULL) {
		return false; // an error occured when loading the fonts
	}
	return true;
} // load_game_font

/**
Draws the game board to the specified buffer.
@param buffer - the double buffer specified in the game object (drawn to the screen in a subsequent call to update_screen)
*/
void draw_game_board(BITMAP* buffer, FONT* game_font) {
	int start_x = INIT_X_START_POS;
	int start_y = INIT_Y_START_POS;
	int end_x = INIT_X_END_POS;
	int end_y = INIT_Y_END_POS;
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
			start_x += TILE_SIZE;
			end_x += TILE_SIZE;
		} // inner for
		start_x = INIT_X_START_POS;
		end_x = INIT_X_END_POS;
		start_y += TILE_SIZE;
		end_y += TILE_SIZE;
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

void testing_snake_spawning(game_state* game_state_p) {
	int row = game_state_p->player->front->cell->row; // 7 
	int col = game_state_p->player->front->cell->col; // 7
	int x_pos = row * TILE_SIZE + X_OFFSET;
	int y_pos = col * TILE_SIZE + Y_OFFSET;
	rectfill(game_state_p->buffer, x_pos, y_pos, x_pos + SNAKE_BLOCK_SIZE, y_pos + SNAKE_BLOCK_SIZE, BLACK);
	textprintf_ex(game_state_p->buffer, font, 20, HEIGHT - 20, WHITE, -1, "Row %d, Col: %d", game_state_p->player->front->cell->row, game_state_p->player->front->cell->col);
	textprintf_ex(game_state_p->buffer, font, 20, HEIGHT - 40, WHITE, -1, "X Pos %d, Y Pos: %d", x_pos, y_pos);
}

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
void destroy_game(game_state* game_state_p) {
	destroy_bitmap(game_state_p->buffer);
	destroy_font(game_state_p->game_font);
	destroy_snake(game_state_p->player);
	free(game_state_p);
} // destroy_game