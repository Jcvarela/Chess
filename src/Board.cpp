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

//keeps track of king position and last one of how many time it move
int Board::wKing[] = { 7, 4,0 };
int Board::white_left_rook[] = { 0, 0, 0 };
int Board::white_right_rook[] = { 0, 0, 0 };

int Board::bKing[] = { 0, 4,0 };
int Board::black_left_rook[] = { 0, 0, 0 };
int Board::black_right_rook[] = { 0, 0, 0 };

std::vector<std::string> Board::history;

//constroctor
Board::Board(){
}

void Board::InitializeBoard(){

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
	black_left_rook[0] = 0;
	black_left_rook[1] = 0;
	black_left_rook[2] = 0;
	b[0][1].setUnit(Knight(0,1,false));
	b[0][2].setUnit(Bishop(0,2,false));
	b[0][3].setUnit(Queen(0,3,false));
	b[0][5].setUnit(Bishop(0,5,false));
	b[0][6].setUnit(Knight(0,6,false));
	b[0][7].setUnit(Rook(0,7,false));
	black_right_rook[0] = 0;
	black_right_rook[1] = 7;
	black_right_rook[2] = 0;



	//white
	b[6][0].setUnit(Pawn(1,0,true));
	b[6][1].setUnit(Pawn(6,1,true));
	b[6][2].setUnit(Pawn(6,2,true));
	b[6][3].setUnit(Pawn(6,3,true));
	b[6][4].setUnit(Pawn(6,4,true));
	b[6][5].setUnit(Pawn(6,5,true));
	b[6][6].setUnit(Pawn(6,6,true));
	b[6][7].setUnit(Pawn(6,7,true));

	b[7][0].setUnit(Rook(7,0,true));
	white_left_rook[0] = 7;
	white_left_rook[1] = 0;
	white_left_rook[2] = 0;
	b[7][1].setUnit(Knight(7,1,true));
	b[7][2].setUnit(Bishop(7,2,true));
	b[7][3].setUnit(Queen(7,3,true));
	b[7][5].setUnit(Bishop(7,5,true));
	b[7][6].setUnit(Knight(7,6,true));
	b[7][7].setUnit(Rook(7,7,true));
	white_right_rook[0] = 7;
	white_right_rook[1] = 7;
	white_right_rook[2] = 0;

	b[0][4].setUnit(King(0, 4, false)); //0,4
	bKing[0] = 0; //row
	bKing[1] = 4; // col
	bKing[2] = 0; // how many time has move

	b[7][4].setUnit(King(7, 4, true)); // 7,4
	wKing[0] = 7; //row
	wKing[1] = 4;// col
	wKing[2] = 0;// how many has move




	delete[] block;
	block =  b;

	playerOneTurn = true;
}



bool Board::moveTo(int frow,int fcol, int trow,int  tcol){

	//keep track of the position of the king if it change
	if (block[frow][fcol].getUnit()->getName().at(1) == 'K'){

		int value = fcol - tcol;

		if (block[frow][fcol].getUnit()->getName().at(0) == 'W'){
			wKing[0] = trow;
			wKing[1] = tcol;
			wKing[2]++;


			if (value == 2){ //castling to the left
				moveTo(7,0,7,3);
			}
			else if (value == -2){ //castling to the right
				moveTo(7,7,7,5);
			}
		}
		else {
			bKing[0] = trow;
			bKing[1] = tcol;
			bKing[2]++;


			if (value == 2){ //castling to the left
				moveTo(0, 0, 0, 3);
			}
			else if (value == -2){ //castling to the right
				moveTo(0, 7, 0, 5);
			}
		}


	}



	//keeps track of the position of the rook if it change
	if (block[frow][fcol].getUnit()->getName().at(1) == 'R'){

		if (frow == white_left_rook[0] && fcol == white_left_rook[1]){
			white_left_rook[0] = trow;
			white_left_rook[1] = tcol;
			white_left_rook[2]++;
		}
		else if (frow == white_right_rook[0] && fcol == white_right_rook[1]){
			white_right_rook[0] = trow;
			white_right_rook[1] = tcol;
			white_right_rook[2]++;
		}
		else if (frow == black_left_rook[0] && fcol == black_left_rook[1]){
			black_left_rook[0] = trow;
			black_left_rook[1] = tcol;
			black_left_rook[2]++;
		}
		else if (frow == black_right_rook[0] && fcol == black_right_rook[1]){
			black_right_rook[0] = trow;
			black_right_rook[1] = tcol;
			black_right_rook[2]++;
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


	 int potentialMovement[] = { -1, 2, -2, 1, 1, 2, 2, 1, 2, -1, 1, -2, -1, -2, -2, -1 };

	 for (int i = 0; i < 16; i += 2){ //check if horse can attack that block
		 int k = row + potentialMovement[i];
		 int p = col + potentialMovement[i + 1];
		 if ((k >= 0 && k <= 7 &&  p >= 0 && p <= 7)){ // if is not out of bound

			 if (board[k][p].ithasUnit() && board[k][p].getUnit()->getName().at(1) == 'N' && board[k][p].getUnit()->isItWhite() != playerOneTurn){
				 return true;
			 }
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
	 std::string position_extra = "";


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


		 case '5':
			 positionFrom = (char)('A' + (extra.at(2) - '0'));
			 positionFrom += (char)('1' + (extra.at(1) - '0'));
			 positionTo = (char)('A' + (extra.at(4) - '0'));
			 positionTo += (char)('1' + (extra.at(3) - '0'));

			 position_extra = (char)('A' + (extra.at(9) - '0'));
			 position_extra += (char)('1' + (extra.at(10) - '0'));

			 value += "En passant: Attack " + extra.substr(7, 2) + " at " + position_extra + " by " + extra.substr(5,2) + " from " + positionFrom + " to " + positionTo;
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

		 int value = tcol - fcol;

		 //if unit at from is a king and the distance move is two then is castling
		 if (block[frow][fcol].getUnit()->getName().at(1) == 'K' && (value == 2 || value == -2)){
			 h = "3"; //its castling
		 }
		 else if (block[frow][fcol].getUnit()->getName().at(1) == 'P' && (value != 0)){ //En passant
			 h = "5";
		 }
		 else {
			 h = "1"; //means its moving
		 }

	}

	 if (h.compare("5") == 0){

		 num << frow << fcol << trow << tcol << block[frow][fcol].getUnit()->getName() + block[frow][tcol].getUnit()->getName() << frow << tcol;
		 h += num.str();
		 block[frow][tcol].setItHasUnit(false);

	 }
	 else {

		 num << frow << fcol << trow << tcol;
		 h += num.str() + block[frow][fcol].getUnit()->getName();

		 if (block[trow][tcol].ithasUnit()){
			 h += block[trow][tcol].getUnit()->getName();
		 }
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
		 case '1': //MOVING

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';

			 moveTo(frow, fcol, trow, tcol);

			 if (block[trow][tcol].getUnit()->getName().at(1) == 'K'){

				 if (block[trow][tcol].getUnit()->getName().at(0) == 'W'){  wKing[2] -= 2;	 }
				 else { bKing[2] -= 2; }

			 }
			 else if (block[trow][tcol].getUnit()->getName().at(1) == 'R'){

				 if (block[trow][tcol].getUnit()->getName().at(0) == 'W'){
					 if (trow == white_left_rook[0] && tcol == white_left_rook[1]){ white_left_rook[2] -= 2; }
					 else { white_right_rook[2] -= 2; }
				 }
				 else {

					 if (trow == black_left_rook[0] && tcol == black_left_rook[1]){ black_left_rook[2] -= 2; }
					 else { black_right_rook[2] -= 2; };
				 }
			 }

			 break;

		 case '2': //EATING

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';

			 moveTo(frow, fcol, trow, tcol);
			 block[frow][fcol].setUnit( extra.substr(7, 2) );



			 if (block[trow][tcol].getUnit()->getName().at(1) == 'K'){

				 if (block[trow][tcol].getUnit()->getName().at(0) == 'W'){ wKing[2] -= 2; }
				 else { bKing[2] -= 2; }

			 }
			 else if (block[trow][tcol].getUnit()->getName().at(1) == 'R'){

				 if (block[trow][tcol].getUnit()->getName().at(0) == 'W'){
					 if (trow == white_left_rook[0] && tcol == white_left_rook[1]){ white_left_rook[2] -= 2; }
					 else { white_right_rook[2] -= 2; }
				 }
				 else {

					 if (trow == black_left_rook[0] && tcol == black_left_rook[1]){ black_left_rook[2] -= 2; }
					 else { black_right_rook[2] -= 2; };
				 }
			 }


			 break;

		 case '3': //CASTLING

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';

			 if (fcol > tcol){ //right
				 moveTo(trow, tcol + 1, trow, 7); //move rook first

				 moveTo(frow, fcol, frow, fcol - 1); //move king
				 moveTo(frow, fcol - 1, trow, tcol);

				 if (block[trow][tcol].getUnit()->isItWhite()){
					 white_right_rook[2] -= 2;
					 wKing[2] -= 3;
				 }
				 else{
					 black_right_rook[2] -= 2;
					 bKing[2] -= 3;
				 }


			 }
			 else { //left
				 moveTo(trow,tcol - 1,trow,0);

				 moveTo(frow, fcol, frow, fcol + 1); //move king
				 moveTo(frow, fcol + 1, trow, tcol);


				 if (block[trow][tcol].getUnit()->isItWhite()){
					 white_left_rook[2] -= 2;
					 wKing[2] -= 3;
				 }
				 else{
					 black_left_rook[2] -= 2;
					 bKing[2] -= 3;
				 }

			 }
			 break;

		 case '4':
			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';

			 block[frow][fcol].setUnit( block[frow][fcol].getUnit()->getName().substr(0,1) + "P" ); //set the value at that position back to Peon
			 goback(); //make peon go back

			 break;

		 case '5':

			 frow = extra.at(3) - '0';
			 fcol = extra.at(4) - '0';
			 trow = extra.at(1) - '0';
			 tcol = extra.at(2) - '0';

			 moveTo(frow, fcol, trow, tcol);

			 block[trow][fcol].setUnit(block[trow][tcol].getUnit()->isItWhite()? "BP":"WP");


		 default: // missing 5
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



 bool Board::checkIfUnitCanMove(int row, int col){

	 bool check = false;

	 if (block[row][col].ithasUnit()){

		 if (block[row][col].getUnit()->isItWhite() != playerOneTurn){

			 block[row][col].getUnit()->setIsItWhite(playerOneTurn);
			 check = !isYourKingBeenAttack();
			 block[row][col].getUnit()->setIsItWhite(!playerOneTurn);
		 }

	 }
	 else {

		 block[row][col].setUnit(Unit(row,col,playerOneTurn));
		 check = !isYourKingBeenAttack();
		 block[row][col].setItHasUnit(false);
	 }


	 return check;
 }

 bool Board::checkIfPlayerHaveMovement(){


	 //go by all the entire board looking for units that belong to current player
	 //if it find that a unit can make a possible movement return true
	 for (int i = 0; i < 8; i++){
		 for (int j = 0; j < 8; j++){

			 // theres a unit in this specific block and it belong to current player
			 if (block[i][j].ithasUnit() && block[i][j].getUnit()->isItWhite() == playerOneTurn){

				 if (block[i][j].getUnit()->canMove().size() > 0){
					 return true; // unit at block i,j has possible movements
				 }
			 }

		 }

	 }

	 //return false if didnt found a unit that could move
	 return false;
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


 bool Board::yourKingMove(){
	 bool check = false;

	 if (playerOneTurn){ //whites
		 check = (wKing[2] != 0); //true if it move
	 }
	 else {
		 check = (bKing[2] != 0); //true if it move
	 }

	 return check;
 }

 bool Board::rook_at_pos_move(int row, int col){

	 bool check = true;

	 if (block[row][col].getUnit()->getName().at(1) != 'R')
		 return true;

	 if (row == white_left_rook[0] && col == white_left_rook[1]){
		 check = (white_left_rook[2] != 0);
	 }
	 else if (row == white_right_rook[0] && col == white_right_rook[1]){
		 check = (white_right_rook[2] != 0);
	 }
	 else if (row == black_left_rook[0] && col == black_left_rook[1]){
		 check = (black_left_rook[2] != 0);
	 }
	 else if (row == black_right_rook[0] && col == black_right_rook[1]){
		 check = (black_right_rook[2] != 0);
	 }

	 return check;
 }


 void Board::setPromotion(std::string name){

	 std::string before = history[history.size() -1];
	 int row = before.at(3) - '0';
	 int col = before.at(4) - '0';

	 if (before.at(0) > '2')
		 return;


	 if (block[row][col].getUnit()->getName().at(1) == 'P' && (row == 0 || row == 7)){

		 block[row][col].setUnit(name); //change block value

		 history.push_back("4" + before.substr(3, 2) + before.substr(3, 2) + before.substr(5, 2) + name); //add to history
	 }

 }





#endif
