#ifndef QUEEN_CPP
#define QUEEN_CPP

#include <string>
#include "Unit.h"
#include "Queen.h"
#include "Block.h"
#include "Board.h"

using namespace std;

Queen::Queen(int row, int col, bool isWhite){

	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "Q";
 }

 Queen::Queen(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WQ";
 }

 vector<int> Queen::canMove(){
	 bool continues = true;
	 int A[16] = {1,1,  1,0,  1,-1,  0,-1,  -1,-1,  -1,0,  -1,1,  0,1};

	 vector<int> movement;				//This vector contains an even number of values, pairing values for every posible move the Rook can move

	 Block** board = Board::block;		//We are creating a 2d array of Block pointers, to asign the static value of our board (WE are getting the value of [Block** block] in class Board and asigning it to our board) 

	 for (int i = 0; i < 16; i += 2){
		 for (int j = 1; j <= 7; j++){

			 int m = A[i] * j + row;
			 int n = A[i + 1] * j + col;

			 if (continues && !this->isOutBounds(m, n) && (hasEnemy(&board[m][n]) || !board[m][n].ithasUnit())){

				 if (hasEnemy(&board[m][n]))			
					 continues = false;
				 movement.push_back(m);
				 movement.push_back(n);
			 }
			 else continues = false;
		 }
		 continues = true;
	 }

	 return movement;
 }

 //This function checks if a block has an enemy unit
 bool Queen::hasEnemy(Block *b){

	 if (!b->ithasUnit())		//If no unit is found in the block return false
		 return false;
	 else if (this->isWhite == (b->getUnit()->isItWhite()))	//If the unit found is the same color return false
		 return false;
	 else							//If the unit found is enemy return true
		 return true;

 }

#endif