#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "User_Move.h"
#include "constants.h"
#include "board.h"
#include "ChessPieces.h"
#include "AI_Move.h"


/*moves queen to desired position. prints invalid move when necessary.*/
int MoveQueen(int queen_value, int arr[], int start, int end){
	/*asserts that piece is either a white or black queen*/
	assert(	queen_value == wQ || queen_value == bQ);
	/*asserts that input is in bounds of board*/
	assert(start >= a8 && start <= h1);
	assert(end >= a8 && end <= h1);

	//stuff ralph added to try to check check
	int boardTemp[64];
	memcpy (boardTemp, arr, sizeof (boardTemp)); //stores the board into a temporary board to save it
	int kingposition = findKing (arr, start); //finds the position of the king to check check
	int kingvalue = boardTemp[kingposition];     //stores the value of which king depending on the startLocation provided by kingposition

	if(start == end){	//no movement needed.
		printf("Invalid move! Piece already in that position.\n");
		return -10;
	} 
	
	/*checks to make sure user does not try to capture own pieces*/
	if(queen_value <17){				//Any piece 17 or larger is black. Any piece from 1 to 16 is white
		if(arr[end] > 0 && arr[end] < 17){
			printf("Invalid move! You cannot capture your own pieces.\n");
			return -10;
		}
	}
	else if(queen_value >= 17){
		if(arr[end] >= 17){
			printf("Invalid move! You cannot capture your own pieces.\n");
			return -10;
		}
	}
	
	int i = start;
	enum direction_value d_value = n_value;
	/*changes queen_direction and d_value to the direction desired. if GetQueenDirection() returns -10 (invalid move), MoveQueen returns -10 as well.*/
	if(GetQueenDirection(start, end, &d_value)){
		return -10;
	}
	while(i != end){
		i += d_value;
		if(i == end){
			if(arr[i]){
				arr[i] = queen_value;
				arr[start] = 0;
				if (isKingInCheckAI (arr, kingvalue, kingposition) == 1) { //if king is in check after a result of the move, then revert board and return error
					memcpy (IntBoard, boardTemp, sizeof (IntBoard));
					printf ("Invalid Move: must move King out of check\n");
					return -100;
				}
				return 0; //a capture occured
			}
			else{
				arr[i] = queen_value;
				arr[start] = 0;
				if (isKingInCheckAI (arr, kingvalue, kingposition) == 1) { //if king is in check after a result of the move, then revert board and return error
					memcpy (IntBoard, boardTemp, sizeof (IntBoard));
					printf ("Invalid Move: must move King out of check\n");
					return -100;
				}
				return 0; //no error, no capture
			}
		}
		else if(arr[i] == 0){
			continue;
		}
		else{
			printf("Invalid move! You cannot move past pieces.\n");
			return -10;
		}
	}
	printf("Error: end of function reached.\n");
	return -10;
}

int MoveRook(int rook_value, int arr[], int start, int end){
	assert(	rook_value == wQr || rook_value == bQr || rook_value == wKr || rook_value == bKr);
	assert(start >= a8 && start <= h1);
	assert(end >= a8 && end <= h1);

		//stuff ralph added to try to check check
	int boardTemp[64];
	memcpy (boardTemp, arr, sizeof (boardTemp)); //stores the board into a temporary board to save it
	int kingposition = findKing (arr, start); //finds the position of the king to check check
	int kingvalue = boardTemp[kingposition];     //stores the value of which king depending on the startLocation provided by kingposition


	if(start == end){	//no movement needed.
		printf("Invalid move! Piece already in that position.\n");
		return -10;
	} 
	
	/*checks to make sure user does not try to capture own pieces*/
	if(rook_value < 17){
		if(arr[end] > 0 && arr[end] < 17){
			printf("Invalid move! You cannot capture your own pieces.\n");
			return -10;
		}
	}
	else if(rook_value >= 17){
		if(arr[end] >= 17){
			printf("Invalid move! You cannot capture your own pieces.\n");
			return -10;
		}
	}
	
	int i = start;
	enum direction_value d_value = n_value;
	/*changes rook_direction and d_value to the direction desired. if GetQueenDirection() returns -10 (invalid move), MoveQueen returns -10 as well.*/
	if(GetRookDirection(start, end, &d_value)){
		return -10;
	}
	while(i != end){
		i += d_value;
		if(i == end){
			if(arr[i]){
				arr[i] = rook_value;
				arr[start] = 0;
				if (isKingInCheckAI (arr, kingvalue, kingposition) == 1) { //if king is in check after a result of the move, then revert board and return error
					memcpy (IntBoard, boardTemp, sizeof (IntBoard));
					printf ("Invalid Move: must move King out of check\n");
					return -100;
				}
				return 0; //a capture occured
			}
			else{
				arr[i] = rook_value;
				arr[start] = 0;
				if (isKingInCheckAI (arr, kingvalue, kingposition) == 1) { //if king is in check after a result of the move, then revert board and return error
					memcpy (IntBoard, boardTemp, sizeof (IntBoard));
					printf ("Invalid Move: must move King out of check\n");
					return -100;
				}
				return 0; //no error, no capture
			}
		}
		else if(arr[i] == 0){
			continue;
		}
		else{
			printf("Invalid move! You cannot move past pieces.\n");
			return -10;
		}
	}
	printf("Error: end of function reached.\n");
	return -10;
}

int MoveBishop(int bishop_value, int arr[], int start, int end){
	assert(	bishop_value == wQb || bishop_value == bQb || bishop_value == wKb || bishop_value == bKb);
	assert(start >= a8 && start <= h1);
	assert(end >= a8 && end <= h1);

	//stuff ralph added to try to check check
	int boardTemp[64];
	memcpy (boardTemp, arr, sizeof (boardTemp)); //stores the board into a temporary board to save it
	int kingposition = findKing (arr, start); //finds the position of the king to check check
	int kingvalue = boardTemp[kingposition];     //stores the value of which king depending on the startLocation provided by kingposition


	if(start == end){	//no movement needed.
		printf("Invalid move! Piece already in that position.\n");
		return -10;
	} 
	
	/*checks to make sure user does not try to capture own pieces*/
	if(bishop_value <17){				//Any piece 17 or larger is black. Any piece from 1 to 16 is white
		if(arr[end] > 0 && arr[end] < 17){
			printf("Invalid move! You cannot capture your own pieces.\n");
			return -100;
		}
	}
	else if(bishop_value >= 17){
		if(arr[end] >= 17){
			printf("Invalid move! You cannot capture your own pieces.\n");
			return -100;
		}
	}
	
	int i = start;
	enum direction_value d_value = ne_value;
	/*changes bishop_direction and d_value to the direction desired. if GetBishopDirection() returns -10 (invalid move), MoveBishop() returns -10 as well.*/
	if(GetBishopDirection(start, end, &d_value)){
		return -10;
	}
	while(i != end){
		i += d_value;
		if(i == end){
			if(arr[i]){
				arr[i] = bishop_value;
				arr[start] = 0;
				if (isKingInCheckAI (arr, kingvalue, kingposition) == 1) { //if king is in check after a result of the move, then revert board and return error
					memcpy (IntBoard, boardTemp, sizeof (IntBoard));
					printf ("Invalid Move: must move King out of check\n");
					return -10;
				}
				return 0; //a capture occured
			}
			else{
				arr[i] = bishop_value;
				arr[start] = 0;
				if (isKingInCheckAI (arr, kingvalue, kingposition) == 1) { //if king is in check after a result of the move, then revert board and return error
					memcpy (IntBoard, boardTemp, sizeof (IntBoard));
					printf ("Invalid Move: must move King out of check\n");
					return -10;
				}
				return 0; //no error, no capture
			}
		}
		else if(arr[i] == 0){
			continue;
		}
		else{
			printf("Invalid move! You cannot move past pieces.\n");
			return -10;
		}
	}
	printf("Error: end of function reached.\n");
	return -10;
}

/*gets the queen's direction and direction value which are passed by refernce. Returns 0 if no errors. Returns -10 if move is invalid.*/
int GetQueenDirection(int start, int end, enum direction_value *D_value){
	assert(start >= a8 && start <= h1);
	assert(end >= a8 && end <= h1);
	if(start == end){return 0;} //no movement needed.
	int i = start;
	enum direction queen_direction = n;
	enum direction_value d_value = n_value;
	
	/*finds direction that queen is supposed to move(north, west, etc.) Does this by checking all directions until i == end (the ending position of piece)*/ 
	for(queen_direction = n; queen_direction <= nw; queen_direction++){
		i = start;
		switch(queen_direction){
			case n:
				d_value = n_value;
				while(i != end){
					if(i + d_value >= 0){
						i += d_value;
					}
					else{
						break;
					}
				}	
				break;
			case ne:
				d_value = ne_value;
				while(i != end){
					if(i % 8 == 7 || i <= 7){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
			case e:
				d_value = e_value;
				while(i != end){
					if(i % 8 == 7){
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
			case se:
				d_value = se_value;
				while(i != end){
					if(i % 8 == 7 || i >= 56){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
			case s:
				d_value = s_value;
				while(i != end){
					if(i + d_value <= 63){		//63 is the largest position on board
						i += d_value;
					}
					else{
						break;
					}
				}
				break;
			case sw:
				d_value = sw_value;
				while(i != end){
					if(i % 8 == 0 || i >= 56){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
			case w:
				d_value = w_value;
				while(i != end){
					if(i % 8 == 0){
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
			case nw:
				d_value = nw_value;
				while(i != end){
					if(i % 8 == 0 || i <= 7){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
		}
		
		if(i == end){
			*D_value = d_value;
			break;
		}
		
		/*if the program gets to this condition then attempted queen move is invalid*/
		if(queen_direction == nw){
			printf("Invalid move!\n");
			return -10;
		}	
	}
	return 0;
}	

int GetRookDirection(int start, int end, enum direction_value *D_value){
	assert(start >= a8 && start <= h1);
	assert(end >= a8 && end <= h1);
	if(start == end){return 0;} //no movement needed.
	int i = start;
	enum direction rook_direction = n;
	enum direction_value d_value = n_value;
	
	/*finds direction that queen is supposed to move(north, west, etc.) Does this by checking all directions until i == end (the ending position of piece)*/ 
	for(rook_direction = n; rook_direction <= w; rook_direction += 2){
		i = start;
		switch(rook_direction){
			case n:
				d_value = n_value;
				while(i != end){
					if(i + d_value >= 0){
						i += d_value;
					}
					else{
						break;
					}
				}	
				break;
			
			case e:
				d_value = e_value;
				while(i != end){
					if(i % 8 == 7){
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
			
			case s:
				d_value = s_value;
				while(i != end){
					if(i + d_value <= 63){		//63 is the largest position on board
						i += d_value;
					}
					else{
						break;
					}
				}
				break;
			
			case w:
				d_value = w_value;
				while(i != end){
					if(i % 8 == 0){
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
			
		}
		
		if(i == end){
			*D_value = d_value;
			break;
		}
		
		/*if the program gets to this condition then attempted move is invalid*/
		if(rook_direction == w){
			printf("Invalid move!\n");
			return -10;
		}	
	}
	return 0;
}

int GetBishopDirection(int start, int end, enum direction_value *D_value){
	assert(start >= a8 && start <= h1);
	assert(end >= a8 && end <= h1);
	if(start == end){return 0;} //no movement needed.
	int i = start;
	enum direction bishop_direction = ne;
	enum direction_value d_value = ne_value;
	
	/*finds direction that queen is supposed to move(north, west, etc.) Does this by checking all directions until i == end (the ending position of piece)*/ 
	for(bishop_direction = ne; bishop_direction <= nw; bishop_direction += 2){
		i = start;
		switch(bishop_direction){
			case ne:
				d_value = ne_value;
				while(i != end){
					if(i % 8 == 7 || i <= 7){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}
				break;

			case se:
				d_value = se_value;
				while(i != end){
					if(i % 8 == 7 || i >= 56){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
			
			case sw:
				d_value = sw_value;
				while(i != end){
					if(i % 8 == 0 || i >= 56){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
			
			case nw:
				d_value = nw_value;
				while(i != end){
					if(i % 8 == 0 || i <= 7){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}
				break;
		}
		
		if(i == end){
			*D_value = d_value;
			break;
		}
		
		/*if the program gets to this condition then attempted move is invalid*/
		if(bishop_direction == nw){
			printf("Invalid move!\n");
			return -10;
		}	
	}
	return 0;
}

/*Verifies if the king is in check or if moving it to a position will put it in check. 
Position parameter is the position to be verified, does not need to be the king's current position.
Returns 0 if not in check.
Returns 1 if in check.*/
int isKingInCheck(int king_value, int position){
	/*asserts that piece is either a white or black king*/
	assert(king_value == wK || king_value == bK);
	/*asserts that position is in bounds of board*/
	assert(position >= a8 && position <= h1);
	
	int i;
	int knight_position; //used when verifying if a knight is putting the king in check.
	enum direction k_direction = n;
	enum direction_value d_value = n_value;
	/*loops trough all 8 directions that king can be attacked from and verifies if king is in check from any of them.*/
	for(k_direction = n; k_direction <= nw; k_direction++){
		i = position;
		switch(k_direction){
			case n:
				d_value = n_value;
				do{
					if(i + d_value >= 0){
						i += d_value;
					}
					else{
						break;
					}
				}while(IntBoard[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) != 0) && (IntBoard[i] == wKr || IntBoard[i] == wQr || IntBoard[i] == bKr || IntBoard[i] == bQr || IntBoard[i] == wQ || IntBoard[i] == bQ)){ 
					return 1;
				}
				break;
			
			case ne:
				d_value = ne_value;
				do{
					if(i % 8 == 7 || i <= 7){ 	/*this condition keeps from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}while(IntBoard[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) != 0) && (IntBoard[i] == wKb || IntBoard[i] == wQb || IntBoard[i] == bKb || IntBoard[i] == bQb || IntBoard[i] == wQ || IntBoard[i] == bQ)){ 
					return 1;
				}
				/*verifies if a black pawn is putting a white king in check*/
				else if((king_value == wK) && (IntBoard[i] >= bp1 && IntBoard[i] <= bp8 ) && (position + d_value == i)){
					return 1;
				}
				break;
			
			case e:
				d_value = e_value;
				do{
					if(i % 8 == 7){
						break;
					}
					else{
						i += d_value;
					}
				}while(IntBoard[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) != 0) && (IntBoard[i] == wKr || IntBoard[i] == wQr || IntBoard[i] == bKr || IntBoard[i] == bQr || IntBoard[i] == wQ || IntBoard[i] == bQ)){ 
					return 1;
				}
				break;
				
			case se:
				d_value = se_value;
				do{
					if(i % 8 == 7 || i >= 56){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}while(IntBoard[i] == 0);
				/*Verifies if king is in check by a queen or bishop*/
				if((strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) != 0) && (IntBoard[i] == wKb || IntBoard[i] == wQb || IntBoard[i] == bKb || IntBoard[i] == bQb || IntBoard[i] == wQ || IntBoard[i] == bQ)){ 
					return 1;
				}
				/*verifies if a white pawn is putting a black king in check*/
				else if((king_value == bK) && (IntBoard[i] >= wp1 && IntBoard[i] <= wp8 ) && (position + d_value == i)){
					return 1;
				}
				break;
				
			case s:
				d_value = s_value;
				do{
					if(i + d_value <= 63){		//63 is the largest position on board
						i += d_value;
					}
					else{
						break;
					}
				}while(IntBoard[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) != 0) && (IntBoard[i] == wKr || IntBoard[i] == wQr || IntBoard[i] == bKr || IntBoard[i] == bQr || IntBoard[i] == wQ || IntBoard[i] == bQ)){ 
					return 1;
				}
				break;
				
			case sw:
				d_value = sw_value;
				do{
					if(i % 8 == 0 || i >= 56){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}while(IntBoard[i] == 0);
				/*Verifies if king is in check by a queen or bishop*/
				if((strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) != 0) && (IntBoard[i] == wKb || IntBoard[i] == wQb || IntBoard[i] == bKb || IntBoard[i] == bQb || IntBoard[i] == wQ || IntBoard[i] == bQ)){ 
					return 1;
				}
				/*verifies if a white pawn is putting a black king in check*/
				else if((king_value == bK) && (IntBoard[i] >= wp1 && IntBoard[i] <= wp8 ) && (position + d_value == i)){
					return 1;
				}
				break;
				
			case w:
				d_value = w_value;
				do{
					if(i % 8 == 0){
						break;
					}
					else{
						i += d_value;
					}
				}while(IntBoard[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) != 0) && (IntBoard[i] == wKr || IntBoard[i] == wQr || IntBoard[i] == bKr || IntBoard[i] == bQr || IntBoard[i] == wQ || IntBoard[i] == bQ)){ 
					return 1;
				}
				break;
				
			case nw:
				d_value = nw_value;
				do{
					if(i % 8 == 0 || i <= 7){ 	/*this condition keeps the piece from going out of bounds*/
						break;
					}
					else{
						i += d_value;
					}
				}while(IntBoard[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) != 0) && (IntBoard[i] == wKb || IntBoard[i] == wQb || IntBoard[i] == bKb || IntBoard[i] == bQb || IntBoard[i] == wQ || IntBoard[i] == bQ)){ 
					return 1;
				}
				/*verifies if a black pawn is putting a white king in check*/
				else if((king_value == wK) && (IntBoard[i] >= bp1 && IntBoard[i] <= bp8 ) && (position + d_value == i)){
					return 1;
				}
				break;
		}	
	}
	
	/*verifies if a knight is putting the king in check*/
	for(i = 0;i < 8; i++){	//will check all 8 positions a knight can attack a king from.
		switch(i){
			case 0:
				knight_position = position - 15;
				if(position % 8 == 7 || position <= 15){
					break;
				}
				else if((strcmp(Piece[IntBoard[knight_position]].color, Piece[king_value].color) != 0) && (IntBoard[knight_position] == wKn || IntBoard[knight_position] == wQn || IntBoard[knight_position] == bKn || IntBoard[knight_position] == bQn)){
					return 1;
				}
				break;
			
			case 1:
				knight_position = position - 6;
				if(position <= 7 || position % 8 == 7 || position % 8 == 6){
					break;
				}
				else if((strcmp(Piece[IntBoard[knight_position]].color, Piece[king_value].color) != 0) && (IntBoard[knight_position] == wKn || IntBoard[knight_position] == wQn || IntBoard[knight_position] == bKn || IntBoard[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 2:
				knight_position = position + 10;
				if(position >= 56 || position % 8 == 7 || position % 8 == 6){
					break;
				}
				else if((strcmp(Piece[IntBoard[knight_position]].color, Piece[king_value].color) != 0) && (IntBoard[knight_position] == wKn || IntBoard[knight_position] == wQn || IntBoard[knight_position] == bKn || IntBoard[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 3:
				knight_position = position + 17;
				if(position >= 48  || position % 8 == 7){
					break;
				}
				else if((strcmp(Piece[IntBoard[knight_position]].color, Piece[king_value].color) != 0) && (IntBoard[knight_position] == wKn || IntBoard[knight_position] == wQn || IntBoard[knight_position] == bKn || IntBoard[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 4:
				knight_position = position + 15;
				if(position >= 48 || position % 8 == 0){
					break;
				}
				else if((strcmp(Piece[IntBoard[knight_position]].color, Piece[king_value].color) != 0) && (IntBoard[knight_position] == wKn || IntBoard[knight_position] == wQn || IntBoard[knight_position] == bKn || IntBoard[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 5:
				knight_position = position + 6;
				if(position >= 56 || position % 8 == 0 || position % 8 == 1){
					break;
				}
				else if((strcmp(Piece[IntBoard[knight_position]].color, Piece[king_value].color) != 0) && (IntBoard[knight_position] == wKn || IntBoard[knight_position] == wQn || IntBoard[knight_position] == bKn || IntBoard[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 6:
				knight_position = position - 10;
				if(position <= 7 || position % 8 == 0 || position % 8 == 1){
					break;
				}
				else if((strcmp(Piece[IntBoard[knight_position]].color, Piece[king_value].color) != 0) && (IntBoard[knight_position] == wKn || IntBoard[knight_position] == wQn || IntBoard[knight_position] == bKn || IntBoard[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 7:
				knight_position = position - 17;
				if(position <= 15 || position % 8 == 0){
					break;
				}
				else if((strcmp(Piece[IntBoard[knight_position]].color, Piece[king_value].color) != 0) && (IntBoard[knight_position] == wKn || IntBoard[knight_position] == wQn || IntBoard[knight_position] == bKn || IntBoard[knight_position] == bQn)){
					return 1;
				}
				break;
		}
	}
	return 0;
}

/*Verifies if king is in checkmate.
Run isKingInCheck() before running this function as this one is a lot more code and would be a waste to run on every turn.
Only run this function if isKingInCheck() returns a 1 for the king's CURRENT position.
For position use only the King's CURRENT position.
Returns 1 if checkmate.
Returns 0 if not checkmate. (King could still be in check)
*/
int isKingInCheckMate(int king_value, int position){
	/*asserts that piece is either a white or black king*/
	assert(king_value == wK || king_value == bK);
	/*asserts that position is in bounds of board*/
	assert(position >= a8 && position <= h1);
	
	int i;
	enum direction k_direction = n;
	enum direction_value d_value = n_value;
	
	/*loops trough all 8 directions that king can be attacked from and verifies if king is in check from any of them.*/
	for(k_direction = n; k_direction <= nw; k_direction++){
		i = position;
		switch(k_direction){
			case n:
				d_value = n_value;
				if(i + d_value >= 0){
					i += d_value;
				}
				else{
					break;
				}
				/*Verifies if king is in check at position*/
				if(strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheck(king_value, i)){
					break;
				}
				else{
					return 0;
				}
				break;
			
			case ne:
				d_value = ne_value;
				
				if(i % 8 == 7 || i <= 7){ 	/*this condition keeps from going out of bounds*/
					break;
				}
				else{
					i += d_value;
				}
	
				/*Verifies if king is in check at position*/
				if(strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheck(king_value, i)){
					break;
				}
				else{
					return 0;
				}
				break;
			
			case e:
				d_value = e_value;
				
				if(i % 8 == 7){
					break;
				}
				else{
					i += d_value;
				}
				
				/*Verifies if king is in check at position*/
				if(strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheck(king_value, i)){
					break;
				}
				else{
					return 0;
				}
				break;
				
			case se:
				d_value = se_value;
				
				if(i % 8 == 7 || i >= 56){ 	/*this condition keeps the piece from going out of bounds*/
					break;
				}
				else{
					i += d_value;
				}
				
				/*Verifies if king is in check by a queen or bishop*/
				if(strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheck(king_value, i)){
					break;
				}
				else{
					return 0;
				}
				break;
				
			case s:
				d_value = s_value;
				
				if(i + d_value <= 63){		//63 is the largest position on board
					i += d_value;
				}
				else{
					break;
				}
				
				/*Verifies if king is in check at position*/
				if(strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheck(king_value, i)){
					break;
				}
				else{
					return 0;
				}
				break;
				
			case sw:
				d_value = sw_value;
				
				if(i % 8 == 0 || i >= 56){ 	/*this condition keeps the piece from going out of bounds*/
					break;
				}
				else{
					i += d_value;
				}
				
				/*Verifies if king is in check by a queen or bishop*/
				if(strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheck(king_value, i)){
					break;
				}
				else{
					return 0;
				}
				break;
				
			case w:
				d_value = w_value;
				
				if(i % 8 == 0){
					break;
				}
				else{
					i += d_value;
				}
			
				/*Verifies if king is in check at position*/
				if(strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheck(king_value, i)){
					break;
				}
				else{
					return 0;
				}
				break;
				
			case nw:
				d_value = nw_value;
			
				if(i % 8 == 0 || i <= 7){ 	/*this condition keeps the piece from going out of bounds*/
					break;
				}
				else{
					i += d_value;
				}
		
				/*Verifies if king is in check at position*/
				if(strcmp(Piece[IntBoard[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheck(king_value, i)){
					break;
				}
				else{
					return 0;
				}
				break;
		}	
	}
	return 1;
}