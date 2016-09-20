#ifndef BISHOP_CPP
#define BISHOP_CPP

#include <string>
#include "Unit.h"
#include "Bishop.h"



Bishop::Bishop(int row, int col, bool isWhite){

	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "B";
 }

 Bishop::Bishop(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WB";
 }

#endif