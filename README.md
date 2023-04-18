# MultithreadedSnake

This repository consists of the code that was used to create a multi-threaded snake game. 
In the snake game, a player controls the snake's head, and must move it using the up, down, left and right arrow keys. If the snake's 
head collides with any part of the snake's body, or the borders of the game board, the game is over. The snake grows by eating an apple
that randomly spawns in some position of the board.

## Gameplay (x4 speedup)
https://user-images.githubusercontent.com/92893114/232644836-76db4140-bb54-4749-aa9a-d27cf813c6af.mp4

## Language & Libraries
- Made with C/C++
- Includes the Allegro 4.4.2 library (a game library for C/C++ programming and includes DirectX and OpenGL to support it)
- Includes the Pthreads library for Windows

## Multithreaded Aspects
- Spawning the apple in a random location
- Handling keyboard input
- Ending the game abruptly when the ESC key is pressed
- The main thread (includes the game loop in the play_game() method)

## Attribution
- Background music provided by Pixabay: https://pixabay.com/music/video-games-chiptune-grooving-142242/
- Apple crunch sound by Koops: https://freesound.org/s/20279/
- End game sound provided by Pixabay: https://pixabay.com/sound-effects/videogame-death-sound-43894/
