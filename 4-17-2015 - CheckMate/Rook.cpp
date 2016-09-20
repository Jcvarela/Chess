#ifndef ROOK_CPP
#define ROOK_CPP
#include<iostream>
#include "Board.h"
#include "Block.h"
#include <vector>
#include <string>
#include "Unit.h"
#include "Rook.h"

using namespace std;

Rook::Rook(int row, int col, bool isWhite){

	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "R";
 }

 Rook::Rook(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WR";
 }


 vector<int> Rook::canMove(){
	 bool continuesUp, continuesDown, continuesRight, continuesLeft;
	 continuesUp = continuesDown = continuesRight = continuesLeft = true;

	 vector<int> movement;				//This vector contains an even number of values, pairing values for every posible move the Rook can move
	 
	 Block** board = Board::block;		//We are creating a 2d array of Block pointers, to asign the static value of our board (WE are getting the value of [Block** block] in class Board and asigning it to our board) 

	 board[row][col].setItHasUnit(false);//remove from board to check movements

	 for(int i=1; i<=7; i++){			//This loop will go (UP TO) 7 places up, down, left and right checking for posible moves for our Rook

		 if (continuesDown && !this->isOutBounds(row, col + i) && (hasEnemy(&board[row][col + i]) || !board[row][col + i].ithasUnit())){  //We check for columns down the board
			 if (hasEnemy(&board[row][col + i]))			/*_________________________________________ */
				 continuesDown = false;						/*|NOTE:								   |*/
			 if (Board::checkIfUnitCanMove(row, col + i)){	/*|If we find a unit either friend or enemy|*/
				 movement.push_back(row);					/*|we set the continue Boolean to false    |*/
				 movement.push_back(col + i);				/*|since we can't check past any unit      |*/
			 }												/*|________________________________________|*/

		 }
		 else continuesDown = false;

		 if (continuesUp && !this->isOutBounds(row, col - i) && (hasEnemy(&board[row][col-i]) || !board[row][col-i].ithasUnit())){  //We check for columns up the board
			 if(hasEnemy(&board[row][col-i]))		
				 continuesUp = false;

			 if (Board::checkIfUnitCanMove(row, col - i)){
				 movement.push_back(row);
				 movement.push_back(col - i);
			 }
		 }													
		 else continuesUp=false;


		 if (continuesRight && !this->isOutBounds(row + i, col) && (hasEnemy(&board[row+i][col]) || !board[row+i][col].ithasUnit())){  //We check for columns to the right of board
			 if(hasEnemy(&board[row+i][col]))			
				 continuesRight=false;					
			

			 if (Board::checkIfUnitCanMove(row + i, col )){
				 movement.push_back(row + i);
				 movement.push_back(col);
			 }
				
		 }												
		 else continuesRight=false;


		 if (continuesLeft && !this->isOutBounds(row - i, col) && (hasEnemy(&board[row-i][col]) || !board[row-i][col].ithasUnit())){  //We check for columns to the left of the board
			 if(hasEnemy(&board[row-i][col]))			
				 continuesLeft=false;					
			
			 if (Board::checkIfUnitCanMove(row - i,col)){
				 movement.push_back(row -i);
				 movement.push_back(col);
			 }
				
		 }												
		 else continuesLeft=false;


	 }


	 board[row][col].setItHasUnit(true); //put unit back in the baord
	 return movement;


 }


 //This function checks if a block has an enemy unit
 bool Rook::hasEnemy(Block *b){

	 if(!b->ithasUnit())		//If no unit is found in the block return false
		 return false;
	 else if(this->isWhite==(b->getUnit()->isItWhite()))	//If the unit found is the same color return false
		 return false;
	 else							//If the unit found is enemy return true
		 return true;

 }

 //b2 previus block
 //b block going to
 //check out of bound before method
  /*bool Rook::canContinue(Block *b, Block *b2){
	 
	  //if previus blokc has unit and are not the same color stop moving farward
	  //or 
	  //if temporary block has unit and are the same color stop moving farward 
	  if(  (b2.ithasUnit() && (this->isItWhite() != b2.getUnit()->isItWhite()))  || (b.ithasUnit() && (this->isItWhite() == b.getUnit()->isItWhite())) ){
		return false;
	  }

	  //everything else return true
	 return true;

 }*/

#endif