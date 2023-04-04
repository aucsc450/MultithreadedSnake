#include "game.h"

game* create_game() {
	game* game_obj = malloc(sizeof(game));
	if (game_obj != NULL) {
		game_obj->buffer = create_bitmap(WIDTH, HEIGHT);
		return game_obj;
	}
	return NULL; // something wrong happened when allocating memory
}

void draw_game_board(BITMAP* buffer) {
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
}

void update_screen(BITMAP* buffer) {
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
	release_screen();
}

void destroy_game(game* game_obj) {
	destroy_bitmap(game_obj->buffer);
	free(game_obj);
}