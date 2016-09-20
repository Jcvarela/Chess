#include "Unit.h"
#include "Pawn.h"
#include "Block.h"
#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#include <vector>
#include <string>


const int Board::row = 8;
const int Board::col = 8;



Board::Board(){

	Block **b = new Block*[this->row];

	bool isColor1 = true;
	for(int i = 0; i < 8; i++){
		b[i] = new Block[this->col];
		for(int j = 0; j < 8; j++){
			b[i][j] = Block(isColor1, NULL);
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
	b[7][4].setUnit(King(7,4,true));
	b[7][5].setUnit(Bishop(7,5,true));
	b[7][6].setUnit(Knight(7,6,true));
	b[7][7].setUnit(Rook(7,7,true));

	
	block =  b;

	this->playerOneTurn = true;

}

std::string Board::getBoard(){
	std::string value = "";

	value +=  "      A      B      C      D      E      F      G      H   \n";

	for (int i = 0; i < 8; i++){

		value += "    ------ ------ ------ ------ ------ ------ ------ ------\n";
		for (int j2 = 0; j2 < 3; j2++){
			if (j2 == 1)
				value +="   |"; // NO
			else
				value += "   |";
			for (int j = 0; j < 8; j++){

				if(!block[i][j].itIsColor1()){

					if(j2 == 1 && block[i][j].ithasUnit()){
						value += "  " + block[i][j].getUnit().getName() + "  ";
					}
					else {
						value += "      ";
					}
				} 
				else {

					if(j2 == 1 && block[i][j].ithasUnit()){
						value += (char)-37;
						value += (char)-37;
						value += block[i][j].getUnit().getName();
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

				value+= "|";
			}
			if (j2 == 1)
				value += "  \n";//NO
			else
				value += "\n";
		}

	}
	value += "    ------ ------ ------ ------ ------ ------ ------ ------\n";
	value +=  "      A      B      C      D      E      F      G      H   \n";



	return value;
}

bool Board::moveTo(int frow,int fcol, int trow,int  tcol){
	this->block[trow][tcol].setUnit(this->block[frow][fcol].getUnit());
	this->block[frow][fcol].setUnit(NULL);
	
	return true;
}