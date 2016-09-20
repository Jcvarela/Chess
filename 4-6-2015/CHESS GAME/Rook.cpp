#include <string>
#include "Unit.h"
#include "Rook.h"



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