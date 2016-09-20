
#include <string>
#include "Block.h"
#include "Unit.h"

Block::Block(bool hasColor1, Unit unit){
	this->hasColor1 = hasColor1;
	this->unit = unit;
	this->hasUnit = true;
}

Block::Block(bool hasColor1, int unit){
	this->hasColor1 = hasColor1;
	this->hasUnit = false;
	this->unit = Unit(0,0,true);
}
Block::Block(){
	this->hasColor1 = true;
	this->hasUnit = false;
	this->unit = Unit(0,0,true);
}


bool Block::itIsColor1(){ return this->hasColor1; }
bool Block::ithasUnit(){ return this->hasUnit; }
Unit Block::getUnit(){ return this->unit; }

void Block::setUnit(Unit unit){
	this->hasUnit = true;
	this->unit = unit;
}
void Block::setUnit(int unit){
	this->hasUnit = false;
}
