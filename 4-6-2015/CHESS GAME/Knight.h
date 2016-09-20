#ifndef KNIGHT_H
#define KNIGHT_H

#include "Unit.h"
#include <string>

class Knight: public Unit{
public:
	Knight(int row, int col, bool isWhite);
	Knight();

};



#endif