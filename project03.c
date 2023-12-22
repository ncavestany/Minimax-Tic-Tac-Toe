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

bool checkXWin(board_t board, char player1) { // Checks if X has won. Returns false if not.
	if (checkRow(board, player1) || checkColumn(board, player1) || checkDiagonal(board, player1)) {
		return true;
	}
	return false;
}

bool checkOWin(board_t board, char player2) { // Checks if O has won. Returns false if not.
	if (checkRow(board, player2) || checkColumn(board, player2) || checkDiagonal(board, player2)) {
		return true;
	}
	return false;
}

bool checkDraw(board_t board) { // Checks if the board is full and neither of the other players have won.
	if ((checkXWin(board, 'X') == false || checkOWin(board, 'O') == false) && isFull(board)) {
	    return true;
	}
	return false;
}

bool checkBest(int score, int best, char player) {
	if (player == 'X') {
		return score > best; // If the player is X, then check if score is greater than current best.
	}
	else {
		return score < best; // If the player is O, check if score is less than best.
	}
	// If this function returns true, then the running best is updated.
}


int minimax(board_t board, char player, int depth) {
	int score;
	int row;
	int col;
	if (checkXWin(board, 'X')) {
		score = 10 - depth;
		return score;
	}
	if (checkOWin(board, 'O')) {
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
	int best = 10;
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
					
				}
			}
		}		
	}
}

bool terminal_state(board_t board) { // If the board is at an ending point (victory or draw), return true and display the result..
	if (checkXWin(board, 'X')) {
		printf("X wins.\n");
		return true;
	}
	else if (checkOWin(board, 'O')) {
		printf("O wins.\n");
		return true;
	}
	else if (checkDraw(board)){
		printf("Draw\n");
		return true;
	}
	else {
		return false;
	}
}


int main(int argc, char **argv) {
    char playAgain;
    printf("Welcome to the Minimax Tic-Tac-Toe Game!\n");
    do {
    	if (playAgain == 'y') { // Reset board input if there was any.
    		argc = 1;
    	}
        board_t board;
        initializeBoard(board);
        int i = 1; // The current index of the user input.
        int row;
        int col;

        if (argc == 1) {
        	printf("Enter your first move. (Column #, Row #) \n");
            while (!terminal_state(board)) { // Run until the board is not in a state of victory or draw.
                printf("X: ");
                fscanf(stdin, "%d %d", &row, &col);
                if (board[row][col] == '_') {
                    board[row][col] = 'X';
                    if (terminal_state(board)) {
                        break;
                    }
                    printBoard(board);
                    find_best_move(board, 'O', &row, &col);
                    board[row][col] = 'O';
                    printf("O: %d %d\n", row, col);
                    printBoard(board);
                } else {
                    printf("Illegal move\n");
                }
            }
        } else {    // Populating the board based on user input if there are any arguments.
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

        printf("Would you like to play again? Enter 'y' if yes or 'n' if no: ");
        scanf(" %c", &playAgain); // Note the space before %c to consume any previous newline character.

    } while (playAgain == 'y');

    printf("Thank you for playing! \n");
    return 0;
}