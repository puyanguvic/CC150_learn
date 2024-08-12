#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 3

// Function to check if a player has won
bool checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    int i, j;
    
    // Check rows
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    
    // Check columns
    for (j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return true;
        }
    }
    
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    
    return false;
}

// Function to print the board
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'O', 'O', 'X'}
    };
    
    printf("Current board:\n");
    printBoard(board);
    
    if (checkWin(board, 'X')) {
        printf("Player X has won!\n");
    } else if (checkWin(board, 'O')) {
        printf("Player O has won!\n");
    } else {
        printf("No winner yet.\n");
    }
    
    return 0;
}