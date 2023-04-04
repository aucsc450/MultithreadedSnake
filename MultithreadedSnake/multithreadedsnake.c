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
	game* a_game = create_game();
	if (a_game == NULL) {
		allegro_message("Error loading the game object.");
		return 1;
		
	}
	else {
		draw_game_board(a_game->buffer);
		update_screen(a_game->buffer);
	}
	

	while (!key[KEY_ESC]); // wait until the ESC key is pressed to do anything (busy waiting loop)
	destroy_game(a_game);
	allegro_exit();
	return 0;
}
END_OF_MAIN()

//void draw_game_board() {
//	int start_x = 25;
//	int start_y = 75;
//	int end_x = 75;
//	int end_y = 125;
//	rectfill(screen, start_x, start_y, end_x, end_y, KELLY_GREEN);
//	bool swap_colour = false;
//	rectfill(screen, 0, 0, 800, 850, BROWN);
//	for (int i = 0; i < SIZE; i++) {
//		for (int j = 0; j < SIZE; j++) {
//			if (!swap_colour) {
//				rectfill(screen, start_x, start_y, end_x, end_y, KELLY_GREEN);
//				swap_colour = true;
//			}
//			else {
//				rectfill(screen, start_x, start_y, end_x, end_y, DARK_LEMON_LIME);
//				swap_colour = false;
//			}
//			start_x += 50;
//			end_x += 50;
//		} // inner for
//		start_x = 25;
//		end_x = 75;
//		start_y += 50;
//		end_y += 50;
//		if (i % 2 != 0) {
//			swap_colour = false;
//		}
//		else {
//			swap_colour = true;
//		}
//	} // outer for
//	textout_right_ex(screen, font, "Made by Anjola Aina", WIDTH - 20, HEIGHT - 15, WHITE, -1);
//} // draw_game_board