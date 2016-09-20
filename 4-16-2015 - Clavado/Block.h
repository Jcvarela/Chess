#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "Unit.h"

class Block{
private:

	Unit *unit;		//Pieces of the board
	
	bool hasUnit;
	//boc color
	bool hasColor1; // true for color white, false for color black 
	
	int row, col; // cant change position once is set 

public:

	Block(int row, int col, bool hasCoolor1, Unit unit);	
	Block(int row, int col, bool hasColor1);			//If unit is null it gets called
	Block();
	~Block();

	bool itIsColor1();
	bool ithasUnit();

	Unit* getUnit();
	void setUnit(Unit unit);
	void setUnit(std::string name);      
	void setUnit();
	void setDefaultUnit();

	void setItHasUnit(bool hasUnit);
private:

	Unit* makeUnit(Unit unit);// locate memory for unit
	Unit* makeUnit(std::string unit);
};

#endif