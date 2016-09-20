#include <string>
#include "Unit.h"
#include "Pawn.h"


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