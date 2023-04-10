/**
* File: multithreadedsnake.cpp
*
* Author: Anjola Aina
* Last Modified: Sunday, April 9th, 2023
*
* This file runs the game.
*/
#include "multithreadedsnake.h"

/*
The entry point of the game.
*/
int main(void) {
	srand(time(NULL));
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

	Game_State* game_state_t = new Game_State();
	game_state_t->start_game();
	//textout_right_ex(screen, font, "Made by Anjola Aina", WIDTH - 20, HEIGHT - 15, WHITE, -1);
	//while (!key[KEY_ESC]); // wait until the ESC key is pressed to do anything (busy waiting loop)
	allegro_exit();
	return 0;
}
END_OF_MAIN()