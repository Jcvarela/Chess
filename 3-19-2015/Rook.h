#ifndef ROOK_H
#define ROOK_H

#include "Unit.h"
#include <string>

class Rook: public Unit{
public:
	Rook(int row, int col, bool isWhite);
	Rook();

};



#endif