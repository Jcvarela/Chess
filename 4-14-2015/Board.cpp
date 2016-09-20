#ifndef BOARD_CPP
#define BOARD_CPP

#include "Block.h"
#include "Board.h"
#include "Unit.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#include <vector>
#include <string>
#include <sstream>

#include <iostream>


bool Board::playerOneTurn = true;
Block** Board::block = new Block*[8];

int Board::wKing[] = {7,4};
int Board::bKing[] = {0,4};

std::vector<std::string> Board::history;

Board::Board(){

	Block **b = new Block*[8];

	bool isColor1 = true;
	for(int i = 0; i < 8; i++){
		
		b[i] = new Block[8];

		for(int j = 0; j < 8; j++){
			b[i][j] = Block(i,j,isColor1);
			b[i][j].setDefaultUnit();
			isColor1 = !isColor1;

		}

		isColor1 = !isColor1;
	}


	//black
	b[1][0].setUnit(Pawn(1,0,false));
	b[1][1].setUnit(Pawn(1,1,false));
	b[1][2].setUnit(Pawn(1,2,false));
	b[1][3].setUnit(Pawn(1,3,false));
	b[1][4].setUnit(Pawn(1,4,false));
	b[1][5].setUnit(Pawn(1,5,false));
	b[1][6].setUnit(Pawn(1,6,false));
	b[1][7].setUnit(Pawn(1,7,false));

	b[0][0].setUnit(Rook(0,0,false));
	b[0][1].setUnit(Knight(0,1,false));
	b[0][2].setUnit(Bishop(0,2,false));
	b[0][3].setUnit(Queen(0,3,false));
	b[0][4].setUnit(King(0,4,false));
	b[0][5].setUnit(Bishop(0,5,false));
	b[0][6].setUnit(Knight(0,6,false));
	b[0][7].setUnit(Rook(0,7,false));



	//white
	b[6][0].setUnit(Pawn(6,0,true));
	b[6][1].setUnit(Pawn(6,1,true));
	b[6][2].setUnit(Pawn(6,2,true));
	b[6][3].setUnit(Pawn(6,3,true));
	b[6][4].setUnit(Pawn(6,4,true));
	b[6][5].setUnit(Pawn(6,5,true));
	b[6][6].setUnit(Pawn(6,6,true));
	b[6][7].setUnit(Pawn(6,7,true));

	b[7][0].setUnit(Rook(7,0,true));
	b[7][1].setUnit(Knight(7,1,true));
	b[7][2].setUnit(Bishop(7,2,true));
	b[7][3].setUnit(Queen(7,3,true));
	b[4][4].setUnit(King(4,4,true));
	b[7][5].setUnit(Bishop(7,5,true));
	b[7][6].setUnit(Knight(7,6,true));
	b[7][7].setUnit(Rook(7,7,true));

	
	wKing[0] = 7;
	wKing[1] = 4;
	bKing[0] = 0;
	bKing[1] = 4;

	delete block;
	block =  b;

	this->playerOneTurn = true;

}



bool Board::moveTo(int frow,int fcol, int trow,int  tcol){

	//keep track of the position of the king if it change
	if (block[frow][fcol].getUnit()->getName().at(1) == 'K'){
		if (block[frow][fcol].getUnit()->getName().at(0) == 'W'){
			wKing[0] = trow;
			wKing[1] = tcol;

		}
		else {
			bKing[0] = trow;
			bKing[1] = tcol;
		}
	}

	block[trow][tcol].setUnit(*block[frow][fcol].getUnit()); //chenges the board
	block[trow][tcol].getUnit()->changePosition(trow,tcol); // changes the position of units
	block[frow][fcol].setUnit(); //delete unit
	
	return true;
}
  

//check if block at postion row, col is been attack by enemy untis
 bool Board::beingAttacked(int row, int col){
	 int arrays[16] = { -1, -1,	  -1, 0,   -1, 1,   0, 1,   1, 1,   1, 0,   1, -1,   0, -1 };
	 Block** board = block;

	 bool check = false;


	 std::vector<int> movement = Knight(row, col, playerOneTurn).canMove();

	 for (unsigned int i = 0; i <movement.size(); i+=2 ){
		 int k = movement[i];
		 int p = movement[i + 1];

		 if (board[k][p].ithasUnit() && board[k][p].getUnit()->getName().at(1) == 'N'){
			 return true;
		 }
	 }



	 //this is going to to check the positions where a block can be attacked, spcifically by a turret, pawn, queen, bishop
	 for (int i = 0; i < 16; i+=2){		
		 for (int j = 1; j < 8; j++){
			 int k = arrays[i] * j + row;
			 int p = arrays[i + 1] * j + col;

				if (!Unit::isOutBounds(k, p)){
					 
					if (board[k][p].ithasUnit()){

						if (board[k][p].getUnit()->isItWhite() != playerOneTurn){
							check = piecesWhat(row, col, k, p);
							if (check){
								return check;
							}
						} 
						
						break;
						
					} 
					else {
						continue;
					}

				}
				else { //is out of bound 
					break;
				}
		 }
	 }
	 return check;
}	
 //checks which element is attacking and returns if there is an element that can attack the block
 bool Board::piecesWhat(int row, int col, int row2, int col2){

	 std::string name = block[row2][col2].getUnit()->getName();
	 bool check = false;
	 int m;
	 int n;
	 int mult;

	 switch (name.at(1)){

	 case 'B':

		 if (row2 != row && col2 != col){
			 check = true;
		 }

		 break;
	 case 'R':

		 if (row2 == row || col2 == col){
			 check = true;
		 }
		 break;

	 case 'P':
		 //find a way check for both pawns
		 mult = (block[row2][col2].getUnit()->isItWhite()? -1 : 1); 

		 if ( (row - row2)*mult  == 1 && ( col + 1 == col2  || col - 1 == col2) ){
			 check = true;
		 }

		 break;

	 case 'K':
		 m = row - row2;
		 n = col - col2;

		 if ((m == 1 || m == -1 || m == 0) && (n == 1 || n == -1 || n == 0)){
			 check = true;
		 }

		 break;
	 case 'Q':
		 check = true;
		 break;

	 default:
		 check = false;
		 break;
	 }

	 return check;
 }


 std::string Board::printHistory(){
	 std::string value = "";
	 std::string extra, positionFrom ="", positionTo = "";

	 //print 5 last plays
	 for (unsigned int i = 1; i <= history.size()  &&   i <= 5; i++){
		 std::ostringstream num;
		 num << i;
		 value += "\t\t\t" + num.str() + ": ";
		 
		 extra = history[history.size() - i];
		 


		 switch(extra.at(0)){
		 case '1': //it move
			 
			 positionFrom = (char)('A' + (extra.at(2) - '0'));
			 positionFrom += (char)('1' + (extra.at(1) - '0'));
			 positionTo = (char)('A' + (extra.at(4) - '0'));
			 positionTo += (char)('1' + (extra.at(3) - '0'));

			 value += "Move " + extra.substr(5,2) +" from " + positionFrom + " to " + positionTo;
			 break;
			 
		 case '2': //it attack

			 positionFrom = (char)('A' + (extra.at(2) - '0'));
			 positionFrom += (char)('1' + (extra.at(1) - '0'));
			 positionTo = (char)('A' + (extra.at(4) - '0'));
			 positionTo += (char)('1' + (extra.at(3) - '0'));

			 value += "Attack " + extra.substr(7, 2) + " at " + positionTo + " from " + positionFrom + " with "+ extra.substr(5,2);
			 break;
			 
		 case '3': //Castling

			 value += "Castling " + extra.substr(5, 2) + " to " + ((extra.at(4) > extra.at(2)) ? "right": "left");
			 break;
		 case '4':
			 positionFrom = (char)('A' + (extra.at(2) - '0'));
			 positionFrom += (char)('1' + (extra.at(1) - '0'));

			 value += "Promote " + extra.substr(5, 2) + " at " + positionFrom + " to " + extra.substr(7, 2);
			break;
		 default:
			 value += extra;
			 break;
		 }//end switch
		value += "\n";
	 }//end for loop

	 return value;
 }

 void Board::addHistory(int frow, int fcol, int trow, int  tcol){
	 std::string h = "";
	 std::ostringstream num;
	 if (block[trow][tcol].ithasUnit()){
		 h = "2"; // means its eating 
	 }
	 else {
		 h = "1"; //means its moving
	 }
	 num << frow << fcol << trow << tcol;
	 h += num.str() + block[frow][fcol].getUnit()->getName();

	 if (block[trow][tcol].ithasUnit()){
		 h += block[trow][tcol].getUnit()->getName();
	 }
	 history.push_back(h);
 }

 bool Board::goback(){
	
	 if (history.size() == 0){
		 return false;
	 }
	 else{
		 int frow, fcol, trow, tcol;

		 std::string extra = history[history.size() - 1];
		 history.pop_back();

		 switch (extra.at(0)){
		 case '1':

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';
		 
			 moveTo(frow, fcol, trow, tcol);

			 break;
			 
		 case '2':

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';

			 moveTo(frow, fcol, trow, tcol);
			 block[frow][fcol].setUnit( extra.substr(7, 2) );

			 break;

		 default: // missing 3 and 4 
			 break;

		 }// end switch

	 }//end for loop

	return true;
 }


 bool Board::isYourKingBeenAttack(){
	
	 if (playerOneTurn){
		 return beingAttacked(wKing[0], wKing[1]);
	 }
	 else {
		 return beingAttacked(bKing[0],bKing[1]);
	 }
	
 }


 std::string Board::getBoard(){
	 std::string value = "";

	 value += "      A      B      C      D      E      F      G      H   \n";

	 for (int i = 0; i < 8; i++){				// 

		 value += "    ------ ------ ------ ------ ------ ------ ------ ------\n";
		 for (int j2 = 0; j2 < 3; j2++){
			 if (j2 == 1)
				 value += " " + std::to_string(i + 1) + " |";
			 else
				 value += "   |";
			 for (int j = 0; j < 8; j++){

				 if (!block[i][j].itIsColor1()){

					 if (j2 == 1 && block[i][j].ithasUnit()){
						 value += "  " + block[i][j].getUnit()->getName() + "  ";
					 }
					 else {
						 value += "      ";
					 }
				 }
				 else {

					 if (j2 == 1 && block[i][j].ithasUnit()){
						 value += (char)-37;
						 value += (char)-37;
						 value += block[i][j].getUnit()->getName();
						 value += (char)-37;
						 value += (char)-37;
					 }
					 else {
						 value += (char)-37;
						 value += (char)-37;
						 value += (char)-37;
						 value += (char)-37;
						 value += (char)-37;
						 value += (char)-37;
					 }
				 }

				 value += "|";
			 }
			 if (j2 == 1)
				 value += " " + std::to_string(i + 1) + "\n";
			 else
				 value += "\n";
		 }

	 }
	 value += "    ------ ------ ------ ------ ------ ------ ------ ------\n";
	 value += "      A      B      C      D      E      F      G      H   \n";



	 return value;
 }

#endif