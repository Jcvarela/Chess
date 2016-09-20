#ifndef BOARD_H
#define BOARD_H


#include "Unit.h"
#include "Block.h"
#include <vector>
#include <string>

class Board{

public:
	static Block **block;
	static bool playerOneTurn;
	
	//keeps track of the position of the kings
	static int wKing[], bKing[];
	
	//constructor
	Board();

		//_ _ _ _ _ _ _
		//option, rowF, colF, rowT, colT , name 
		//option 1 -> move
		//option 2 -> eat need extra name at the end
		//option 3 -> Castling
		//option 4 -> peon gets promoted
	static std::vector<std::string> history; 


	//Prints the board
	std::string getBoard();						

	//move unit from (frow,fcol) to (trow,tcol) 
	static bool moveTo(int frow,int fcol, int trow,int  tcol);
	//check if unit at (row2,col2) can attack (row,col)
	static bool piecesWhat(int row, int col, int row2, int col2);
	

	//check if position at (m,n) is been attack by enemy units
	static bool beingAttacked(int row, int col);

	//retrunsthe last 5 movement maid in the game
	static std::string printHistory();
	// add to history
	static void addHistory(int frow, int fcol, int trow, int  tcol);
	//goes back
	// true -> if it can go back 
	// false -> history is empty
	static  bool goback();

	//check if your king is on check 
	static bool isYourKingBeenAttack();
	
};

#endif