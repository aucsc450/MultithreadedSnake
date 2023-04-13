/**
* File: game.h
*
* Author: Anjola Aina
* Last Modified: Thursday, April 13th, 2023
*
* This file defines the game_state class, which contains the objects and functions controlling the execution of the game.
*/
#ifndef game_h
#define game_h

#define HAVE_STRUCT_TIMESPEC
#include <allegro.h>
#include <pthread.h>
#include "board.h"
#include "snake.h"

// Screen Constants
#define WIDTH 800
#define HEIGHT 850

// Colour Constants
#define WHITE makecol(255, 255, 255)
#define GREY makecol(127, 127, 127) 
#define BLACK makecol(0, 0, 0)
#define APPLE_RED makecol(255, 8 ,0)
#define KELLY_GREEN makecol(95, 195, 20)
#define DARK_LEMON_LIME makecol(121, 208, 33)
#define FOREST_BROWN makecol(63, 48, 29)
#define BROWN makecol(89, 63, 30)
#define DARK_BROWN makecol(26, 18, 6)

// Game Constants
#define FPS 60
#define VOLUME 32
#define PANNING 32
#define FREQUENCY 1000
#define SLOW_MOVEMENT_DOWN 7
#define MAX_SCORE_LEN 12 // max int digits = 10 + 1 to account for the '\0' (null) character and + 1 for the '-' character
#define MAX_TIME_LEN 3

// Board & Tile Size Constants
#define SIZE 15
#define TILE_SIZE 50
#define INIT_X_START_POS 25
#define INIT_X_END_POS 75
#define INIT_Y_START_POS 75
#define INIT_Y_END_POS 125

// Offset Constants
#define X_OFFSET 27
#define Y_OFFSET 77
#define SNAKE_BLOCK_SIZE 45

// The game_state class
class Game_State {
private:
	static pthread_t apple_thread;
	static pthread_t input_thread;
	static pthread_t end_game_thread;
	BITMAP* buffer;
	FONT* game_font;
	SAMPLE* background_music;
	SAMPLE* crunch_sound;
	SAMPLE* game_over_sound;
	static Board* game_board;
	Snake* player;
	static bool game_over;
	static direction dir;
	static volatile int speed_counter;
	static volatile int timer;
	static int total_score;
public:
	Game_State();
	~Game_State();
	bool load_fonts();
	bool load_sounds();
	bool initialize_game();
	void start_game();
	void new_game();
	void reset_game();
	void run_game();
	bool main_menu();
	Cell* get_next_cell(Cell* curr_position);
	bool is_snake_out_of_bounds(int row, int col);
	void run_game_logic();
	bool play_game();
	void draw_game_board();
	void draw_snake();
	void draw_snake_face(int x_pos, int y_pos);
	void draw_face_left(int x_pos, int y_pos);
	void draw_face_right(int x_pos, int y_pos);
	void draw_face_up(int x_pos, int y_pos);
	void draw_face_down(int x_pos, int y_pos);
	void draw_apple();
	void end_game_menu();
	void update_screen();
	static void increment_speed_counter();
	static pthread_t create_pthread(void* (*thread_function) (void*), void* param);
	static bool is_apple_in_board();
	static void* spawn_apple(void* args);
	static void* handle_keyboard_input(void* args);
	static void* end_game(void* args);
};

#endif