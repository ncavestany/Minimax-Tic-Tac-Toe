# Tic-Tac-Toe with Minimax Algorithm

This is a simple command-line implementation of Tic-Tac-Toe with an opponent using the Minimax algorithm. The game is written in C.

## Description

This project implements a Tic-Tac-Toe game where a human player can play against an AI opponent. The AI opponent uses the Minimax algorithm to make optimal moves and therefore never lose.

## Features

- Command-line interface for easy interaction.
- Human vs AI gameplay.
- Minimax algorithm for AI decision-making.
- Option to play multiple rounds.

## How to Play

1. If you are compiling and running the program manually:
   - Compile the source code using the provided Makefile: `make`
   - Run the executable: `./Minimax-Tac-Tac-Toe`

2. If you are providing initial board positions as command-line arguments:
   - Pass a string of 9 characters representing the initial board state (e.g., `X _ X O _ O _ _ _`).
   - The program will then display which move is ideal to win.

3. Follow the on-screen prompts to make your moves as 'X'. The AI opponent ('O') will respond with optimal moves.

4. After the game ends, you will be asked if you want to play again. Enter 'y' for yes or 'n' for no.

## Requirements

- C compiler (e.g., GCC)

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/ncavestany/Minimax-Tic-Tac-Toe.git
    cd Minimax-Tac-Tac-Toe
    ```

2. Compile the source code using the provided Makefile:

    ```bash
    make
    ```

## Usage

- Run the executable:

    ```bash
    ./Minimax-Tac-Tac-Toe
    ```

- Follow the on-screen prompts to play the game.
