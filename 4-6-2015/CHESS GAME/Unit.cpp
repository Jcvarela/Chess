
#include "Unit.h"
#include <string>

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


 int Unit::getRow(){ return this->row; }
 int Unit::getCol(){ return this->col; }
 bool Unit::isItWhite(){return this->isWhite; }
 std::string Unit::getName(){ return this->name; }

 bool Unit::moveTo(std::string to){
	 
	 int row = to.at(1) - '1';
	 int col = to.at(0) - 'a';

	
	 //can be remove on board before sending to

	 if(to.size() > 2)                
		 return false;
	 if( col < 0 || col > 25)
		 return false;
	 if(row < 0 || row >7)
		 return false;

	 //_________________________________________

	 int checkR = row - this->row;
	 int checkC = col - this->col;

	 bool check = false;
	 for(int i = 0; i < sizeof(move)/sizeof(move[i]); i = i+2){
		 if(checkR == move[i] && checkC == move[i+1]){
			 check = true;
			 break;
		 }
	 }

	 if(check){
		this->row = row;
		this->col = col;
		return true;
	 }
	 else{
		return false;
	 } 
 }

 bool Unit::attackTo(std::string to){
	 int row = to.at(1) - '1';
	 int col = to.at(0) - 'a';

	 //can be remove on board before sending to

	 if(to.size() > 2)                
		 return false;
	 if( col < 0 || col > 25)
		 return false;
	 if(row < 0 || row >7)
		 return false;

	 //_________________________________________

	 int checkR = row - this->row;
	 int checkC = col - this->col;

	 bool check = false;
	 for(int i = 0; i < sizeof(attack)/sizeof(attack[i]); i = i+2){
		 if(checkR == attack[i] && checkC == attack[i+1]){
			 check = true;
			 break;
		 }
	 }

	 if(check){
		this->row = row;
		this->col = col;
		return true;
	 }
	 else{
		return false;
	 } 
 
 }

 bool Unit::isOutBounds(int row, int col){
	 return (row>=0 && row<=7 && col>=0 && col<=7);
 }
