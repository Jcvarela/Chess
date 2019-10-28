#ifndef ROOK_H
#define ROOK_H

#include "Block.h"
#include <vector>
#include "Unit.h"
#include <string>

class Rook: public Unit{
	public:
		Rook(int row, int col, bool isWhite);
		Rook();

		std::vector<int> canMove();
		bool hasEnemy(Block *b);
};

#endif
