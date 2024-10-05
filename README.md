File Overview
snakes.h: Header file defining the Snakes class and all related functions.
snakes.cpp: Implementation of the Snakes class, including the logic for creating the board, moving players, and managing snakes and ladders.
test.cpp: Contains unit tests to verify game functionality, including deep copying, assignment operator, and valid/invalid moves.
How the Game Works
Board Initialization: The game creates a board of a given size with randomly placed snakes and ladders.
Player Turns: Two players take turns rolling a dice. Players move forward according to the dice roll.
Snakes and Ladders: If a player lands on the head of a snake, they are moved down to the snake’s tail. If a player lands on the bottom of a ladder, they are moved to the top.
Winning Condition: The first player to reach the last square of the board wins the game.
Example Gameplay
Board Setup: A 5x5 board is created with randomly placed snakes and ladders.
Players' Turns: Player 1 and Player 2 take turns rolling the dice, moving across the board.
Interacting with Snakes and Ladders: Landing on a snake sends a player back, while landing on a ladder moves them forward.
