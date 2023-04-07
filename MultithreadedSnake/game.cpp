/**
* File: game.cpp
*
* Author: Anjola Aina
* Last Modified: Tuesday, April 4th, 2023
*
* This file implements the game struct and its associated functions.
*/
#include "game.h"

volatile int Game_State::speed_counter = 0;

/*
Constructs a new instance of the game class, and initializes all variables.
*/
Game_State::Game_State() {
	buffer = create_bitmap(WIDTH, HEIGHT);
	game_font = NULL;
	game_board = new Board();
	game_over = false;
	speed_counter = 0;
	timer = 0;
	total_score = 0;
	seconds_elasped = 0;
	minutes_elasped = 0;
	LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
} // constructor

/*
Destroys the bitmaps, fonts, and samples associated with the game.
*/
Game_State::~Game_State() {
	destroy_bitmap(buffer);
	destroy_font(game_font);
} // destructor

/*
Loads all BMP files into the fonts used in the game.
@return - true if all files was loaded successfully into their respective fonts, false otherwise
*/
bool Game_State::load_fonts() {
	game_font = load_font("graphics\\franklin_gothic_heavy_font.pcx", NULL, NULL);
	if (game_font != NULL) {
		return true;
	}
	return false; // font is null
} // load_fonts

/*
Initializes the game by loading all the game objects.
@return - true if every game object was loaded successfully, false otherwise
*/
bool Game_State::initialize_game() {
	bool loaded_fonts = load_fonts();
	if (!loaded_fonts) {
		return false;
	}
	return true;
} // initialize_game

/*
Starts the game by ensuring that all game objects have been loaded, and calls the new_game function to
create a new game. If at least one game object has not loaded successfully, an error message is printed
in which afterwards, the game closes.
*/
void Game_State::start_game() {
	bool initialized_game = initialize_game();
	if (!initialized_game) {
		allegro_message("Error loading game objects.");
		return;
	}
	new_game();
} // start_game

/*
Creates a new game by setting all game values to their default state and runs the game.
This function calls itself recursively every time the player wants to replay the game.
*/
void Game_State::new_game() {
	bool play_again = run_game();
	if (play_again) {
		reset_game();
		new_game();
	}
} // new_game

/*
Resets the game, by setting all game objects back to their initial states.
*/
void Game_State::reset_game() {
	game_over = false;
	speed_counter = 0;
	timer = 0;
	total_score = 0;
	seconds_elasped = 0;
	minutes_elasped = 0;
} // reset_game

/*
Runs the whole game, from the main menu to the end game menu.
@return - true if the player wants to play the game again, false otherwise
*/
bool Game_State::run_game() {
	bool advance = main_menu();
	if (!advance) {
		return false; // game is over
	}
	int installed_interrupt = install_int_ex(increment_speed_counter, BPS_TO_TIMER(FPS));
	if (installed_interrupt != 0) {
		allegro_message("Error setting up the interrupt handler.");
		return false; // an error has occured, so do not restart the game again
	}
	bool game_ended = play_game();
	if (game_ended) {
		return false; // game is over
	}
	return true; // the player wants to play the game again
} // run_game

/*
Displays the main menu of the game.
@param background - the static background
@return - true if the enter key was pressed was pressed, false if the escape key was pressed
*/
bool Game_State::main_menu() {
	clear_bitmap(buffer);
	draw_game_board();
	textout_centre_ex(buffer, game_font, "Welcome to Snake! Press the ENTER button to start the game!", WIDTH / 2, HEIGHT / 2, WHITE, -1);
	update_screen();
	while (true) {
		clear_keybuf();
		if (key[KEY_ESC]) {
			return false;
		}
		if (key[KEY_ENTER]) {
			key[KEY_ENTER] = 0; // so that the user can press the key again
			return true; // the enter key was pressed
		}
	} // while
} // main_menu

/*
Runs the following methods associated with the game logic, such as moving the player, fish, and trash sprites,
getting input from the user, and ensuring that all sprites are not out of bounds.
*/
void Game_State::run_game_logic() {

} // run_game_logic

/*
Runs the actual game.
@return - true if the game was over by pressing the ESC key, false otherwise
*/
bool Game_State::play_game() {
	bool pressed_esc = false;
	bool skip_timer = true;
	while (!game_over) {
		while (speed_counter > 0) {
			speed_counter--;
			run_game_logic();
			timer++;
		} // inner while

		// Game is over if the user has pressed the ESC key
		if (key[KEY_ESC]) {
			game_over = true;
			pressed_esc = true;
		}

		// Determining how long the player has played for currently
		seconds_elasped = (timer / FPS) % FPS;
		minutes_elasped = (timer / FPS) / FPS;
		
		// Updating the screen
		draw_game_board();
		update_screen();
		// draw_game_objects();
		

	} // game loop
	remove_int(increment_speed_counter); // removing the interrupt handler as we don't need it anymore
	return pressed_esc;
} // play_game

/*
Draws all the game objects to the buffer, and updates the screen at the end.
*/
void Game_State::draw_game_objects() {
	
} // draw_game_objects

/*
Draws all the game objects to the buffer, and updates the screen at the end.
*/
void Game_State::draw_game_board() {
	int start_x = INIT_X_START_POS;
	int start_y = INIT_Y_START_POS;
	int end_x = INIT_X_END_POS;
	int end_y = INIT_Y_END_POS;
	clear_bitmap(buffer);
	rectfill(buffer, 0, 0, WIDTH, HEIGHT, BROWN);
	rectfill(buffer, start_x, start_y, end_x, end_y, KELLY_GREEN);
	bool swap_colour = false;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (!swap_colour) {
				rectfill(buffer, start_x, start_y, end_x, end_y, KELLY_GREEN);
				swap_colour = true;
			}
			else {
				rectfill(buffer, start_x, start_y, end_x, end_y, DARK_LEMON_LIME);
				swap_colour = false;
			}

			// For testing purposes - delete later
			// textprintf_centre_ex(buffer, font, start_x + 25, start_y, WHITE, -1, "(%d, %d)", game_board->get_specific_cell(i, j)->get_row(), game_board->get_specific_cell(i, j)->get_col());


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
	textprintf_ex(buffer, game_font, 25, 25, WHITE, -1, "Score: %d", total_score);
	textout_right_ex(buffer, game_font, "Stop - ESC", WIDTH - 25, 25, WHITE, -1);
	if (seconds_elasped < 10) {
		textprintf_centre_ex(buffer, game_font, WIDTH / 2, 25, WHITE, -1, "%d : 0%d", minutes_elasped, seconds_elasped);
	}
	else {
		textprintf_centre_ex(buffer, game_font, WIDTH / 2, 25, WHITE, -1, "%d : %d", minutes_elasped, seconds_elasped);
	}
} // draw_game_board

void Game_State::draw_snake() {

} // draw_snake

/*
Increases the speed counter, which is used to update / move the objects in the game.
*/
void Game_State::increment_speed_counter() {
	speed_counter++;
} // increment_speed_counter
END_OF_FUNCTION(increment_speed_counter);

/*
The new thread function that updates the screen. It works the same way the update_screen() function used to work, with the
only difference being is that another thread executes it.
@param game_buffer - the double buffer of the game (represented as a void pointer)
*/
void Game_State::update_screen() {
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
	release_screen();
} // update_screen