RedmiGame

Welcome to RedmiGame, a classic snake game with a musical twist! 🐍🎵 Developed in C++ using SDL2, this game challenges you to guide the snake to eat musical notes while enjoying sound effects and a special Symphony Mode.

Game Overview

In RedmiGame, you control a snake that moves around the screen to eat musical notes. Each note you eat correctly increases your score, and eating a sequence of notes in the right order triggers the Symphony Mode, where you must collect 20 golden notes within a time limit to win. Be careful not to crash into the walls or the snake's own body, or the game will end!

Features





Classic Snake Gameplay: Control the snake using arrow keys to eat notes.



Musical Notes: Eat notes in the correct order to progress.



Symphony Mode: Collect 20 golden notes in 50 seconds to win the game.



Sound Effects: Enjoy sound effects for eating notes, failing, and completing sequences.



Visual Effects: Sparkle and eat effects add a fun visual flair.



Score System: Gain points for eating notes and completing sequences.

Installation

To play RedmiGame, you need to compile the source code on your machine. Follow these steps:

Prerequisites





C++ Compiler: g++ or any C++ compiler (e.g., MinGW for Windows, GCC for Linux/Mac).



SDL2 Libraries:





SDL2



SDL2_image



SDL2_ttf



SDL2_mixer



Install SDL2 on your system:





Ubuntu/Linux: sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev



Windows: Download SDL2 development libraries from libsdl.org and link them in your compiler.



macOS: Use Homebrew: brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer

Steps to Build and Run





Clone the repository:

git clone https://github.com/your-username/RedmiGame.git
cd RedmiGame



Compile the code:

g++ -o RedmiGame main.cpp PlayGround.cpp Snake.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer





If you're on Windows, you may need to specify the include and library paths, e.g.:

g++ -o RedmiGame main.cpp PlayGround.cpp Snake.cpp -I"path/to/SDL2/include" -L"path/to/SDL2/lib" -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer



Run the game:

./RedmiGame

How to Play





Controls:





Use the arrow keys to control the snake's direction (Up, Down, Left, Right).



Press Enter to play again after winning or losing.



Press Escape to quit the game.



Objective:





Eat the musical notes in the correct order to increase your score.



Complete a sequence of 5 notes to enter Symphony Mode.



In Symphony Mode, collect 20 golden notes within 50 seconds to win.



Game Over:





The game ends if the snake hits the walls or its own body.



In Symphony Mode, the game resets to normal mode if you fail to collect 20 golden notes in time.

Project Structure





main.cpp: Main game loop and initialization.



PlayGround.cpp/PlayGround.h: Manages the game board, notes, and game state.



Snake.cpp/Snake.h: Handles the snake's movement, collision, and note-eating logic.



Renderer.h: (Assumed) Renders the game using SDL2.



AudioManager.h: (Assumed) Manages sound effects.



EffectManager.h: (Assumed) Manages visual effects.

Screenshots

(TODO: Add screenshots of the game here to showcase gameplay.)

Contributing

Feel free to fork this repository, make improvements, and submit pull requests! If you find any bugs or have suggestions, please open an issue.

License

This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments





Inspired by classic snake games.



Thanks to the SDL2 community for providing awesome libraries for game development.
