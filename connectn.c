#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "connectnGameLogic.h"

// displays usage error message 
void DisplayError();

// translates command line arguments into a structure of a type defined in the header file
InputVals ReadArgs(int numArgs, char *argArray[]);

int main(int argc, char *argv[]) {

   InputVals boardInfo = ReadArgs(argc, argv);
   char** connectBoard = CreateBoard(boardInfo);
   DisplayBoard(connectBoard, boardInfo);

   int moveNumber = 0; //stores number of moves
   bool win = false; // holds win condition
   do {
      move currentMove; // declares a struct of type move
      //switches players each turn
      if (moveNumber % 2 == 0) {
         currentMove = RequestMove('X', connectBoard, boardInfo);
      }
      else {
         currentMove = RequestMove('O', connectBoard, boardInfo);
      }

      // updates the board with a new move
      connectBoard = MakeMove(currentMove, connectBoard, boardInfo);

      //display board
      DisplayBoard(connectBoard, boardInfo);

      //check for win condition
      win = HasWon(moveNumber, connectBoard, boardInfo);

      moveNumber++;

   } while(!win);

   //display winning message
   DisplayWin(moveNumber);

   return 0;
}

//Displays usage information
void DisplayError() {
   printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
}

//Reads the command line arguments and returns a struct containing board info
InputVals ReadArgs(int numArgs, char *argArray[]) {
   //start by checking user inputs
   if (numArgs > 4) {
      printf("Too many arguments entered\n");
      DisplayError();
      exit(0);
   }
   else if (numArgs < 4) {
      printf("Not enough arguments entered\n");
      DisplayError();
      exit(0);
   }

   //declare InputVals variable to contain setup information
   InputVals boardInfo;
   //scan each user value into a corresponing int
   sscanf(argArray[1], "%d", &boardInfo.numRows);
   sscanf(argArray[2], "%d", &boardInfo.numCols);
   sscanf(argArray[3], "%d", &boardInfo.numToWin);

   return boardInfo;
}