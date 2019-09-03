#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "connectnGameLogic.h"

//Creates board and returns a char array pointer
char** CreateBoard(InputVals boardInfo) {
   // initializes the board to hold the proper number of rows
   char **connectBoard = (char**)malloc(boardInfo.numRows * sizeof(char*));

   // for each row, allocates memory for the proper number of columns
   for (int i = 0; i < boardInfo.numRows; i++) {
      connectBoard[i] = (char*)malloc(boardInfo.numCols * sizeof(char));
   }

   // initializes each space on the board to an asterisk
   for (int row = 0; row < boardInfo.numRows; row++){
      for (int col = 0; col < boardInfo.numCols; col++) {
         connectBoard[row][col] = '*';
      }
   }

   return connectBoard;
}

//Display the current board
void DisplayBoard(char** board, InputVals boardInfo) {

   // prints rows starting from the top down
   for (int row = 0; row < boardInfo.numRows; row++) {
      printf("%d ", boardInfo.numRows - 1 - row);
      for (int col = 0; col < boardInfo.numCols; col++) {
         printf("%c ", board[boardInfo.numRows - 1 - row][col]);
      }
      printf("\n");
   }
   printf("  "); //aligns the column numbers

   // prints the column numbers
   for (int col = 0; col < boardInfo.numCols; col++) {
      printf("%d ", col);
   }
   printf("\n");
}

// asks for user input and returns a struct representing the player move
move RequestMove(char player, char** board, InputVals boardInfo) {
   move currentMove;
   currentMove.player = player;
   //prompt the user for input
   do {
      printf("Enter a column between 0 and %d to play in: ", (boardInfo.numCols - 1));
      scanf("%d", &currentMove.col);
   } while (!IsValidMove(currentMove.col, board, boardInfo));
   return currentMove;
}

// returns true if the column choice is playable
bool IsValidMove(int col, char** board, InputVals boardInfo) {
   bool isValid = true;

   // if the player choice is outside the column range, return false
   if (col < 0 || col >= boardInfo.numCols) {
      return false;
   }

   // if the top row is not empty, return false
   if (board[boardInfo.numRows - 1][col] != '*') {
      isValid = false;
   }
   return isValid;
}

// changes the board to place the piece in the correct position
char** MakeMove(move currentMove, char** board, InputVals boardInfo) {

   // if bottom row is empty, place piece there
   if (board[0][currentMove.col] == '*') {
      board[0][currentMove.col] = currentMove.player;
      return board;
   }

   // seeks the lowest position to place token
   for (int row = boardInfo.numRows - 1; row >= 0; row--) {
      if (board[row][currentMove.col] != '*') {
         board[row + 1][currentMove.col] = currentMove.player;
         return board;
      }
   }
   return board;
}

// prints win message based on who played the last turn
void DisplayWin(int moveNumber) {
   if (moveNumber % 2) {
      printf("Player 1 Won!\n");
   }
   else {
      printf("Player 2 Won!\n");
   }
}

// returns true if a winning move has been played
bool HasWon(int numMoves, char** board, InputVals boardInfo) {
   //check for win conditions
   bool win;

   // checks every possible type of win
   win = (VertWin(numMoves, board, boardInfo) || HorizWin(numMoves, board, boardInfo) || PosDiagWin(numMoves, board, boardInfo) || NegDiagWin(numMoves, board, boardInfo));
   
   // if there are no winning moves played and the board is full, display tie message
   if (numMoves == boardInfo.numRows * boardInfo.numCols - 1) {
      printf("Tie game!\n");
      exit(0);
   }
   return win;
}

// returns true if a vertical win has occurred
bool VertWin(int numMoves, char** board, InputVals boardInfo) {
   char player = (numMoves % 2 == 0)? 'X' : 'O';
   bool win = false;

   // iterates through every position on the board
   for (int row = 0; row < boardInfo.numRows; row++) {
      for (int col = 0; col < boardInfo.numCols; col++) {

         // if the current player has a piece there...
         if (board[row][col] == player) {
            int numInARow = 0;
            // checks spaces above for a win condition
            for (int i = 0; i < boardInfo.numToWin; i++) {
               if ((row + i) >= boardInfo.numRows ) {
                  continue;
               }
               if (board[row + i][col] == player) {
                  numInARow++;
               }
            }
            if (numInARow == boardInfo.numToWin) {
               win = true;
            }
         }
      }
    }
   return win;
 }

// returns true if a horizontal win has occurred
bool HorizWin(int numMoves, char** board, InputVals boardInfo) {
   char player = (numMoves % 2 == 0)? 'X' : 'O';
   bool win = false;

   // iterates through every position on the board
   for (int row = 0; row < boardInfo.numRows; row++) {
      for (int col = 0; col < boardInfo.numCols; col++) {

         // if the current player has a piece there...
         if (board[row][col] == player) {
            int numInARow = 0;
            // checks spaces to the right for a win condition
            for (int i = 0; i < boardInfo.numToWin; i++) {
               if ((col + i) >= boardInfo.numCols) {
                  continue;
               }
               if (board[row][col + i] == player) {
                  numInARow++;
               }
            }
            if (numInARow == boardInfo.numToWin) {
               win = true;
            }
         }
      }
    }
   return win;
}

// returns true if a positive diagonal win has occurred 
bool PosDiagWin(int numMoves, char** board, InputVals boardInfo) {
   char player = (numMoves % 2 == 0)? 'X' : 'O';
   bool win = false;

   // iterates through every position on the board
   for (int row = 0; row < (boardInfo.numRows - boardInfo.numToWin); row++) {
      for (int col = 0; col < (boardInfo.numCols - boardInfo.numToWin); col++) {

         // if the current player has a piece there...
         if (board[row][col] == player) {
            // checks spaces above and to the right for a win condition
            int numInARow = 0;
            for (int i = 0; i < boardInfo.numToWin; i++) {
               if ((row + i) > boardInfo.numRows || (col + i) > boardInfo.numCols) {
                  continue;
               }
               if (board[row + i][col + i] == player) {
                  numInARow++;
               }
            }
            if (numInARow == boardInfo.numToWin) {
               win = true;
            }
         }
      }
    }
   return win;
}

// returns true if a negative diagonal win has occurred 
bool NegDiagWin(int numMoves, char** board, InputVals boardInfo) {
   char player = (numMoves % 2 == 0)? 'X' : 'O';
   bool win = false;

   // iterates through every position on the board
   for (int row = boardInfo.numRows - 1; row >= boardInfo.numToWin - 1; row--) {
      for (int col = 0; col < boardInfo.numCols; col++) {

         // if the current player has a piece there...
         if (board[row][col] == player) {
            // checks spaces below and to the right for a win condition
            int numInARow = 0;
            for (int i = 0; i < boardInfo.numToWin; i++) {
               if ((row - i) < 0 || (col + i) > boardInfo.numCols) {
                  continue;
               }
               if (board[row - i][col + i] == player) {
                  numInARow++;
               }
            }
            if (numInARow == boardInfo.numToWin) {
               win = true;
            }
         }
      }
    }
   return win;
}