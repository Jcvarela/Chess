#ifndef BISHOP_H
#define BISHOP_H

#include "Unit.h"
#include <string>

class Bishop: public Unit{
public:
	Bishop(int row, int col, bool isWhite);
	Bishop();

};



#endif