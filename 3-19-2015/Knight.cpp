#include <string>
#include "Unit.h"
#include "Knight.h"



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