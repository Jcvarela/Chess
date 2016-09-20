#ifndef KNIGHT_H
#define KNIGHT_H

#include "Unit.h"
#include <string>
#include <vector>

class Knight: public Unit{
public:
	Knight(int row, int col, bool isWhite);
	Knight();
	std::vector<int> canMove();
};



#endif