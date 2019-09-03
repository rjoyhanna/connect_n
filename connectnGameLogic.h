#ifndef CONNECTNGAMELOGIC_H
#define CONNECTNGAMELOGIC_H

   // used for holding the input values
   typedef struct InputVals_STRUCT{
      int numRows;
      int numCols;
      int numToWin;
   } InputVals;

   // used for holding the player move information 
   typedef struct MOVE_Struct {
      char player;
      int col;
   } move;

   // creates and returns an array representing the game board
   char** CreateBoard(InputVals boardInfo);

   //  prints board row by row
   void DisplayBoard(char** board, InputVals boardInfo);

   // asks for user input and returns a struct representing the player move
   move RequestMove(char player, char** board, InputVals boardInfo);

   // returns true if the column choice is playable
   bool IsValidMove(int col, char** board, InputVals boardInfo);

   // changes the board to place the piece in the correct position
   char** MakeMove(move currentMove, char** board, InputVals boardInfo);

   // prints win message based on who played the last turn
   void DisplayWin(int moveNumber);

   // returns true if a winning move has been played
   bool HasWon(int numMoves, char** board, InputVals boardInfo);
   
   // returns true if a vertical win has occurred
   bool VertWin(int numMoves, char** board, InputVals boardInfo);

   // returns true if a horizontal win has occurred
   bool HorizWin(int numMoves, char** board, InputVals boardInfo);

   // returns true if a positive diagonal win has occurred 
   bool PosDiagWin(int numMoves, char** board, InputVals boardInfo);

   // returns true if a negative diagonal win has occurred 
   bool NegDiagWin(int numMoves, char** board, InputVals boardInfo);

#endif