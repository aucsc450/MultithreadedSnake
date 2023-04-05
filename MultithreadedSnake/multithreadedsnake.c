/**
* File: multithreadedsnake.c
*
* Author: Anjola Aina
* Last Modified: Tuesday, April 2nd, 2023
*
* This file runs the game.
*/
#include "multithreadedsnake.h"

/*
The entry point of the game.
*/
int main(void) {
	if (allegro_init() != 0) {
		return 1;
	}
	set_window_title("Multithreaded Snake");
	set_color_depth(24);
	install_keyboard();
	set_keyboard_rate(10000, 0);
	int ret = set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting GFX mode.");
		return 1;
	}
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error initializing sound system.");
		return 1;
	}	
	game_state* a_game = create_game();
	if (a_game == NULL) {
		allegro_message("Error loading the game object.");
		return 1;
		
	}
	
	bool loaded_font = load_game_font(a_game);
	if (!loaded_font) {
		allegro_message("Error loading game font.");
		return 1;
	}

	draw_game_board(a_game->buffer, a_game->game_font);
	update_screen(a_game->buffer);
	
	while (!key[KEY_ESC]); // wait until the ESC key is pressed to do anything (busy waiting loop)
	destroy_game(a_game);
	allegro_exit();
	return 0;
}
END_OF_MAIN()