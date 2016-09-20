#ifndef BLOCK_CPP
#define BLOCK_CPP


#include <string>
#include "Block.h"
#include "Unit.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"


#include <iostream>

Block::Block(int row, int col, bool hasColor1, Unit unit){
	this->row = row;
	this->col = col;

	this->hasColor1 = hasColor1;
	this->unit = makeUnit(unit);
	this->hasUnit = true;

}

Block::Block(int row, int col, bool hasColor1){
	this->row = row;
	this->col = col;

	this->hasColor1 = hasColor1;
	this->hasUnit = false;
	this->unit = makeUnit(Unit(0,0,true)); //default unit
}
Block::Block(){
	this->hasColor1 = true;
	this->hasUnit = false;
	this->unit = makeUnit(Unit(0,0,true));
}
Block::~Block(){
	delete this->unit;
	this->unit = NULL;
}


bool Block::itIsColor1(){ return this->hasColor1; }
bool Block::ithasUnit(){ return this->hasUnit; }

Unit* Block::getUnit(){
	return this->unit;
}
void Block::setUnit(std::string name){
	this->hasUnit = true;
	delete this->unit;
	this->unit = makeUnit(name);
}

void Block::setUnit(Unit unit){
	setUnit(unit.getName());
}

void Block::setUnit(){  // NULL
	this->hasUnit = false;
	delete this->unit;
	this->unit = makeUnit(Unit(0, 0, true));
}

void Block::setDefaultUnit(){
	this->hasUnit = false;
	this->unit = makeUnit(Unit(0,0,true));
}

//private method
Unit* Block::makeUnit(Unit unit){
	return makeUnit(unit.getName());
}

Unit* Block::makeUnit(std::string unit){
	Unit *ans = NULL;

	if (unit.substr(1, 1).compare("P") == 0){
		ans = new Pawn(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("R") == 0){
		ans = new Rook(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("B") == 0){
		ans = new Bishop(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("N") == 0){
		ans = new Knight(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("Q") == 0){
		ans = new Queen(row, col, unit.at(0) == 'W');
	}
	else if (unit.substr(1, 1).compare("K") == 0){
		ans = new King(row, col, unit.at(0) == 'W');
	}
	else {
		ans = new Unit(row, col, unit.at(0) == 'W');
	}

	return ans;
}


void Block::setItHasUnit(bool hasUnit){

	this->hasUnit = hasUnit;
}

#endif