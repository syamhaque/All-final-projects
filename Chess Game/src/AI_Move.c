#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#include "AI_Move.h"
#include "board.h"
#include "ChessPieces.h"
#include "User_Move.h"
#include "constants.h"


/*******************************************/
/***************** ROOK ********************/
/*******************************************/

BESTMOVE bestMove;

int minimax (int depth, int plyOne, int board[], int isMax, int alpha, int beta, char allyTeam[], char enemyTeam[]){ //assuming computer always black
	//printBestMove();
	int IntBoardTemp[64]; // creates the temporary IntBoard so that bestMove knows what to store
	//int newBoard[64];
	int minimaxScore;	//temporary value that will store the score of minimax after it has gone its full depth
	NODELIST *nodeList = createNodeList();	// this initializes the nodelist
	Node *curr;
	if (depth == 0){		// after reaching the leaf node, returns the score of the board after depth number of moves
        if(strcmp(allyTeam, "Black") == 0){
			return -evalscore(board);
        }
		else{
		 	return  evalscore(board);
		}
  	}

	memcpy (IntBoardTemp, board, sizeof (IntBoardTemp));
	if (isMax){ //if its the ai's turn
		MoveAI(allyTeam, nodeList, board); 					// this will generate the list of possible moves
		curr = nodeList->first;				//sets up the variable for the dynamically allocated array; curr is the first member of the array(nodeList)
		int allyLocation;
		for(int i = 0; i< 64; i++){
			if (strcmp(allyTeam, "Black") == 0){
				if(board[i] > 16 && board[i] <= 32){
					allyLocation = i;
					break;
				}
			}
			else if (strcmp(allyTeam, "White") == 0){
				if(board[i] > 0 && board[i] <= 16){
					allyLocation = i;
					break;
				}
			}
		}

		// int kingposition = findKing (board, allyLocation); //passes in endLocation after we update the board
		// if(isKingInCheckAI(bestMove.board, bestMove.board[kingposition], kingposition) == 1 && plyOne == 0){
  //       	if(isKingInCheckMateAI(bestMove.board, bestMove.board[kingposition], kingposition) == 1){
  //       		memcpy (bestMove.board, board, sizeof (bestMove.board));
  //       		printf("King is in Checkmate:'(\n");
  //       	}
  //      	}

		/* this is an alternate loop in case we have issues with the for-loop */
		while(curr){

			minimaxScore = minimax(depth - 1, 1,  curr->board, !isMax, alpha, beta, allyTeam, enemyTeam); //recursive function that calls itself with depth+1 and !isMax, which means it'll be the min

				if (minimaxScore > alpha){ // this assumes that bestMove is a global variable, and that we can directly access this struct 
					bestMove.score = minimaxScore;	// if (value of minimax, so value of leaf node) is greater than score stored in bestMove, then changes bestMove.score to minimaxScore
		        	alpha = minimaxScore;
		        	if (plyOne == 0){	// if it's the first iteration of the minimax, it will save this array which is the move that the AI could possible make
	        			memcpy (bestMove.board, curr->board, sizeof (IntBoardTemp));
	        			bestMove.startLocation = curr->startLoc;
	        			bestMove.endLocation = curr->endLoc;

	        		}
				}

			curr = curr->next;
		}
		deleteNodeList(nodeList);
		return alpha;
	}
	else { // if it is the enemies turn
		MoveAI(enemyTeam, nodeList, board);
		curr = nodeList->first;
		while (curr){
			if (plyOne == 0){
        		memcpy (IntBoardTemp, curr->board, sizeof (IntBoardTemp));
			}
			minimaxScore = minimax(depth - 1, 1, curr->board, !isMax, alpha, beta, allyTeam, enemyTeam);//recursive function that calls itself with depth+1, and !isMax, so it'll be the max, since we're in the min function
			if (minimaxScore < beta){
				//bestMove.score = minimaxScore;
        		beta = minimaxScore;
        		//memcpy (bestMove.board, IntBoardTemp, sizeof (bestMove.board));
      			// changes board array to IntBoardTemp, which had stored the IntBoard created by the node thta led to this minimaxScore
			}
      		curr = curr->next;
		}
		deleteNodeList(nodeList);
		return beta;
	}
}

//this function is for debugging purposes
void printBestMove(){
	printf("BestMove board:\n[");
	for(int i = 0; i < 64; i++){
		printf("%d, ", bestMove.board[i]);
		if(i % 8 == 7)
			printf("\n");
	}
	printf("]");
}

void printMove(int board[]){
	printf("board:\n[");
	for(int i = 0; i < 64; i++){
		printf("%d, ",board[i]);
		if(i % 8 == 7)
			printf("\n");
	}
	printf("]");
}

void moveRook(int startLocation, NODELIST *nodeList, int board[64]){
	int endLocation = startLocation;
    //Checks Locations going down
    do {
	    endLocation = endLocation + 8;
	    //if a move is legal, then add it to the board
	    if(isLegal(startLocation, endLocation, board) == true)
	       createValidMove(startLocation , endLocation , nodeList, board);
	    //if (isEnemy(startLocation, endLocation, board) == true){
	    //	createValidMove(startLocation , endLocation , nodeList, board);
	    //	break;
	    //}

 	}while(isLegal(startLocation, endLocation, board) == true && isOccupied(endLocation, board) == false);
	endLocation = startLocation;
 
	//Checks Locations going up
	do{
	    endLocation -= 8;
	    //if a move is legal, then add it to the board
	    if(isLegal(startLocation, endLocation, board) == true) {
	        createValidMove(startLocation, endLocation, nodeList, board);
	    }
	}while(isLegal(startLocation, endLocation, board) && isOccupied(endLocation, board) == false);
	endLocation = startLocation;
 
 //Checks Locations going right
 // makes sure that the move is legal and that you arent at the right edge of the board (endLocation % 8 != 0)
 	do{
   		endLocation++;
   //if a move is legal, then add it to the board
   		if(isLegal(startLocation, endLocation, board) && (startLocation % 8) != 7){
       		createValidMove(startLocation , endLocation, nodeList, board);
   		}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 7 && isOccupied(endLocation, board) == false);
 	endLocation = startLocation;

 //Checks Locations going left
 // makes sure that the move is legal and that you arent at the left edge of the board (endLocation % 8 != 1)
 	do{
   		endLocation--;
   //if a move is legal, then add it to the board
   		if(isLegal(startLocation, endLocation, board) && (startLocation % 8) != 0)
       		createValidMove(startLocation , endLocation, nodeList, board);

 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 0 && isOccupied(endLocation, board) == false);
}
/*******************************************/
/**************** BISHOP *******************/
/*******************************************/

void moveBishop(int startLocation, NODELIST *nodeList, int board[64]){
 	int endLocation = startLocation;
 //Checks Locations going up-right
 // makes sure that the move is legal and that you arent at the right edge of the board (endLocation % 8 != 7)
	do {
     endLocation -= 7;
   
     //if a move is legal, then add it to the board
    	if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8) != 7 ) {
        	createValidMove(startLocation , endLocation, nodeList, board);
    	}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 7 && isOccupied(endLocation, board) == false);

 	endLocation = startLocation;
 
 //Checks Locations going up-left
 // makes sure that the move is legal and that you arent at the left edge of the board (endLocation % 8 != 0)
 	do {
   	endLocation -= 9;
   //if a move is legal, then add it to the board
   		if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8) != 0 ) {
       		createValidMove(startLocation , endLocation, nodeList, board);
   		}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 0 && isOccupied(endLocation, board) == false);

 	endLocation = startLocation;
 
 //Checks Locations going down-right
 // makes sure that the move is legal and that you arent at the right edge of the board (endLocation % 8 != 7)
 	do {
   		endLocation += 9;
   //if a move is legal, then add it to the board
   		if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8) != 7 ) {
       		createValidMove(startLocation , endLocation, nodeList, board);
   		}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 7 && isOccupied(endLocation, board) == false);

 	endLocation = startLocation;
 
 //Checks Locations going down-left
 // makes sure that the move is legal and that you arent at the left edge of the board (endLocation % 8 != 0)
 	do {
  		endLocation += 7;
   //if a move is legal, then add it to the board
   		if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8) != 0 ) {
       		createValidMove(startLocation , endLocation, nodeList, board);
   		}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 0 && isOccupied(endLocation, board) == false);
}

/*******************************************/
/**************** KING *******************/
/*******************************************/

void moveKing(int startLocation, NODELIST *nodeList, int board[64]){	
   int endLocation = startLocation;
	
   //Checks Locations going down
   endLocation += 8;
   //if a move is legal, then add it to the board
   if(isLegal(startLocation, endLocation, board) == true) {
       createValidMove(startLocation , endLocation, nodeList, board);
       
   }
   endLocation = startLocation;
 
   //Checks Locations going up
   endLocation -= 8;
   //if a move is legal, then add it to the board
   if(isLegal(startLocation, endLocation, board) == true) {
       createValidMove(startLocation , endLocation, nodeList, board);
       
   }
   endLocation = startLocation;
 
   //Checks Locations going right
   // makes sure that the move is legal and that you arent at the right edge of the board (endLocation % 8 != 0)
   endLocation++;
   //if a move is legal, then add it to the board
   if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 7) {
       createValidMove(startLocation , endLocation, nodeList, board);
       
   }
   endLocation = startLocation;

   //Checks Locations going left
   // makes sure that the move is legal and that you arent at the left edge of the board (endLocation % 8 != 1)
   endLocation--;
   //if a move is legal, then add it to the board
   if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 0) {
       createValidMove(startLocation , endLocation, nodeList, board);
       
   }
   endLocation = startLocation;
 
   //Checks Locations going up-right
   // makes sure that the move is legal and that you arent at the left edge of the board (endLocation % 8 != 1)
   endLocation -= 7;
   //if a move is legal, then add it to the board
   if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 7) {
       createValidMove(startLocation , endLocation, nodeList, board);
       
   }
   endLocation = startLocation;
 
   //Checks Locations going up-left
   // makes sure that the move is legal and that you arent at the left edge of the board (endLocation % 8 != 1)
   endLocation -= 9;
   //if a move is legal, then add it to the board
   if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 0) {
       createValidMove(startLocation , endLocation, nodeList, board);
       
   }
   endLocation = startLocation;
 
   // Checks Locations going down-right
   // makes sure that the move is legal and that you arent at the left edge of the board (endLocation % 8 != 1)
   endLocation += 9;
   //if a move is legal, then add it to the board
   if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 7) {
       createValidMove(startLocation , endLocation, nodeList, board);
       
   }
 
   endLocation = startLocation;
 
   // makes sure that the move is legal and that you arent at the left edge of the board (endLocation % 8 !=  1)
   endLocation += 7;
   //if a move is legal, then add it to the board
   if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 0) {
       createValidMove(startLocation , endLocation, nodeList, board);
       
   }
}

int findKing (int board[64], int startLocation) {

	if (board[startLocation] > 0 && board[startLocation] <= 16){
		for (int i = 0 ; i < 64 ; i++){
			if (board[i] == wK){ //wk = 13
				//printf("wk location: %d", i);
				return i; //returns the position of the king 
			}
		}
	}
	else if (board[startLocation] >= 17 && board[startLocation] <= 32){
		for (int j = 0 ; j < 64 ; j++){
			if (board[j] == bK){ //wk = 29
				//printf("bk location: %d\n", j);
				return j; //returns the position of the king
			}
		}
	}
	else{
		printf ("Error, cannot find king!\n");
		return -1;
	}
}

// This function creates a valid move that will be considered by the AI before it makes a move
void createValidMove (int startLocation, int endLocation, NODELIST *nodeList, int board[64]) {
	//manipulate the board to represent moving a piece
    int boardTemp[64];
    int kingposition;

    for (int i = 0 ; i < 64 ; i++)
    	boardTemp[i] = board[i]; //this creates a temporary array to store the values of the board

 	boardTemp[endLocation] = boardTemp[startLocation];
	boardTemp[startLocation] = 0;
	kingposition = findKing (boardTemp, endLocation); //passes in endLocation after we update the board

	if (isKingInCheckAI(boardTemp, boardTemp[kingposition],kingposition) == 0){

		assert (nodeList);
		Node *n = NULL;
		n = (Node*) malloc (sizeof(Node));
		if (!n) {
			printf("Out of memory! Could not create valid move.\nAborting Game.\n");
			exit(0);
		}
		// make the newly created Node point back to the list of nodes
		n->list = nodeList;
		memcpy (n->board,boardTemp,sizeof(n->board));


		/* this means this is the first element being added*/
		if(nodeList->length == 0){
			//printf("firstelement*****************************************************************************************************************************\n");
			/* Since there is only one element, both first and last pointers should point to the same node*/
			nodeList->first = n;
			nodeList->last = n;
			/* Consequently, they should both be pointing to each other */
			nodeList->first->next = nodeList->first->prev;
			nodeList->first->prev = nodeList->first->next;

			nodeList->length++;
		}else{
			//printf("otherelement**************************************************\n");
			// set it to point to NULL
			n->next = NULL;
			// now the Node's prev pointer points to the end of the list
			n->prev = nodeList->last;
			// set the nodeList's last Node to point to the Node n pointer
			nodeList->last->next = n;
			// update Node *last for the nodeList
			nodeList->last = n;
			// increment its length
			nodeList->length++;
		}
		n->startLoc = startLocation;
		n->endLoc = endLocation;

	}
	else {
	}
	
}

NODELIST *createNodeList(){
	NODELIST *nodeList = NULL;;
	nodeList = (NODELIST*) malloc (sizeof(NODELIST));
	if (!nodeList) {
		printf("Out of memory! Could not create valid move.\n");
		return NULL;
	}
	nodeList->length = 0;
	nodeList->first = NULL;
	nodeList->last = NULL;
	return nodeList; 
}

void deleteNodeList (NODELIST *nodeList){
	assert (nodeList);
	Node *curr = NULL;
	Node *n    = NULL;
	curr = nodeList->first;
	while(curr){
		n = curr->next;
		deleteMove (curr);
		curr = n;
	}
	nodeList->first = NULL; 
	nodeList->last = NULL;

	free (nodeList);
	nodeList = NULL;
}

//This function will deallocate the memory used for possible valid move that is considered by the AI
void deleteMove (Node *node) {
	assert (node);
	node->list = NULL;
	// node->board = NULL;
	node->next = NULL;
	node->prev = NULL;

	free (node);
	node = NULL;
}


// This function evaluates the score of a move by checking the end result of moving the piece to the designated location
int evalscore (int board[64]) {
   	int numWhitePawn = 0;
	int numWhiteRook = 0;
	int numWhiteKnight = 0;
	int numWhiteBishop = 0;
	int numWhiteQueen = 0;
	int numWhiteKing = 0;
	int numBlackPawn = 0;
	int numBlackRook = 0;
	int numBlackKnight = 0;
	int numBlackBishop = 0;
	int numBlackQueen = 0;
	int numBlackKing = 0;
	int score = 0;
	int value;
	for (int i = 0; i < 64; i++){ // goes through the board to find what pieces are alive
	    value = board[i];
	    if (value == 0)		// if empty
	    	score = score;
	    else if(value >= 1 && value <= 8)
			numWhitePawn += 1;
	    else if (value >= 17 && value <= 24)		// if pawn
			numBlackPawn += 1;
	    else if (value == 9 || value == 16)
			numWhiteRook += 1;
	    else if (value == 25 || value == 32)		// if rook
			numBlackRook += 1;	
	    else if (value == 10 || value == 15)
			numWhiteKnight += 1;
	    else if (value == 26 || value == 31)		// if night
	   		numBlackKnight += 1;
	    else if (value == 11 || value == 14)
			numWhiteBishop += 1;
	   	else if (value == 27 || value == 30)
			numBlackBishop += 1;		// if bishop
	   	else if (value == 12) 
			numWhiteQueen += 1;
	   	else if (value == 28)	
			numBlackQueen += 1;				// if queen
	   	else if (value == 13)
			numWhiteKing += 1; 
	   	else if (value == 29)
			numBlackKing += 1;					// if king
	   	else
	    	return -1000000; //error 
	}
	score = 10*(numWhitePawn - numBlackPawn) +	//this score is weighted by the worth of the pieces
		    50*(numWhiteRook - numBlackRook) +
		    30*(numWhiteKnight - numBlackKnight) +
	      	35*(numWhiteBishop - numWhiteBishop) +
	      	90*(numWhiteQueen - numBlackQueen) +
      		1000*(numWhiteKing - numBlackKing) ;
	return score;
}

/* This function will distinguish between pieces and activate the appropriate move function */
void MoveAI(char team[], NODELIST *nodeList, int board[64]){
   int length = 0; // length represents how many units are not captured
   int *teamLocations = findTeam(team, &length, board); // find and store the locations of where the allied units are
   
   for(int i = 0; i < length; i++){
	    int startLocation = teamLocations[i];
	    // the array of stored locations are used to get the value of the current piece
	    int value = board[startLocation];

	    // printf("Value: %d\n", value);
	    // printf("Start Location: %d\n", startLocation);

	    if((value >= 1 && value <= 8) || (value >= 17 && value <= 24))
	        movePawn(startLocation,nodeList, board);
	    else if(value == 9 || value == 16 || value == 25 || value == 32)
	        moveRook(startLocation,nodeList, board);
	    else if(value == 10 || value == 15 || value == 26 || value == 31)
	        moveKnight(startLocation,nodeList, board);
	    else if(value == 11 || value == 14 || value == 27 || value == 30)
	        moveBishop(startLocation,nodeList,board);
	    else if(value == 12 || value == 28)
	        moveQueen(startLocation,nodeList, board);
	    else if(value == 13 || value == 29)
	        moveKing(startLocation,nodeList, board);
	    else{
			printf("%d\n", value);
	        printf("This should never happen! Error Located in MoveAI()\n");
	    }
    }
    //if(nodeList->length == 0)
	//    	printf("Checkmate!>:) %d\n", nodeList->length);
}

// array stores the locations where the allied units are
int * findTeam(char team[], int *length, int board[]){
   static int team_arr[16];
   int k = 0;
	char white[50] = "White";
	char black[50] = "Black";

   for(int i = 0; i < 64; i++){
       if(strcmp(black, team) == 0){              // if AI's team is black
           if(board[i] > 16 && board[i] <= 32){ // once it picks up a black piece
               team_arr[k] = i;
               k++;
           }                     // add its location to the array
       }else if(strcmp(white, team) == 0){        // if AI's team is white
           if(board[i] > 0 && board[i] <= 16){ // once it picks up a white piece
               team_arr[k] = i;
               k++;                     
           }                                        // add its location to the array
       }
   }
   *length = k;
   return team_arr;
}

/* Checks to see that the location is a valid entry within the bound of the array*/
bool isValid(int endLocation){
   if(endLocation >= 0 && endLocation <= 63)
       return true;
   else
       return false;
}

/* Checks to see whether or not a piece is occupying the tile*/
bool isOccupied(int position, int board[]){
   if(board[position] != 0)
       return true; // the position is occupied
   else
       return false; // the position is empty
}

/* Checks to see whether or not the piece is an enemy */
bool isEnemy(int startLocation, int endLocation, int board[]){
    if (board[startLocation] < 0 || board[startLocation] > 64 || board[endLocation] < 0 || board[endLocation] > 64){
        printf ("THIS SHOULD NEVER HAPPEN\n");
        return false;
    }
    else if ( ((board[startLocation] > 0  && board[startLocation] <= 16) && (board[endLocation] > 0  && board[endLocation] <= 16)) ||
            ((board[startLocation] > 16 && board[startLocation] <= 32) && (board[endLocation] > 16 && board[endLocation] <= 32)) ) {
       return false; // the piece at the endLocation is an ally
    }
    else if(board[endLocation] == 0)
        return false; // is an enemy
    else 
    	return true;
}

bool isLegal(int startLocation, int endLocation, int board[]){

   if(isValid(endLocation) == false) {
       //printf("isLegal(). Location: %d is Out of Bounds\n", endLocation);
       return false; // // if target location is not within the board boundaries, then the move is not legal
    }else{
        if (isOccupied(endLocation, board) == false) {
            //printf("isLegal(). Location not occupied\n");
            return true; // if target location is not occupied, then the move is legal
        }else{
            if (isEnemy(startLocation, endLocation, board) == true)
            {
                //printf("isLegal(). Location %d occupied with an enemy\n", endLocation);
                return true; // if target location is occupied, but with an enemy, then the move is legal
            }
            else{
                //printf("isLegal(). Location %d occupied with an ally\n", endLocation);
                return false;// if target location is occupied, but with an ally, then the move is not legal
            }
       }
   }
}

/*******************************************/
/**************** QUEEN *******************/
/*******************************************/

/*moves queen to desired position. prints invalid move when necessary.*/
void moveQueen(int startLocation, NODELIST *nodeList, int board[64]){	
	int endLocation = startLocation;
    //Checks Locations going down
    do {
	    endLocation = endLocation + 8;
	    //if a move is legal, then add it to the board
	    if(isLegal(startLocation, endLocation, board) == true)
	       createValidMove(startLocation , endLocation , nodeList, board); 
 	}while(isLegal(startLocation, endLocation, board) == true && isOccupied(endLocation, board) == false);
	endLocation = startLocation;
 
	//Checks Locations going up
	do{
	    endLocation -= 8;
	    //if a move is legal, then add it to the board
	    if(isLegal(startLocation, endLocation, board) == true) {
	        createValidMove(startLocation, endLocation, nodeList, board);
	    }
	}while(isLegal(startLocation, endLocation, board) && isOccupied(endLocation, board) == false);
	endLocation = startLocation;
 
 	//Checks Locations going right
 	// makes sure that the move is legal and that you arent at the right edge of the board (endLocation % 8 != 0)
 	do{
   		endLocation++;
   		//if a move is legal, then add it to the board
   		if(isLegal(startLocation, endLocation, board) && (startLocation % 8) != 7){
       		createValidMove(startLocation , endLocation, nodeList, board);
   		}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 7 && isOccupied(endLocation, board) == false);
 	endLocation = startLocation;

	 //Checks Locations going left
	// makes sure that the move is legal and that you arent at the left edge of the board (endLocation % 8 != 1)
 	do{
   		endLocation--;
  	 	//if a move is legal, then add it to the board
   		if(isLegal(startLocation, endLocation, board) && (startLocation % 8) != 0)
       		createValidMove(startLocation , endLocation, nodeList, board);

 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 0 && isOccupied(endLocation, board) == false);
	endLocation = startLocation;

	// checks locations going up right
	do {
    	endLocation -= 7;
   
     	//if a move is legal, then add it to the board
    	if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8) != 7 ) {
        	createValidMove(startLocation , endLocation, nodeList, board);
    	}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 7 && isOccupied(endLocation, board) == false);

 	endLocation = startLocation;

 	//checks locations going up left
 	do {
    	endLocation -= 9;
   
     	//if a move is legal, then add it to the board
    	if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8) != 0 ) {
        	createValidMove(startLocation , endLocation, nodeList, board);
    	}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 0 && isOccupied(endLocation, board) == false);

 	endLocation = startLocation;

 	// checks locations going down left
 	do {
    	endLocation += 7;
   
     	//if a move is legal, then add it to the board
    	if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8) != 0 ) {
        	createValidMove(startLocation , endLocation, nodeList, board);
    	}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 0 && isOccupied(endLocation, board) == false);

 	endLocation = startLocation;

 	// checks locations going down right
 	do {
    	endLocation += 9;
   
     	//if a move is legal, then add it to the board
    	if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8) != 7 ) {
        	createValidMove(startLocation , endLocation, nodeList, board);
    	}
 	}while(isLegal(startLocation, endLocation, board) && (endLocation % 8) != 7 && isOccupied(endLocation, board) == false);

}

/*******************************************/
/**************** KNIGHT *******************/
/*******************************************/

void moveKnight(int startLocation, NODELIST *nodeList, int board[64]){	
	int moveCounter, endLocation;
	 
	moveCounter = -17; // moves the knight up 2 spaces and left 1 space 
	endLocation = startLocation + moveCounter;
	if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 0)
	    createValidMove(startLocation , endLocation , nodeList, board);
	 
	moveCounter = -15; // moves the knight up 2 spaces and right 1 space 
	endLocation = startLocation + moveCounter;
	if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 7)
	    createValidMove(startLocation , endLocation , nodeList, board);
	 
	moveCounter = -10; // moves the knight up 1 spaces and left 2 space 
	endLocation = startLocation + moveCounter;
	if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8 != 0 && startLocation % 8 != 1))
	   createValidMove(startLocation , endLocation , nodeList, board);
	 
	moveCounter = -6; // moves the knight up 1 spaces and right 2 space 
	endLocation = startLocation + moveCounter;
	if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8 != 6 && startLocation % 8 != 7))
	    createValidMove(startLocation , endLocation , nodeList, board);	 

	moveCounter = 17; // moves the knight down 2 spaces and right 1 space 
	endLocation = startLocation + moveCounter;
	if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 7)
	    createValidMove(startLocation , endLocation , nodeList, board);
	 
	moveCounter = 15; // moves the knight down 2 spaces and left 1 space 
	endLocation = startLocation + moveCounter;
	if(isLegal(startLocation, endLocation, board) == true && startLocation % 8 != 0)
	    createValidMove(startLocation , endLocation , nodeList, board);
	 
	moveCounter = 10; // moves the knight down 1 spaces and right 2 space 
	endLocation = startLocation + moveCounter;
	if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8 != 6 && startLocation % 8 != 7))
	    createValidMove(startLocation , endLocation , nodeList, board);
	 
	moveCounter = 6; // moves the knight down 1 spaces and left 2 space 
	endLocation = startLocation + moveCounter;
	if(isLegal(startLocation, endLocation, board) == true && (startLocation % 8 != 1 && startLocation % 8 != 0))
	    createValidMove(startLocation , endLocation , nodeList, board);
}

/*******************************************/
/**************** PAWN *******************/
/*******************************************/

void movePawn(int startLocation, NODELIST *nodeList, int board[64]){
   int direction, endLocation; // -1 represents up and 1 represents down
   struct Pieces *piece = &Piece[board[startLocation]];
   
   if(strcmp(piece->color, "White") == 0)
       direction = -1;
   else 
       direction = 1;
    
   /* if the piece is White and in its starting position */    
   if(startLocation >= 48 && startLocation <= 55 && strcmp(piece->color, "White")) {
       endLocation = startLocation + 8*direction;

        if(isValid(endLocation) == true && isOccupied(endLocation, board) == false) {
			createValidMove(startLocation , endLocation , nodeList, board);

			// the 2nd space ahead will only be a legal move if the 1st space ahead is unoccupied.
			endLocation = endLocation + 8;
			if(isValid(endLocation) == true && isOccupied(endLocation, board) == false) {
				
				createValidMove(startLocation , endLocation , nodeList, board);
			}
		}	

    /* if the piece is Black and in its starting position */
    }else if(startLocation >= 8 && startLocation <= 15 && strcmp(piece->color, "Black")) {
        endLocation = startLocation + 8;
        
        // move will be generated if the spot is valid and empty
        if(isValid(endLocation) == true && isOccupied(endLocation, board) == false) {
			
			createValidMove(startLocation , endLocation , nodeList, board);

			// the 2nd space ahead will only be a legal move if the 1st space ahead is unoccupied.
			endLocation += 8;
			if(isValid(endLocation) == true && isOccupied(endLocation, board) == false) {
				
				createValidMove(startLocation , endLocation , nodeList, board);
			}
		}

    }else{
   
	   /* if the pawn is not in its starting position, regardless of team */    
	   endLocation = startLocation + 8*direction;
	   if(isValid(endLocation) == true && isOccupied(endLocation, board) == false){
	   		if (direction == -1) {//if white
	   			if(endLocation >= 0 && endLocation <= 7){
	   				board[endLocation] = wQ;
	    			createValidMove(startLocation , endLocation , nodeList, board);
	    		}
	    		else
	    			createValidMove(startLocation , endLocation , nodeList, board);
	    	}
	    	else {
	    		if (endLocation >= 56 && endLocation <= 63){
	    			board[endLocation] = bQ;
	    			createValidMove(startLocation , endLocation , nodeList, board);
	    		}
	    		else
	    			createValidMove(startLocation , endLocation , nodeList, board);
	    	}
	   }
    }
    
    /* can capture, irregardless of team */
    int diagonalOne = 9;
    endLocation = startLocation + diagonalOne*direction;
    if(direction == 1){ // if black pawn is moving down the board
		if(isLegal(startLocation, endLocation, board) && board[endLocation] != 0 && startLocation % 8 != 7){
	        createValidMove(startLocation , endLocation , nodeList, board);
	    }
	}else{ // white pawn moving up the board, index location decreases
		if(isLegal(startLocation, endLocation, board) && board[endLocation] != 0 && startLocation % 8 != 0){
	        createValidMove(startLocation , endLocation , nodeList, board);
	    }
	}
   
    int diagonalTwo = 7;
    endLocation = startLocation + diagonalTwo*direction;
    if(direction == 1){ // if black pawn is moving down the board
		if(isLegal(startLocation, endLocation, board) && board[endLocation] != 0 && startLocation % 8 != 0){
	        createValidMove(startLocation , endLocation , nodeList, board);
	    }
	}else{ // white pawn moving up the board, index location decreases
		if(isLegal(startLocation, endLocation, board) && board[endLocation] != 0 && startLocation % 8 != 7){
	        createValidMove(startLocation , endLocation , nodeList, board);
	    }
	}
}



int isKingInCheckAI(int board[], int king_value, int position){
	//printf("In isKingInCheckAI, king location: %d. ", position);
	/*asserts that piece is either a white or black king*/
	//assert(king_value == wK || king_value == bK);
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
				}while(board[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[board[i]].color, Piece[king_value].color) != 0) && (board[i] == wKr || board[i] == wQr || board[i] == bKr || board[i] == bQr || board[i] == wQ || board[i] == bQ)){ 
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
				}while(board[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[board[i]].color, Piece[king_value].color) != 0) && (board[i] == wKb || board[i] == wQb || board[i] == bKb || board[i] == bQb || board[i] == wQ || board[i] == bQ)){ 
					return 1;
				}
				/*verifies if a black pawn is putting a white king in check*/
				else if((king_value == wK) && (board[i] >= bp1 && board[i] <= bp8 ) && (position + d_value == i)){
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
				}while(board[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[board[i]].color, Piece[king_value].color) != 0) && (board[i] == wKr || board[i] == wQr || board[i] == bKr || board[i] == bQr || board[i] == wQ || board[i] == bQ)){ 
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
				}while(board[i] == 0);
				/*Verifies if king is in check by a queen or bishop*/
				if((strcmp(Piece[board[i]].color, Piece[king_value].color) != 0) && (board[i] == wKb || board[i] == wQb || board[i] == bKb || board[i] == bQb || board[i] == wQ || board[i] == bQ)){ 
					return 1;
				}
				/*verifies if a white pawn is putting a black king in check*/
				else if((king_value == bK) && (board[i] >= wp1 && board[i] <= wp8 ) && (position + d_value == i)){
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
				}while(board[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[board[i]].color, Piece[king_value].color) != 0) && (board[i] == wKr || board[i] == wQr || board[i] == bKr || board[i] == bQr || board[i] == wQ || board[i] == bQ)){ 
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
				}while(board[i] == 0);
				/*Verifies if king is in check by a queen or bishop*/
				if((strcmp(Piece[board[i]].color, Piece[king_value].color) != 0) && (board[i] == wKb || board[i] == wQb || board[i] == bKb || board[i] == bQb || board[i] == wQ || board[i] == bQ)){ 
					return 1;
				}
				/*verifies if a white pawn is putting a black king in check*/
				else if((king_value == bK) && (board[i] >= wp1 && board[i] <= wp8 ) && (position + d_value == i)){
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
				}while(board[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[board[i]].color, Piece[king_value].color) != 0) && (board[i] == wKr || board[i] == wQr || board[i] == bKr || board[i] == bQr || board[i] == wQ || board[i] == bQ)){ 
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
				}while(board[i] == 0);
				/*Verifies if king is in check at position*/
				if((strcmp(Piece[board[i]].color, Piece[king_value].color) != 0) && (board[i] == wKb || board[i] == wQb || board[i] == bKb || board[i] == bQb || board[i] == wQ || board[i] == bQ)){ 
					return 1;
				}
				/*verifies if a black pawn is putting a white king in check*/
				else if((king_value == wK) && (board[i] >= bp1 && board[i] <= bp8 ) && (position + d_value == i)){
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
				else if((strcmp(Piece[board[knight_position]].color, Piece[king_value].color) != 0) && (board[knight_position] == wKn || board[knight_position] == wQn || board[knight_position] == bKn || board[knight_position] == bQn)){
					return 1;
				}
				break;
			
			case 1:
				knight_position = position - 6;
				if(position <= 7 || position % 8 == 7 || position % 8 == 6){
					break;
				}
				else if((strcmp(Piece[board[knight_position]].color, Piece[king_value].color) != 0) && (board[knight_position] == wKn || board[knight_position] == wQn || board[knight_position] == bKn || board[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 2:
				knight_position = position + 10;
				if(position >= 56 || position % 8 == 7 || position % 8 == 6){
					break;
				}
				else if((strcmp(Piece[board[knight_position]].color, Piece[king_value].color) != 0) && (board[knight_position] == wKn || board[knight_position] == wQn || board[knight_position] == bKn || board[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 3:
				knight_position = position + 17;
				if(position >= 48  || position % 8 == 7){
					break;
				}
				else if((strcmp(Piece[board[knight_position]].color, Piece[king_value].color) != 0) && (board[knight_position] == wKn || board[knight_position] == wQn || board[knight_position] == bKn || board[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 4:
				knight_position = position + 15;
				if(position >= 48 || position % 8 == 0){
					break;
				}
				else if((strcmp(Piece[board[knight_position]].color, Piece[king_value].color) != 0) && (board[knight_position] == wKn || board[knight_position] == wQn || board[knight_position] == bKn || board[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 5:
				knight_position = position + 6;
				if(position >= 56 || position % 8 == 0 || position % 8 == 1){
					break;
				}
				else if((strcmp(Piece[board[knight_position]].color, Piece[king_value].color) != 0) && (board[knight_position] == wKn || board[knight_position] == wQn || board[knight_position] == bKn || board[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 6:
				knight_position = position - 10;
				if(position <= 7 || position % 8 == 0 || position % 8 == 1){
					break;
				}
				else if((strcmp(Piece[board[knight_position]].color, Piece[king_value].color) != 0) && (board[knight_position] == wKn || board[knight_position] == wQn || board[knight_position] == bKn || board[knight_position] == bQn)){
					return 1;
				}
				break;
				
			case 7:
				knight_position = position - 17;
				if(position <= 15 || position % 8 == 0){
					break;
				}
				else if((strcmp(Piece[board[knight_position]].color, Piece[king_value].color) != 0) && (board[knight_position] == wKn || board[knight_position] == wQn || board[knight_position] == bKn || board[knight_position] == bQn)){
					return 1;
				}
				break;
		}
	}
	return 0;
}

int isKingInCheckMateAI(int board[],int king_value, int position){
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
				if(strcmp(Piece[board[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheckAI(board, king_value, i)){
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
				if(strcmp(Piece[board[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheckAI(board, king_value, i)){
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
				if(strcmp(Piece[board[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheckAI(board, king_value, i)){
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
				if(strcmp(Piece[board[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheckAI(board, king_value, i)){
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
				if(strcmp(Piece[board[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheckAI(board, king_value, i)){
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
				if(strcmp(Piece[board[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheckAI(board, king_value, i)){
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
				if(strcmp(Piece[board[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheckAI(board, king_value, i)){
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
				if(strcmp(Piece[board[i]].color, Piece[king_value].color) == 0){ 
					break;
				}
				else if(isKingInCheckAI(board, king_value, i)){
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

int tempCheckMate (int board[], char allyTeam[]){
	char enemyTeam[50];
	if (strcmp ("White",allyTeam)==0)
		strcpy(enemyTeam, "Black");
	else
		strcpy(enemyTeam, "White");

	int IntBoardTemp[64]; // creates the temporary IntBoard to check checkmate of the board
	NODELIST *nodeList = createNodeList();	// this initializes the nodelist, this will check Checkmate by exhausting all possible moves
	Node *curr;
	memcpy (IntBoardTemp, board, sizeof (IntBoardTemp));
	MoveAI(allyTeam, nodeList, board); 					// this will generate the list of possible moves
	curr = nodeList->first;				//sets up the variable for the dynamically allocated array; curr is the first member of the array(nodeList)
	int allyLocation;
	for(int i = 0; i< 64; i++){
		if (strcmp(allyTeam, "Black") == 0){
			if(board[i] > 16 && board[i] <= 32){
				allyLocation = i;
				break;
			}
		}
		else if (strcmp(allyTeam, "White") == 0){
			if(board[i] > 0 && board[i] <= 16){
				allyLocation = i;
				break;
			}
		}
	}

	int kingposition = findKing (board, allyLocation); //passes in endLocation after we update the board

	if (!curr){
		if(isKingInCheckAI(board, board[kingposition], kingposition) == 1){
    		printf("%s King is in Checkmate!\n", allyTeam);
    		printf("%s Player wins!\n", enemyTeam);
    		deleteNodeList(nodeList);
    		return 1;
    	}
    	else if (isKingInCheckAI(board, board[kingposition], kingposition) == 0){
			printf("%s King is in Stalemate.\n", allyTeam);
			printf("Black and White tie.\n");
			deleteNodeList(nodeList);
    		return 2;
    	}
    }
	deleteNodeList(nodeList);
	return 0;
}


