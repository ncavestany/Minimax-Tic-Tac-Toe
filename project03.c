#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>  

typedef char board_t[3][3];

void printBoard(board_t board) { // Prints the board with proper formatting.
	int row;
	int col;
	for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            if (col != 2) {
            	printf(" %c |", board[row][col]);
            }
            else {
            	printf(" %c \n", board[row][col]);
            }
    	}
    	if (row != 2) {
			printf("---+---+---\n");
		 }
    
	}
}

bool ifEmpty(board_t board) { // Checks if the board is completely empty, returns true if it is.
	int row = 0;
	int col = 0;

	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			if (board[row][col] == '_') {
				continue;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

bool isFull(board_t board) { // Checks if the board is completely populated, returns true if it is.. (Empty and partially populated do not mean full.)
	int row = 0;
	int col = 0;
	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			if (board[row][col] == '_') {
				return false;
			}
		}
	}
	return true;
}

bool checkRow(board_t board, char player) { // Check each row and see if any row has all identical characters. If so, return true and indicate which icon that is.
	int row;
	for (row = 0; row < 3; row++) {
		if (board[row][0] == player  && board[row][1] == player &&  board[row][2] == player) {
			printf("%c wins\n", player);
			return true;
		}
	}
	return false;
}

bool checkColumn(board_t board, char player) { // Scan through each column to check for a victory. 
	int column;
	for (column = 0; column < 3; column++) {
		if (board[0][column] == player && board[1][column] == player &&  board[2][column] == player) {
			printf("%c wins\n", player);
			return true;	
		}	
	}
	return false;
}

bool checkDiagonal(board_t board, char player) {
	if (board[0][0] == player && board[1][1] == player && board[2][2] == player) { // Check diagonal right (top left to bottom right) victory		
		printf("%c wins\n", player);
		return true;
	}
	else if (board[0][2] == player && board[1][1] == player && board[2][0] == player) { // Check diagonal left
			printf("%c wins\n", player);
			return true;
	}
	return false;
}

bool checkXWin(board_t board, char player1) {
	if (checkRow(board, player1) || checkColumn(board, player1) || checkDiagonal(board, player1)) {
		return true;
	}
	return false;
}

bool checkOWin(board_t board, char player2) {
	if (checkRow(board, player2) || checkColumn(board, player2) || checkDiagonal(board, player2)) {
		return true;
	}
	return false;
}


int main(int argc, char **argv) {
    if (argc != 10) {
        printf("invalid args\n");
        exit(-1);
    }

    board_t board;

    int i = 1; // The current index of the user input.
    int row;
    int col;
    char player1 = 'X';
    char player2 = 'O';
    
	// Populating the board based on user input.
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            board[row][col] = argv[i][0];
            i++;
        }
    }

    printBoard(board);
    if (ifEmpty(board)) {
    	exit(0);
    }

	
    if ((checkXWin(board, player1) == false || checkOWin(board, player2) == false) && isFull(board)) {
    	printf("draw\n");
    }
  	
    
    return 0;
}
