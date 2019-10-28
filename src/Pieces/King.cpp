#ifndef KING_CPP
#define KING_CPP

#include <string>
#include "Unit.h"
#include "King.h"
#include "Board.h"
#include "Block.h"


//constructor 
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

	 //checks all 8 possible mvoement
	 for (int i = 0; i < 16; i+=2){
		 int m = row + arrays[i];
		 int n = col + arrays[i + 1];

		 if (!this->isOutBounds(m, n)	 &&		!Board::beingAttacked(m, n)		 &&		(!board[m][n].ithasUnit()	 ||		this->isWhite != board[m][n].getUnit()->isItWhite())){
			 movement.push_back(m);
			 movement.push_back(n);
		 }
	}

	 int rowloc = (isWhite ? 7 : 0);


	//check if it can casteling
	 if (!Board::yourKingMove() && !Board::beingAttacked(row,col)){ // check if king hasent move and king is not been attack
		
		 if (!Board::rook_at_pos_move(rowloc, 0)){ //rook hase't move
			 //check if the 3 blocks at the left are empty and are not under attack... 3rd blokc has to be empty
			 if (!board[rowloc][col - 1].ithasUnit() && !Board::beingAttacked(rowloc, col - 1) && !board[rowloc][col - 2].ithasUnit() && !Board::beingAttacked(rowloc, col - 2) && !board[rowloc][col - 3].ithasUnit()){
				 movement.push_back(rowloc);
				 movement.push_back(col - 2);
			 }
		 }

		 if (!Board::rook_at_pos_move(rowloc, 7)){ //rook hase't move
			 //check if the 2 blocks at the right are empty and are not under attack
			 if (!board[rowloc][col + 1].ithasUnit() && !Board::beingAttacked(rowloc, col + 1) && !board[rowloc][col + 2].ithasUnit() && !Board::beingAttacked(rowloc, col  + 2)){
				 movement.push_back(rowloc);
				 movement.push_back(col + 2);
			 }
		 }

	 }


	board[row][col].setItHasUnit(true); //put unit back in the baord
	return movement;
 }


#endif