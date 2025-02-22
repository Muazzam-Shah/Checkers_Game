# Checkers Game in C++

## Overview
This project is a simple implementation of the classic **Checkers** game using C++. The game is played on an 8x8 board with two players (Player 1 and Player 2). Each player moves their pieces diagonally, and pieces that reach the opposite side are promoted to kings, allowing them to move both forward and backward.

## Features
- **Board Representation**: The game board is represented as an 8x8 grid.
- **Player Pieces**:
  - Player 1: Represented by `r` (regular piece) and `R` (king piece).
  - Player 2: Represented by `w` (regular piece) and `W` (king piece).
- **Move Validation**:
  - Simple moves (diagonal movement for regular pieces).
  - Jump moves (capturing opponent pieces by jumping over them).
  - King movement (allows movement in both directions).
- **Piece Promotion**: Regular pieces are promoted to kings when they reach the last row.
- **Win Detection**: The game ends when a player has no remaining pieces, declaring the opponent as the winner.
- **Console-based Interaction**: The game is played through a terminal, prompting users for moves.

## How to Run
### Prerequisites
- A C++ compiler (e.g., `g++` for GCC)

### Compilation
To compile the program, run the following command in your terminal:
```sh
 g++ -o checkers checkers.cpp
```

### Running the Game
After compilation, execute the following command:
```sh
 ./checkers
```

## How to Play
- Players take turns entering their moves in the format:
  ```
  Enter current position (row column): x y
  Enter destination position (row column): x y
  ```
- The game validates the moves and updates the board.
- Players can perform simple moves or jump moves (captures).
- If a piece reaches the opposite side, it is promoted to a king.
- The game continues until one player has no remaining pieces.

## Example Output
```
***CHECKERS GAME***
A capital letter represents a king piece.
Rows and columns are 0-indexed.

   0 1 2 3 4 5 6 7
0  - r - r - r - r 0
1  r - r - r - r - 1
2  - r - r - r - r 2
3  - - - - - - - - 3
4  - - - - - - - - 4
5  w - w - w - w - 5
6  - w - w - w - w 6
7  w - w - w - w - 7
   0 1 2 3 4 5 6 7

Player 1's turn.
Enter current position (row column): 2 1
Enter destination position (row column): 3 2
```

## Future Improvements
- Implement a graphical user interface (GUI).
- Add AI for single-player mode.
- Allow multi-jump moves in one turn.
