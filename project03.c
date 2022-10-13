#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  
#include <sys/param.h>

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

void initializeBoard(board_t board) { // Fills the entire board with '_' characters.
	int row;
	int col;
	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			board[row][col] = '_';
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
			return true;
		}
	}
	return false;
}

bool checkColumn(board_t board, char player) { // Scan through each column to check for a victory. 
	int column;
	for (column = 0; column < 3; column++) {
		if (board[0][column] == player && board[1][column] == player &&  board[2][column] == player) {
			return true;	
		}	
	}
	return false;
}

bool checkDiagonal(board_t board, char player) {
	if (board[0][0] == player && board[1][1] == player && board[2][2] == player) { // Check diagonal right (top left to bottom right) victory				
		return true;
	}
	else if (board[0][2] == player && board[1][1] == player && board[2][0] == player) { // Check diagonal left
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

bool checkDraw(board_t board) {
	if ((checkXWin(board, 'X') == false || checkOWin(board, 'O') == false) && isFull(board)) {
	    return true;
	}
	return false;
}

bool checkBest(int score, int best, char player) {
	if (player == 'X') {
		return score < best; // If the player is X, then check if score is less than current best.
	}
	else {
		return score > best; // If the player is O, check if score is greater than best.
	}
	// If this function returns true, then the running best is updated.
}


int minimax(board_t board, char player, int depth) {
	int score;
	int row;
	int col;
	if (checkXWin(board, player)) {
		score = 10 - depth;
		return score;
	}
	if (checkOWin(board, player)) {
		score = (-10) + depth;
		return score;
	}
	if (checkDraw(board)) {
		score = 0;
		return score;
	}

	if (player == 'X') {
		score = -1000;
		for (row = 0; row < 3; row++) {
			 for (col = 0; col < 3; col++) {
		        if (board[row][col] == '_') {
		        	board[row][col] = player; // make move
		        	score = MAX(score, minimax(board, 'O', depth + 1)); // Returns the highest score
		        	board[row][col] = '_'; //unmake move
		        }
		  }
		}
	}
	else {
		score = 1000;
		for (row = 0; row < 3; row++) {
			for (col = 0; col < 3; col++) {
				if (board[row][col] == '_') {
					board[row][col] = player; // make move
					score = MIN(score, minimax(board, 'X', depth + 1)); // Returns the lowest score
					board[row][col] = '_'; // unmake move
				}
			}
		}
	}
	return score;
}

void find_best_move(board_t board, char player, int *pr, int *pc) {
	int score;
	int best = 0;
	int row;
	int col;
			
	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			if (board[row][col] == '_') {
				board[row][col] = player; // Trial move
				if (player == 'X') { // If the current player is X, run the trial moves for O (and vice versa).
					score = minimax(board, 'O', 0);
				} 
				else {
					score = minimax(board, 'X', 0);
				}
				board[row][col] = '_'; // Undo the move.
				if (checkBest(score, best, player)) { // Update the current best score and best move.
					best = score;
					*pr = row;
					*pc = col;
					printf("Best score for %d, %d is %d\n", row, col, score);
				}
			}
		}		
	}
}

bool terminal_state(board_t board) { // If the board is at an ending point (victory or draw), return true.
	if (checkXWin(board, 'X') || checkOWin(board, 'O') || checkDraw(board)) {
		return true;
	}
	else {
		return false;
	}
}


int main(int argc, char **argv) {
    board_t board;
    initializeBoard(board);
    int i = 1; // The current index of the user input.
    int row;
    int col;

    
	if (argc == 1) {
		while(!terminal_state(board)) {
			printf("X: ");
			fscanf(stdin, "%d %d", &row, &col);
			if (board[row][col] != 'X' || board[row][col] != 'O') {
				board[row][col] = 'X';
				if (terminal_state(board)) {
					break;
				}
				find_best_move(board, 'O', &row, &col);
				board[row][col] = 'O';
				printf("O: %d %d\n", row, col);
			}
			else {
				printf("Illegal move\n");
			}
		}
		
	}  
	else {	// Populating the board based on user input if there are any arguments.
		for (row = 0; row < 3; row++) {
			 for (col = 0; col < 3; col++) {
		        board[row][col] = argv[i][0];
		        i++;
		   }
		}
		row = 0;
		col = 0;
		printBoard(board);
		find_best_move(board, 'O', &row, &col);
		printf("O: %d %d\n", row, col);
	}
		
    return 0;
}
