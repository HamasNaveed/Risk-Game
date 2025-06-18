Risk Game
🎲 A 2D strategy board game inspired by Risk, built in C++ using OpenGL (GLUT). Players (2–6) compete to conquer 132 territories by assigning troops, attacking adjacent territories, and managing positions. Features a high score system and interactive menu. Created by Hamas Naveed for SE (A), Roll No: 23I-3014.
Table of Contents

Features
Demo
Installation
How to Play
Technologies Used

Features

Territory Management: 132 territories displayed as a 12x11 grid, colored by player ownership.
Player Setup: 2–6 players enter names and choose colors (Red, White, Purple, Orange, Blue, Yellow).
Troop System: Assign 80 troops (Infantry: 3 troops, Cannon: 5 troops) to owned territories.
Turn-Based Gameplay: Players take turns to attack, move troops, or pass, starting with the highest dice roll.
Attack Mechanics: Attack adjacent territories with dice-based outcomes; winners gain territories and random troop cards (0–10 troops).
Position Tracking: Each player has a position on their territory, updated if lost during attacks.
High Scores: Tracks and displays top scores in highscores.txt based on territories owned.
Interactive Menu: Adjust player count (+/-), view high scores (!), and input names (uppercase letters).

Demo

Installation
To run the game on Windows:
Installation might not be correct as i also had a hard time setting up the game SO BEST OF LUCK!!!




Install dependencies:
Install a C++ compiler (e.g., MinGW or MSYS2).
Install OpenGL/GLUT:
For MinGW: Download freeglut and add to your compiler’s include/lib paths.
Example (MSYS2):pacman -S mingw-w64-x86_64-freeglut






Compile the game:
Assuming your main file is Risk.cpp, compile with:g++ Risk.cpp -o Risk -lglut -lGL -lGLU




Run the game:  Risk.exe



How to Play

Menu:
Press +/- to set 2–6 players.
Press ! to view high scores.
Enter uppercase letters to input player names and choose colors (1–6).
Press Enter to start when all names are entered.


Gameplay:
Territory Selection: Click territories (brown squares) to claim them in turn order.
Troop Assignment: Select Infantry (3 troops) or Cannon (5 troops) for your 80 troops.
Position Selection: Click an owned territory to set your starting position.
Troop Placement: Click owned territories to place troops.
Turns: Choose to:
Attack: Click an adjacent enemy territory; dice determine win/loss.
Move: Select troops and click an owned territory to reposition.
Pass: End turn.


Game ends when a player controls 132+ territories; high score is updated.


Controls:
Mouse: Click to select territories or place troops.
Keyboard: Menu inputs (+, -, !, uppercase letters, Enter).



Technologies Used

C++: Core programming language.
OpenGL (GLUT): Renders 2D game board, territories, and UI elements.
File I/O: Stores high scores in highscores.txt.


🌍 Conquer territories and dominate in this strategic Risk game! Feedback is welcome. 🎮
