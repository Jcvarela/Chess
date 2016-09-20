#ifndef BOARD_H
#define BOARD_H


#include "Unit.h"
#include "Block.h"
#include <vector>
#include <string>

class Board{

public:
	//keeps track of the 64 block in the board game
	static Block **block;

	//true if its whites turn
 	//false if its black turn
	static bool playerOneTurn;
	
	//keeps track of the position of the kings
	static int wKing[], bKing[]; // {row,col,movement}
	//keeps track of rooks position and how many time they mvoe
	static int white_left_rook[], white_right_rook[];
	static int black_left_rook[], black_right_rook[];


	
	//constructor
	Board();







		//_ _ _ _ _ _ _
		//option, rowF, colF, rowT, colT , name 
		//option 1 -> move												-> size = 7
		//option 2 -> eat, add extra name of who got eaten				-> size = 9
		//option 3 -> Castling											-> size = 7
		//option 4 -> Promotion, extra name								-> size = 9								
		//option 5 -> En passant, add extra name and its position		-> size = 11
	static std::vector<std::string> history; 


	//Prints the board
	std::string getBoard();						

	//move unit from (frow,fcol) to (trow,tcol) 
	static bool moveTo(int frow,int fcol, int trow,int  tcol);

	//check if unit at (row2,col2) can attack (row,col)
	static bool piecesWhat(int row, int col, int row2, int col2);
	

	//check if position at (m,n) is been attack by enemy units
	static bool beingAttacked(int row, int col);

	//retrunsthe the last 5 movement maid in the game
	static std::string printHistory();

	// add to history
	static void addHistory(int frow, int fcol, int trow, int  tcol);
	
	//goes back
	// true -> if it can go back 
	// false -> history is empty
	static  bool goback();

	//true your king is udner attack
	//false false your king is not under attack
	static bool isYourKingBeenAttack();

	// true if your king has move
	// false if your king hasen't move
	static bool yourKingMove();

	// true if rook at specific position move
	// false otherwise
	static bool rook_at_pos_move(int row,int col);


	// check if a unit can move to position with out king been in check
	// return true if you can move 
	// return false if king is under attack or u cant move there 
	static bool checkIfUnitCanMove(int row, int col);
	

	//return true if player at this turn can make at least one movement
	//return false if player at this turn cant make anymovements meaning tie or checkmate
	static bool checkIfPlayerHaveMovement();


	//peopn gets promoted && and add to history
	static void setPromotion(std::string name);

	//static void print();
};

#endif