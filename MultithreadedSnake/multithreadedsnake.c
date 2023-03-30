#include <allegro.h>

#define WHITE makecol(255, 255, 255) // the colour white

/*
The entry point of the game.
*/
int main(void) {
	if (allegro_init() != 0) {
		return 1;
	}
	set_window_title("Snake");
	set_color_depth(24);
	install_keyboard();
	set_keyboard_rate(10000, 0);
	int ret = set_gfx_mode(GFX_SAFE, 800, 600, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting GFX mode.");
		return 1;
	}
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error initializing sound system.");
		return 1;
	}
	textout_ex(screen, font, "Welcome to Snake!", 10, 10, WHITE, -1);
	while (!key[KEY_ESC]); // wait until the ESC key is pressed to do anything (busy waiting loop)
	allegro_exit();
	return 0;
}
END_OF_MAIN()