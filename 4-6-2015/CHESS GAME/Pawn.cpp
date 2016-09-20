#include <string>
#include "Unit.h"
#include "Pawn.h"
#include "Board.h"

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

 void Unit::changePosition(int row, int col){
	 
	 this->row = row;
	 this->col = col;
 }


 //This function returns an awrray with all posible moves for the pawn piece
 int* Pawn::canMove(Block** block){
	 int *A=new int[8];                  //We put 8 since the row/column size is 8 in a chess board
	 for(int i=0; i<8; i++) A[i]=0;		 //Moves are all 0,0 meaning no moves possible

	 int mult = isWhite? 1:-1;
	 
	 int row=this->row;
	 int col=this->col;

	 //Checks if pawn can move to the block in front of it (one space)
	 if(!this->isOutBounds(row + (-1)*mult, col) && !block[row + (-1)*mult][col].ithasUnit()){
		 A[0]=row + (-1)*mult;
		 A[1]=col;
	 }

	 //Checks if pawn can move to the block in front of it (two spaces)
	 if((isWhite && row == 6 || !isWhite && row == 1) && !block[row + (-2)*mult][col].ithasUnit() && !block[row + (-1)*mult][col].ithasUnit()){
		 A[2] = row + (-2)*mult;
		 A[3] = col;
	 }
	 //Checks if pawn can move/attack to the diagonal (right block)
	 if(!this->isOutBounds(row + (-1)*mult, col + 1) && block[row + (-1)*mult][col + 1].ithasUnit() && (this->isWhite != block[row + (-1)*mult][col + 1].getUnit().isItWhite())){
		 A[4] = row + (-1)*mult;
		 A[5] = col + 1;
	 }  
	 //Checks if pawn can move/attack to the diagonal (left block)
	 if(!this->isOutBounds(row + (-1)*mult, col - 1) && block[row + (-1)*mult][col - 1].ithasUnit() && (this->isWhite != block[row + (-1)*mult][col - 1].getUnit().isItWhite())){
		 A[6] = row + (-1)*mult;
		 A[7] = col - 1;
	 }  

	 return A;
 }
