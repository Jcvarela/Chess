#ifndef PAWN_H
#define PAWN_H

#include "Unit.h"
#include <string>

class Pawn: public Unit{

public:
	Pawn(int row, int col, bool isWhite);
	Pawn();

};



#endif
