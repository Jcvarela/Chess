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
	

public:

	Block(bool hasCoolor1, Unit unit);	
	Block(bool hasColor1);			//If unit is null it gets called
	Block();
	~Block();

	bool itIsColor1();
	bool ithasUnit();

	Unit* getUnit();
	void setUnit(Unit unit);
	void setUnit();
	void setDefaultUnit();

private:

	Unit* makeUnit(Unit unit);// locate memory for unit

};

#endif