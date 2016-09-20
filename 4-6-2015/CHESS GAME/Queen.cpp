#include <string>
#include "Unit.h"
#include "Queen.h"



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