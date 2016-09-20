#ifndef KING_CPP
#define KING_CPP

#include <string>
#include "Unit.h"
#include "King.h"
#include "Board.h"
#include "Block.h"


 King::King(int row, int col, bool isWhite){

	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;

	 this->name = (isWhite)?"W":"B";

	 this->name += "K";
 }

 King::King(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WK";
 }


 std::vector <int> King::canMove(){
	 int arrays[16]= { -1,-1,   -1, 0,   -1, 1,   0, 1,   1,1,   1, 0,   1, -1,   0, -1 };
	 Block** board = Board::block;
	 std::vector <int> movement;
	 
	 board[row][col].setItHasUnit(false);//remove from board to check movements

	 for (int i = 0; i < 16; i+=2){
		 int m = row + arrays[i];
		 int n = col + arrays[i + 1];

		 if (!this->isOutBounds(m, n)	 &&		!Board::beingAttacked(m, n)		 &&		(!board[m][n].ithasUnit()	 ||		this->isWhite != board[m][n].getUnit()->isItWhite())){
			 
			 movement.push_back(m);
			 movement.push_back(n);
		 
		 }
	}

	board[row][col].setItHasUnit(true); //put unit back in the baord
	return movement;
 }

#endif