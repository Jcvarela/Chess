#ifndef PAWN_H
#define PAWN_H

#include "Unit.h"
#include <string>
#include "Board.h"

class Pawn: public Unit{

public:

	Pawn(int row, int col, bool isWhite);
	Pawn();
	int* canMove(Block** block);
};


#endif
