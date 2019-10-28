#ifndef PAWN_CPP
#define PAWN_CPP


#include <string>
#include "Unit.h"
#include "Pawn.h"
#include "Block.h"
#include "Board.h"


#include <iostream>

//row col
//const int Unit::move[8] = {-1,0, -2,0, -1,-1, -1,1};

 Pawn::Pawn(int row, int col, bool isWhite){

	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;

	 this->name = (isWhite)?"W":"B";

	 this->name += "P";
 }

 Pawn::Pawn(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WP";
 }


 //This function returns a vector with all posible movements of this specific pawn
 std::vector<int> Pawn::canMove(){

	 // every two elements will be compose of row and col so peon has 4 movments
	 //{-1,0, -2,0, -1,-1, -1,1}
	 std::vector<int> movement;  // return this value

	 //Block is a static array in the Board class
	 //doing this will alow you to get all the information from the board
	 Block** board = Board::block;

	 board[row][col].setItHasUnit(false);//remove from board to check movements

	 int mult = (this->isWhite ? 1 : -1);



	 //Checks if pawn can move to the block in front of it (one space)
	 if (!this->isOutBounds(row + (-1)*mult, col) && !board[row + (-1)*mult][col].ithasUnit()){

		 if (Board::checkIfUnitCanMove(row + (-1)*mult, col)){
			 movement.push_back(row + (-1)*mult);
			 movement.push_back(col);
		 }
	 }

	 //Checks if pawn can move to the block in front of it (two spaces)
	 if (( (isWhite && row == 6) || (!isWhite && row == 1)) && !board[row + (-2)*mult][col].ithasUnit() && !board[row + (-1)*mult][col].ithasUnit()){


		 if (Board::checkIfUnitCanMove(row + (-2)*mult, col)){
			 movement.push_back(row + (-2)*mult);
			 movement.push_back(col);
		 }


	 }
	 //Checks if pawn can move/attack to the diagonal (right block)
	 if (!this->isOutBounds(row + (-1)*mult, col + 1) && board[row + (-1)*mult][col + 1].ithasUnit() && (this->isWhite != board[row + (-1)*mult][col + 1].getUnit()->isItWhite())){


		 if (Board::checkIfUnitCanMove(row + (-1)*mult, col + 1)){
			 movement.push_back(row + (-1)*mult);
			 movement.push_back(col + 1);
		 }
	 }
	 //Checks if pawn can move/attack to the diagonal (left block)
	 if (!this->isOutBounds(row + (-1)*mult, col - 1) && board[row + (-1)*mult][col - 1].ithasUnit() && (this->isWhite != board[row + (-1)*mult][col - 1].getUnit()->isItWhite())){


		 if (Board::checkIfUnitCanMove(row + (-1)*mult, col - 1)){
			 movement.push_back(row + (-1)*mult);
			 movement.push_back(col - 1);
		 }
	 }



	 //check peon al paso
	 if (Board::history.size() > 0){
		 std::string before = Board::history[Board::history.size() - 1];

		 int frow = before.at(3) - '0';
		 int fcol = before.at(4) - '0';
		 int trow = before.at(1) - '0';
		 int tcol = before.at(2) - '0';


		 if (before.substr(6, 1).compare("P") == 0 && ((frow - trow) == 2 || (frow - trow) == -2)){ // last movement was a peon and its stared with double jump

			 if ((tcol - col == 1 || tcol - col == -1) && row == frow){ // if the difference between columes is 1 and they are at the same row then pawn can do En passant


				 if (Board::checkIfUnitCanMove(row + (-1)*mult, tcol)){
					 movement.push_back(row + (-1)*mult);
					 movement.push_back(tcol);
				 }


			 }
		 }

	 }
	 board[row][col].setItHasUnit(true); //put unit back in the baord
	 return movement;
 }


#endif
