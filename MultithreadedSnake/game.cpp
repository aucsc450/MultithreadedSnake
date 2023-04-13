/**
* File: game.cpp
*
* Author: Anjola Aina
* Last Modified: Monday, April 10th, 2023
*
* This file implements the game_state class.
*/
#include "game.h"

// Variables to be shared among all the threads
volatile int Game_State::speed_counter = 0;
volatile int Game_State::timer = 0;
bool Game_State::game_over = false;
Board* Game_State::game_board = new Board();
pthread_t Game_State::apple_thread;
pthread_t Game_State::input_thread;
direction Game_State::dir = NONE;

/*
Constructs a new instance of the game class, and initializes all variables.
*/
Game_State::Game_State() {
	buffer = create_bitmap(WIDTH, HEIGHT);
	game_font = NULL;
	background_music = NULL;
	crunch_sound = NULL;
	game_over_sound = NULL;
	game_board->generate_apple();
	player = new Snake();
	player->grow(new Cell(BOARD_SIZE / 2, BOARD_SIZE / 2, SNAKE));
	// dir = NONE;
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
Loads all BMP files into the sounds used in the game.
@return - true if all files was loaded successfully into their respective sounds, false otherwise
*/
bool Game_State::load_sounds() {
	background_music = load_sample("sounds\\background_music.wav");
	crunch_sound = load_sample("sounds\\apple_crunch.wav");
	game_over_sound = load_sample("sounds\\end_game_sound.wav");
	if (background_music != NULL && crunch_sound != NULL && game_over_sound != NULL) {
		return true;
	}
	return false; // sounds are null
} // load_sounds

/*
Initializes the game by loading all the game objects.
@return - true if every game object was loaded successfully, false otherwise
*/
bool Game_State::initialize_game() {
	bool loaded_fonts = load_fonts();
	bool loaded_sounds = load_sounds();
	if (!loaded_fonts || !loaded_sounds) {
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
	play_sample(background_music, VOLUME, PANNING, FREQUENCY, TRUE);
	new_game();
} // start_game

/*
Creates a new game.
*/
void Game_State::new_game() {
	run_game();
} // new_game

/*
Resets the game, by setting all game objects back to their initial states.
*/
void Game_State::reset_game() {
	game_board->reset();
	game_over = false;
	speed_counter = 0;
	timer = 0;
	total_score = 0;
	seconds_elasped = 0;
	minutes_elasped = 0;
	player->reset();
	player->grow(new Cell(BOARD_SIZE / 2, BOARD_SIZE / 2, SNAKE));
	//game_board->generate_apple();
} // reset_game

/*
Runs the whole game, from the main menu to the end game menu.
*/
void Game_State::run_game() {
	bool advance = main_menu();
	if (!advance) {
		return; // the esc button was pressed, so terminate game
	}
	int installed_interrupt = install_int_ex(increment_speed_counter, BPS_TO_TIMER(FPS));
	if (installed_interrupt != 0) {
		allegro_message("Error setting up the interrupt handler.");
		return; // an error has occured, so terminate game
	}
	bool pressed_esc = play_game();
	if (pressed_esc) {
		return;
	}
	end_game_menu();
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

/**
Returns the next position that the snake is to move to.
@param curr_position - the current position of the snake (including the row and column)
@return - a cell consisting of the updated row and column positions for the snake to go to
*/
Cell* Game_State::get_next_cell(Cell* curr_position) {
	int row = curr_position->get_row();
	int col = curr_position->get_col();
	switch (dir) {
		case LEFT:
			col--;
			break;
		case RIGHT:
			col++;
			break;
		case UP:
			row--;
			break;
		case DOWN:
			row++;
			break;
	}
	if (is_snake_out_of_bounds(row, col)) {  
		return NULL;
	}
	Cell* next_cell = game_board->get_specific_cell(row, col);
	return next_cell;
} // get_next_cell

/**
Determines whether the snake is out of bounds, by checking if the current row and col are either 0 or larger than the board size.
@param row - the x-coordinate of the snake's head
@param col - the y-coordinate of the snake's head
@return true if the snake is out of bounds, false otherwise
*/
bool Game_State::is_snake_out_of_bounds(int row, int col) {
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
		return true;
	}
	return false;
} // is_snake_out_of_bounds

/*
Runs the following methods associated with the game logic, such as moving the player, fish, and trash sprites,
getting input from the user, and ensuring that all sprites are not out of bounds.
*/
void Game_State::run_game_logic() {
	// handle_keyboard_input();
	if (dir != NONE) {
		Cell* curr_position = player->get_snake()->get_front()->get_data();
		Cell* next_cell = get_next_cell(curr_position);
		if (next_cell == NULL) {
			game_over = true;
			return;
		}
		bool snake_collision = player->collided(next_cell);
		if (snake_collision) {
			game_over = true;
			return;
		}
		player->move(next_cell);
		if (next_cell->get_type() == APPLE) {
			play_sample(crunch_sound, VOLUME * 2, PANNING, FREQUENCY, FALSE);
			player->grow(curr_position);
			next_cell->set_type(EMPTY);
			total_score += 100;
		}
		//dir = NONE;
	}
} // run_game_logic

/*
Runs the game.
@return - true if the user pressed the esc button, false otherwise
*/
bool Game_State::play_game() {
	bool pressed_esc = false;
	// Setting up threads
	apple_thread = create_pthread(spawn_apple, NULL);
	input_thread = create_pthread(handle_keyboard_input, NULL);
	while (!game_over) {
		while (speed_counter > 0) {
			speed_counter--;
			timer++;
			if (timer % SLOW_MOVEMENT_DOWN == 0) { // this slows down the game logic so that it executes less frequently
				run_game_logic();
			}
			// handle_keyboard_input();
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
		draw_snake();
		draw_apple();
		update_screen();
	} // game loop
	remove_int(increment_speed_counter); // removing the interrupt handler as we don't need it anymore
	return pressed_esc;
} // play_game

/*
Draws the game board to the buffer.
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
	textout_right_ex(buffer, font, "Made for AUCSC 450 Winter 2023", WIDTH - 20, HEIGHT - 15, WHITE, -1);
	textprintf_ex(buffer, game_font, 25, 25, WHITE, -1, "Score: %d", total_score);
	textout_right_ex(buffer, game_font, "Stop - ESC", WIDTH - 25, 25, WHITE, -1);
	if (seconds_elasped < 10) {
		textprintf_centre_ex(buffer, game_font, WIDTH / 2, 25, WHITE, -1, "%d : 0%d", minutes_elasped, seconds_elasped);
	}
	else {
		textprintf_centre_ex(buffer, game_font, WIDTH / 2, 25, WHITE, -1, "%d : %d", minutes_elasped, seconds_elasped);
	}
} // draw_game_board

/**
Draws the snake to the double buffer.
*/
void Game_State::draw_snake() {
	Node* temp = player->get_snake()->get_front();
	while (temp != NULL) {
		int row = temp->get_data()->get_row();
		int col = temp->get_data()->get_col();
		int x_pos = (col * TILE_SIZE) + X_OFFSET;
		int y_pos = (row * TILE_SIZE) + Y_OFFSET;
		rectfill(buffer, x_pos, y_pos, x_pos + SNAKE_BLOCK_SIZE, y_pos + SNAKE_BLOCK_SIZE, BLACK);
		if (player->get_snake()->is_front(temp)) {
			draw_snake_face(x_pos, y_pos);
		}
		temp = temp->get_next();
	} // while
} // draw_snake

/**
Draws the snake's face, depending on what direction the snake is currently going.
@param x_pos - the x position of the snake's front
@param y_pos - the y position of the snake's front
*/
void Game_State::draw_snake_face(int x_pos, int y_pos) {
	switch (dir) {
		case LEFT:
			draw_face_left(x_pos, y_pos);
			break;
		case RIGHT:
			draw_face_right(x_pos, y_pos);
			break;
		case UP:
			draw_face_up(x_pos, y_pos);
			break;
		case DOWN:
			draw_face_down(x_pos, y_pos);
			break;
		case NONE:
			draw_face_up(x_pos, y_pos);
	}
} // draw_snake_front

/**
Draws the face of the snake when the snake's direction is LEFT.
@param x_pos - the x position of the snake's front
@param y_pos - the y position of the snake's front
*/
void Game_State::draw_face_left(int x_pos, int y_pos) {
	// eyes
	rectfill(buffer, x_pos + 20, y_pos + 5, x_pos + 30, y_pos + 15, WHITE);
	rectfill(buffer, x_pos + 20, y_pos + 30, x_pos + 30, y_pos + 40, WHITE);
	// pupils
	rectfill(buffer, x_pos + 25, y_pos + 7, x_pos + 30, y_pos + 13, BLACK);
	rectfill(buffer, x_pos + 25, y_pos + 32, x_pos + 30, y_pos + 38, BLACK);
	// white eye part
	rectfill(buffer, x_pos + 27, y_pos + 8, x_pos + 28, y_pos + 9, WHITE);
	rectfill(buffer, x_pos + 27, y_pos + 33, x_pos + 28, y_pos + 34, WHITE);
	// nostrils
	rectfill(buffer, x_pos + 8, y_pos + 10, x_pos + 10, y_pos + 12, GREY);
	rectfill(buffer, x_pos + 8, y_pos + 32, x_pos + 10, y_pos + 34, GREY);
} // draw_face_left

/**
Draws the face of the snake when the snake's direction is RIGHT.
@param x_pos - the x position of the snake's front
@param y_pos - the y position of the snake's front
*/
void Game_State::draw_face_right(int x_pos, int y_pos) {
	// eyes
	rectfill(buffer, x_pos + 15, y_pos + 5, x_pos + 25, y_pos + 15, WHITE);
	rectfill(buffer, x_pos + 15, y_pos + 30, x_pos + 25, y_pos + 40, WHITE);
	// pupils
	rectfill(buffer, x_pos + 15, y_pos + 7, x_pos + 20, y_pos + 13, BLACK);
	rectfill(buffer, x_pos + 15, y_pos + 32, x_pos + 20, y_pos + 38, BLACK);
	// white eye part
	rectfill(buffer, x_pos + 17, y_pos + 8, x_pos + 18, y_pos + 9, WHITE);
	rectfill(buffer, x_pos + 17, y_pos + 33, x_pos + 18, y_pos + 34, WHITE);
	// nostrils
	rectfill(buffer, x_pos + 35, y_pos + 10, x_pos + 37, y_pos + 12, GREY);
	rectfill(buffer, x_pos + 35, y_pos + 32, x_pos + 37, y_pos + 34, GREY);
} // draw_face_right

/**
Draws the face of the snake when the snake's direction is UP.
@param x_pos - the x position of the snake's front
@param y_pos - the y position of the snake's front
*/
void Game_State::draw_face_up(int x_pos, int y_pos) {
	// eyes
	rectfill(buffer, x_pos + 5, y_pos + 15, x_pos + 15, y_pos + 25, WHITE);
	rectfill(buffer, x_pos + 30, y_pos + 15, x_pos + 40, y_pos + 25, WHITE);
	// pupils
	rectfill(buffer, x_pos + 7, y_pos + 19, x_pos + 13, y_pos + 25, BLACK);
	rectfill(buffer, x_pos + 32, y_pos + 19, x_pos + 38, y_pos + 25, BLACK);
	// white eye part
	rectfill(buffer, x_pos + 8, y_pos + 20, x_pos + 9, y_pos + 21, WHITE);
	rectfill(buffer, x_pos + 36, y_pos + 20, x_pos + 37, y_pos + 21, WHITE);
	// nostrils
	rectfill(buffer, x_pos + 10, y_pos + 7, x_pos + 12, y_pos + 9, GREY);
	rectfill(buffer, x_pos + 33, y_pos + 7, x_pos + 35, y_pos + 9, GREY);
} // draw_face_up

/**
Draws the face of the snake when the snake's direction is DOWN.
@param x_pos - the x position of the snake's front
@param y_pos - the y position of the snake's front
*/
void Game_State::draw_face_down(int x_pos, int y_pos) {
	// eyes
	rectfill(buffer, x_pos + 5, y_pos + 15, x_pos + 15, y_pos + 25, WHITE);
	rectfill(buffer, x_pos + 30, y_pos + 15, x_pos + 40, y_pos + 25, WHITE);
	// pupils
	rectfill(buffer, x_pos + 7, y_pos + 15, x_pos + 13, y_pos + 21, BLACK);
	rectfill(buffer, x_pos + 32, y_pos + 15, x_pos + 38, y_pos + 21, BLACK);
	// white eye part
	rectfill(buffer, x_pos + 8, y_pos + 16, x_pos + 9, y_pos + 17, WHITE);
	rectfill(buffer, x_pos + 36, y_pos + 16, x_pos + 37, y_pos + 17, WHITE);
	// nostrils
	rectfill(buffer, x_pos + 10, y_pos + 37, x_pos + 12, y_pos + 39, GREY);
	rectfill(buffer, x_pos + 33, y_pos + 37, x_pos + 35, y_pos + 39, GREY);
} // draw_face_down

/**
Draws the apple to the double buffer.
*/
void Game_State::draw_apple() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (game_board->get_specific_cell(i, j)->get_type() == APPLE) {
				int x_pos = (j * TILE_SIZE) + X_OFFSET;
				int y_pos = (i * TILE_SIZE) + Y_OFFSET;
				circlefill(buffer, x_pos + 16, y_pos + 25, 17, APPLE_RED);
				circlefill(buffer, x_pos + 29, y_pos + 25, 17, APPLE_RED);
				rectfill(buffer, x_pos + 21, y_pos, x_pos + 24, y_pos + 12, FOREST_BROWN);
			} // if
		} // inner for
	} // outer for
} // draw_apple

/*
Displays the end game menu.
@param background - the static background
@return - true if the escape key was pressed, false if the enter key was pressed
*/
void Game_State::end_game_menu() {
	clear_bitmap(buffer);
	stop_sample(background_music);
	play_sample(game_over_sound, VOLUME, PANNING, FREQUENCY, FALSE);
	draw_game_board();
	textout_centre_ex(buffer, game_font, "Uh oh, the Game has ended!", WIDTH / 2, HEIGHT / 2 - 25, WHITE, -1);
	textout_centre_ex(buffer, game_font, "Press ESC to exit the game!", WIDTH / 2, HEIGHT / 2, WHITE, -1);
	update_screen();
	while (true) {
		clear_keybuf();
		if (key[KEY_ESC]) {
			break;
		}
	} // while
} // end_game_menu

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

/*
Increases the speed counter, which is used to update / move the objects in the game.
*/
void Game_State::increment_speed_counter() {
	speed_counter++;
} // increment_speed_counter
END_OF_FUNCTION(increment_speed_counter);

/**
Creates a new thread with the thread function and thread parameters specified in the parameters of this function, and returns the thread id.
@param thread_function - the function to be run by the new thread
@param param - the parameter(s) for the thread function
@return - the thread id of the newly created thread.
*/
pthread_t Game_State::create_pthread(void* (*thread_function) (void*), void* param) {
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, thread_function, param);
	return thread_id;
} // create_pthread

/**
Determines whether the apple is currently spawned in the board.
@return - true if the apple is in the board, false otherwise
*/
bool Game_State::is_apple_in_board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (game_board->get_specific_cell(i, j)->get_type() == APPLE) {
				return true;
			} // if
		} // inner for
	} // outer for
	return false; // an apple is currently NOT in the board
} // is_apple_in_board

/**
The thread method that spawns an apple if an apple is not already in the game board.
@param args - thread parameters (none)
*/
void* Game_State::spawn_apple(void* args) {
	while (!game_over) {
		if (!is_apple_in_board()) {
			game_board->generate_apple();
		}
	} // while
	pthread_join(apple_thread, NULL);
	return NULL;
} // spawn_apple

/**
Handles keyboard input by changing the direction of the snake based on what key the user presses.
*/
void* Game_State::handle_keyboard_input(void* args) {
	while (!game_over) {
		while (speed_counter > 0) {
			clear_keybuf();
			if (key[KEY_LEFT]) {
				dir = LEFT;
			}
			else if (key[KEY_RIGHT]) {
				dir = RIGHT;
			}
			else if (key[KEY_UP]) {
				dir = UP;
			}
			else if (key[KEY_DOWN]) {
				dir = DOWN;
			}
		} // inner while
	} // game loop
	pthread_join(input_thread, NULL);
	return NULL;
} // handle_keyboard_input