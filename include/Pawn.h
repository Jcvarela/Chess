#ifndef PAWN_H
#define PAWN_H

#include "Unit.h"
#include <string>
#include <vector>

class Pawn: public Unit{
	public:
		Pawn(int row, int col, bool isWhite);
		Pawn();

		std::vector<int> canMove();
};

#endif
