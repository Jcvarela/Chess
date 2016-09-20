#ifndef KNIGHT_CPP
#define KNIGHT_CPP


#include <string>
#include <vector>
#include "Unit.h"
#include "Knight.h"
#include "Board.h"

#include <iostream>

Knight::Knight(int row, int col, bool isWhite){

	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "N";
 }

 Knight::Knight(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WN";
 }

 
std::vector<int> Knight::canMove(){
 	
	std::vector<int>movement;
	Block** board = Board::block;
	
	board[row][col].setItHasUnit(false);//remove from board to check movements

	int potentialMovement[]={-1,2, -2,1, 1,2, 2,1, 2,-1, 1,-2, -1,-2, -2,-1};
 	for (int i = 0; i <16; i+=2)
 	{

		int k = row + potentialMovement[i];
		int p = col + potentialMovement[i + 1];

 		if (!this->isOutBounds(k,p)){//checks if it goes out of bounds
			//then checks if there is a unit on the square and checks what color that unit is

			if (Board::checkIfUnitCanMove(k,p)){
				movement.push_back(k);
				movement.push_back(p);
			}
		}
	}

	board[row][col].setItHasUnit(true); //put unit back in the baord

	return movement;
 }
 




//only have to check if out of bounds or landing on an ally piece




 
 

#endif