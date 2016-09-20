#ifndef UNIT_CPP
#define UNIT_CPP

#include "Unit.h"
#include <string>
#include <vector>

#include <iostream>

 const int Unit::move[16] = {-1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1};
 const int Unit::attack[16] = {-1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1};

 Unit::Unit(int row, int col, bool isWhite){
	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;

	 this->name = (isWhite)?"W":"B";

	 this->name += "U";
 }
 Unit::Unit(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WU";
 }

 //getters
 int Unit::getRow(){ return this->row; }
 int Unit::getCol(){ return this->col; }
 bool Unit::isItWhite(){return this->isWhite; }
 std::string Unit::getName(){  return this->name;
 }


 //setters 

 void Unit::changePosition(int row, int col){
	 this->row = row;
	 this->col = col;
 }



 // return true if is out of bound
 //			false if is in bound
 bool Unit::isOutBounds(int row, int col){
	 return !(row >= 0 && row <= 7 && col >= 0 && col <= 7);
 }

 //default canMove function return all values 
 std::vector<int> Unit::canMove(){

	 std::vector<int> movement; // {row, col}

	 for (int i = 0; i < 8; i ++){
		 for (int j = 0; j < 8;j ++){
			 movement.push_back(i);
			 movement.push_back(j);
		 }
	 }
	 return movement;
 }


 void Unit::setIsItWhite(bool isWhite){
	 this->isWhite = isWhite;
 }





#endif