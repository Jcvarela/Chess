#include <string>
#include "Unit.h"
#include "King.h"


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