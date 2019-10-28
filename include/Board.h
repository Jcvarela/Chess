#ifndef BOARD_H
#define BOARD_H

#include "Unit.h"
#include "Block.h"
#include <vector>
#include <string>

class Board{
	public:
		//Keeps track of the 64 blocks in the board game
		static Block **block;
		//Keeps track what player is playing right now
		static bool playerOneTurn;
		//keeps track of the position of the kings
		static int wKing[], // {row,col, how many time it move}
					bKing[];
		//keeps track of rooks position and how many time they mvoe
		static int white_left_rook[], white_right_rook[];
		static int black_left_rook[], black_right_rook[];
		//Code to keep track of the history by string, so the players can see all the moves and be able to go back
		//History values will be saved as a string code, the first character will define what action was taken
		//		each action will have a different format,
		//
		//	Action_number | row_from | col_from | row_to | col_to | extra_name | extra_pos
		//	Action 1 -> moveTo																						-> size = 7
		//	Action 2 -> eat unit, use value "extra_name" for eaten unit 	-> size = 9
		//	Action 3 -> Castling																					-> size = 7
		//	Action 4 -> Promotion, "extra_name" picked unit								-> size = 9
		//	Action 5 -> En passant, "extra_name" for eaten unit					-> size = 11
		//											 & "extra_pos" to know units positin
		//
		//eg 10203WK -> 1 means: Unit move from (0,2) to (0,3) and it was the white king
		static std::vector<std::string> history;

		Board();

		//Set the board to its default value
		static void InitializeBoard();
		//Move unit from (frow,fcol) to (trow,tcol)
		static bool moveTo(int frow,int fcol, int trow,int  tcol);
		//Check if unit at (row2,col2) can attack (row,col)
		static bool piecesWhat(int row, int col, int row2, int col2);
		//Check if the position at (m,n) is been attacked by any enemy units
		static bool beingAttacked(int row, int col);
		//Returns the last 5 movements made in the game
		static std::string printHistory();
		//Add to history
		static void addHistory(int frow, int fcol, int trow, int  tcol);
		//Check if it can move back
		static  bool goback();
		static bool isYourKingBeenAttack();
		//Check if the king can move
		static bool yourKingMove();
		//Return true if rook at specific position move
		static bool rook_at_pos_move(int row,int col);
		//Check if a unit can move to position without king been in check
		static bool checkIfUnitCanMove(int row, int col);
		//Return false if the player at this turn can't make any movements, or its a  tie or checkmate
		static bool checkIfPlayerHaveMovement();
		//Pawn gets promoted
		static void setPromotion(std::string name);
		//Returns the board as a string so it can be printed in the console
		std::string getBoard();
};

#endif
