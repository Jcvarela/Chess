#ifndef QUEEN_H
#define QUEEN_H

#include "Unit.h"
#include <string>
#include <vector>
#include "Block.h"

class Queen: public Unit{
	public:
		Queen(int row, int col, bool isWhite);
		Queen();

		std::vector<int> canMove();
		bool hasEnemy(Block *b);
};

#endif
