#ifndef BISHOP_CPP
#define BISHOP_CPP

#include <string>
#include "Unit.h"
#include "Bishop.h"
#include <vector>
#include "Board.h"


Bishop::Bishop(int row, int col, bool isWhite){

	 this->row = row;
	 this->col = col;
	 this->isWhite = isWhite;
	 this->name = (isWhite)?"W":"B";
	 this->name += "B";
 }

 Bishop::Bishop(){
	 this->row = 0;
	 this->col = 0;
	 this->isWhite = true;
	 this->name = "WB";
 }
 std::vector<int> Bishop::canMove(){
	 std::vector<int> movement;
	 Block** board = Board::block;
	 
/*	 int a[] = {1,1,  1,-1,  -1,1,  -1,-1};
	 for (int i = 0; i < 8; i += 2){
		 for (int j = 1; j < 8; j ++) {
			 
			 int k = a[i] * j + row;
			 int p = a[i + 1] * j + col;

			 if (this->isOutBounds(k, p) ){

				 if (board[k][p].ithasUnit()){
				  
				 }

			 }
			 
		 }
	 }
	 */

	 for (int i = 0; i < 4; i++)
	 {
		 
		 for (int j = 1; j < 8; j++){
			 int k = 0;
			 int p = 0;
			 switch (i){
			 case 0:
				 k = row - j ;
				 p = col + j ;
				 break;
			 case 1:
				 k = row + j;
				 p = col + j ;
				 break;
			 case 2:
				 k = row - j;
				 p = col - j;
				 break;
			 default:
				 k = row + j;
				 p = col - j;
				 break;

			 }
				if (this->isOutBounds(k, p)){
					break;
				}
				else{ 
					if (board[k][p].ithasUnit() ){
						
						if (this->isWhite != board[k][p].getUnit()->isItWhite()){
							movement.push_back(k);
							movement.push_back(p);
						}
						break;
					}
					else{
						movement.push_back(k);
						movement.push_back(p);
					}
				}
		 }
		

	 }
	 return movement;
 }
#endif