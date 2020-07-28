#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"
#include "ChessPieces.h"
#include "board.h"
#include "User_Move.h"
#include "AI_Move.h"



/* Below is struct array that contains every chess piece present in a game. This array won't be added or subtracted from and works as constant.
My idea is using it to refer the Integer board to build the board in "PrintBoard". Integer board is where all movement and removal of pieces is done,
Simply by rearranging numbers in integer array will move pieces and setting values in array to 0 will remove pieces and generate blank space on board.*/



                                                        

struct sPlayer{

	char color[50];
		

};

typedef struct sPlayer PLAYER;

bool EndGame = false;

int Position();
void PrintBoard(int arr[]);
void PlayerTurn(PLAYER player);
int KingSearch(char player[50]);
int CheckMate;

 /*Writes to LogFile.txt
start_coord, and end_coord are the strings that the user types to move pieces. Do not pass numerical values, pass the strings themselves.
Make sure that you pass the strings after the user has actually made a valid move. You do not want to write invalid moves into the LogFile.txt*/
void logFile(int start_pos, int end_pos){
	FILE * fp;
	char start[2];
	char end[2];
	int i;
	for(i = 0; i < 64; i++){
		if(start_pos == Squares[i].val){
			strcpy(start, Squares[i].sq);
		}
		if(end_pos == Squares[i].val){
			strcpy(end, Squares[i].sq);
		}
	}
	fp = fopen("../bin/LogFile.txt", "a+");
	fprintf(fp, "%s --> %s\n", start, end);
	fclose(fp);
}
 
int main(){
 	memcpy (bestMove.board, IntBoard, sizeof (bestMove.board));
  	bestMove.score = -99999;

	// PLAYER player1 = {"White"};
	// PLAYER player2 = {"Black"};
	PLAYER player1;
	PLAYER player2; // must always be the AI

	int WhiteKing;
	int BlackKing;

	
	bool WhiteCheckFlag = false;
	bool BlackCheckFlag = false;
	bool Winner = false;
	
	int turn;
	int x;
	
	FILE *log;
	log = fopen("../bin/LogFile.txt", "w");
	fclose(log);
//	srand(time(NULL));		//initializing random; no more random
  	
  	printf("\n---------------Welcome to SimuChess v1.0---------------\n");
	PrintBoard(IntBoard);
	printf("---------------Please Select from the available options:---------------\n\nEnter '1' for Player Versus Player      Enter '2' for Player vs Computer\n\n                         Enter '0' to Quit Game\n\n");
	int choice = 0;
  	scanf("%d",&choice);
	
  	while((choice != 0) && (!EndGame)){
  		int input = -1;
    	if(choice == 1){
    		strcpy(player1.color,"White");
	    	strcpy(player2.color,"Black");
	    	for(turn = 0;turn < 500;turn++){
      		
  		  		if ( turn % 2 == 0){
  		  			WhiteCheckFlag = false;
  		  			BlackCheckFlag = false;
  			
					WhiteKing = KingSearch(player1.color);

					if (Winner == true){
						printf("White Player 1 is the Winner!\n\n\n");
					 	Winner = false;
					 	break;
					 }
					// if(WhiteKing == 99){
					// 	printf("Black Player 2 is the Winner!\n\n\n");
					// 	EndGame = true;
					// 	break;
					// }
					

					if(isKingInCheck(wK, KingSearch(player1.color)) == 1){
						printf("White King is in check!\n");
						WhiteCheckFlag = true;
					}

		    		PrintBoard(IntBoard);
		  	  		printf("%s's turn.\n", player1.color);
		    			

		  	  		CheckMate = tempCheckMate (IntBoard, player1.color);
		  	  		if (CheckMate){
		  	  			EndGame = true;
		  	  			break;
		  	  		}



		  			PlayerTurn(player1);
		  			 
					 if (EndGame == true){
					 	Winner = true;	
					 } 

					if (En_Passant_Flag != 0){
		  		  		En_Passant_Flag--;
		  			}

					// if ((WhiteCheckFlag) && (!EndGame))
					// {
					// 	if (isKingInCheckMate(wK, KingSearch(player1.color))){
					// 		printf("Check Mate!\n");
					// 		printf("Black Player 2 is the Winner!\n\n\n");
					// 		EndGame = true;
					// 		break;
					// 	}
					// }	
  	  			}
  		  
  				else if ( turn % 2 == 1){
  					WhiteCheckFlag = false;
  		  			BlackCheckFlag = false;
			
					BlackKing = KingSearch(player2.color);

					 if (Winner == true){
					 	printf("Black Player 2 is the Winner!\n\n\n");
					 	Winner = false;
					 	break;
					 }
					
					// if(BlackKing == 99){
					// 	printf("White Player 1 is the Winner!\n\n\n");
					// 	EndGame = true;
					// 	break;
					// }
					
					if(isKingInCheck(bK, BlackKing) == 1){
						printf("Black King is in check!\n");
						BlackCheckFlag = true;
					
					}
		  
		  			PrintBoard(IntBoard);
		  			printf("%s's turn.\n", player2.color);
		  			
		    		CheckMate = tempCheckMate (IntBoard, player2.color);
		  	  		if (CheckMate){
		  	  			EndGame = true;
		  	  			break;
		  	  		}
		  
		    		PlayerTurn(player2);

					 if (EndGame == true){
					 	Winner = true;
					 } 

		  	  		if (En_Passant_Flag != 0){
		  		  		En_Passant_Flag--;
		  			}

					// if ((BlackCheckFlag) && (!EndGame)){
					// 		if (isKingInCheckMate(bK, KingSearch(player2.color))){
					// 			printf("Check Mate!\n");
					// 			printf("White Player 1 is the Winner!\n\n\n");
					// 			EndGame = true;
					// 			break;
					// 		}
					// }
		  		}
			}
		}
    	else if(choice == 2){
    		int AITurn = 0;
    		/* loop ensures that the user is inputting data correctly when deciding what team the AI shall be */
    		//while (true){

	    	while (input == -1){
	    		printf("What team will the AI be, 1 = Black or 0 = White?\n");
	    		scanf("%d", &input);

	    		if(input == 1){
	    			strcpy(player1.color,"White");
	    			strcpy(player2.color,"Black");

	    		}
	    		else if(input == 0 ){
	    			strcpy(player1.color, "Black");
	    			strcpy(player2.color, "White");
	    			AITurn = 1;

	    		}
	    		else{
	    			printf("Error in input format, try again.");
	    			input = -1;

	    		}
	    	}


	        for(; AITurn < 500;AITurn++){
	      		if (AITurn % 2 == 0){
	      			BlackCheckFlag = false;
  		    		WhiteCheckFlag = false;
		  		    
		  		    /* if player1 is white, else they are black*/
		  		    if(strcmp(player1.color, "White") == 0){
		  		    	WhiteKing = KingSearch(player1.color);
		  		    }
		    		else if (strcmp(player1.color, "Black") == 0){
		    			BlackKing = KingSearch(player1.color);
		    		}

		   //  		if(strcmp(player1.color, "White") == 0){
					// 	if (Winner == true){
					// 		printf("White Player 1 is the Winner!\n\n\n");
					// 		Winner = false;
					// 		break;
					// 	}
					// }else if(strcmp(player1.color, "Black") == 0){
					 	if (Winner == true){
					 		printf("Black Player 1 is the Winner!\n\n\n");
					 		Winner = false;
					 		break;
					 	}
					// }

					if(strcmp(player1.color, "White") == 0){
					// 	if(WhiteKing == 99){
					// 		printf("Black Player 2 is the Winner!\n\n\n");
					// 		EndGame = true;
					// 		break;
						if(isKingInCheck(wK, KingSearch(player1.color)) == 1){
							printf("White King is in check!\n");
							WhiteCheckFlag = true;
						}
					}else if(strcmp(player1.color, "Black") == 0){
					// 	if(BlackKing == 99){
					// 		printf("White Player 2 is the Winner!\n\n\n");
					// 		EndGame = true;
					// 		break;
						if(isKingInCheck(bK, KingSearch(player1.color)) == 1){
							printf("Black King is in check!\n");
							BlackCheckFlag = true;
						}
					}
					
		    		PrintBoard(IntBoard);
		  	  		printf("%s's turn.\n", player1.color);
			    			
					CheckMate = tempCheckMate (IntBoard, player1.color);
			  	  		if (CheckMate){
			  	  			EndGame = true;
			  	  			break;
			  	  		}
		  			PlayerTurn(player1);
		  			  /* Every turn EnPassantFlag decremented till it becomes zero. In EnPassant() it increases to 2 for activation and gives other player 1 turn to perform if not the right is lost*/
		  			
					 if (EndGame == true){
					 	Winner = true;
						
					 } 

					if (En_Passant_Flag != 0){
		  		  		En_Passant_Flag--;
		  			}

		  	// 		if(strcmp(player1.color, "White") == 0){
					// 	if ((WhiteCheckFlag) && (!EndGame))
					// 	{
					// 		if (isKingInCheckMate(wK, KingSearch(player1.color))){
					// 			printf("Check Mate!\n");
					// 			printf("Black Player 2 is the Winner!\n\n\n");
					// 			EndGame = true;
					// 			break;
					// 		}
					// 	}
					// }
					// else if(strcmp(player1.color, "Black") == 0){
					// 	if ((BlackCheckFlag) && (!EndGame))
					// 	{
					// 		if (isKingInCheckMate(bK, KingSearch(player1.color))){
					// 			printf("Check Mate!\n");
					// 			printf("White Player 2 is the Winner!\n\n\n");
					// 			EndGame = true;
					// 			break;
					// 		}
					// 	}
					// }
  	  		
  				}
  		    	else if ( AITurn % 2 == 1){
  		    		BlackCheckFlag = false;
  		    		WhiteCheckFlag = false;
  					/* if player2 is white, else they are black*/
		  		    if(strcmp(player2.color, "White") == 0){
	    				WhiteKing = KingSearch(player2.color);
		  		    }
		    		else if(strcmp(player2.color, "Black") == 0){
		    			BlackKing = KingSearch(player2.color);
		    		}
					// BlackKing = KingSearch(player2.color);

					// if(strcmp(player1.color, "White") == 0){
						if (Winner == true){
							printf("White Player 2 is the Winner!\n\n\n");
					 		Winner = false;
					 		break;
					 	}

					// }else if(strcmp(player1.color, "Black") == 0){
					// 	if (Winner == true){
					// 		printf("Black Player 2 is the Winner!\n\n\n");
					// 		Winner = false;
					// 		break;
					// 	}
					// }
					// if(strcmp(player2.color, "White") == 0){
					// 	if(WhiteKing == 99){
					// 		printf("Black Player 1 is the Winner!\n\n\n");
					// 		EndGame = true;
					// 		break;
					if(strcmp(player2.color, "White") == 0){
						if(isKingInCheck(wK, KingSearch(player2.color)) == 1){
								printf("White King is in check!\n");
								WhiteCheckFlag = true;
							}
					}else {
						if(isKingInCheck(bK, KingSearch(player2.color)) == 1){
								printf("Black King is in check!\n");
								BlackCheckFlag = true;
							}
					}
		  
	  			  	PrintBoard(IntBoard);
	  			    printf("%s's turn.\n", player2.color);
	  			
	    			// if (En_Passant_Flag == 1)
	  	  		// 		printf("* En Passant is available\n");

				    int alpha = -9999;
	  				int beta = 9999;   

	  				CheckMate = tempCheckMate (IntBoard, player2.color);
			  	  	if (CheckMate){
			  	  		EndGame = true;
			  	  		break;
			  	  	}

					x = minimax(3, 0, IntBoard, 1, alpha, beta, player2.color, player1.color); //depth - plyone - board - ismax - alpha - beta
			
					//printf("score of minimax = %d", x);
					//printBestMove();
			      	memcpy(IntBoard, bestMove.board, sizeof (IntBoard));
			      	bestMove.score = -9999;
					logFile(bestMove.startLocation, bestMove.endLocation);
		  	  		
		  	  		if (En_Passant_Flag != 0){
		  		  		En_Passant_Flag--;
		  			}
					 if (EndGame == true){
					 	Winner = true;
					 } 


					// if(strcmp(player2.color, "White") == 0){
					// 	if ((WhiteCheckFlag) && (!EndGame))
					// 	{
					// 		if (isKingInCheckMate(wK, KingSearch(player2.color))){
					// 			printf("Check Mate!\n");
					// 			printf("Black Player 1 is the Winner!\n\n\n");
					// 			EndGame = true;
					// 			break;
					// 		}
					// 	}
					// }
					// else if(strcmp(player2.color, "Black") == 0){
					// 	if ((BlackCheckFlag) && (!EndGame))
					// 	{
					// 		if (isKingInCheckMate(bK, KingSearch(player2.color))){
					// 			printf("Check Mate!\n");
					// 			printf("White Player 1 is the Winner!\n\n\n");
					// 			EndGame = true;
					// 			break;
					// 		}
					// 	}
					

		  		}
		  	}
		}

    
	    EndGame = false;
	    memcpy (IntBoard, reIntBoard, sizeof (IntBoard));
	    printf("---------------Please Select from the available options:---------------\n\nEnter '1' for Player Versus Player      Enter '2' for Player vs Computer\n\n                         Enter '0' to Quit Game\n\n");
	    scanf("%d",&choice);	
	  	}
  
  	printf("---------------Thank you for playing SimuChess!---------------\n");
}

int KingSearch(char player[50]){
	
int KingInReference;

	if (strcmp("White",player) == 0){
		
		KingInReference = wK;
	}

	if (strcmp("Black",player) == 0){
		
		KingInReference = bK;
	}	
		
	for (int i=0; i<64 ; i++){    // runs through Spaces[] which is array of every space on board
		

		if (IntBoard[i] == KingInReference){     // search for space on board with king in consideration
			return i;                       // value of the space that holds king is returned
		}
 		
	}
	

	return 99;
}

void PlayerTurn (PLAYER player){

int PieceSpace;
int MoveSpace;
int ChessPiece;
int MovePiece;
int ErrorInvalidInput = 0; //If player tries to move opponents piece or tries to capture her own piece, error triggers.Let's player select move again.
int ErrorInvalidMove = 0; // If move is invalid, the player gets to select a move again
int PieceVal;

do{ // while (ErrorInvalidMove). Lets player select piece and move again
	do{ //while(ErrorInvalidInput). Lets player select piece and move again
		do{ //while (ErrorInvalidInput). Lets player select piece again.
			printf("Select piece to move: ");
	
			PieceSpace = Position();
			printf("\n");

			ChessPiece = IntBoard[PieceSpace];	//The value of the piece in IntBoard is the position of that piece in Piece array (the struct array)
			
			if (EndGame == true){
			
				printf("%s player has ended game\n", player.color);
				break;

			}
			else if (strcmp(Piece[ChessPiece].color, player.color) != 0){
		
				ErrorInvalidInput = 1;
				printf("Invalid Move: Cannot move that piece.\n"); //ralph:changed "opponents" to "that"
			}
	
			else{
				ErrorInvalidInput = 0;
			}

		}while (ErrorInvalidInput);

	
		
		if (EndGame == true){
			break;
		}

		printf("Select space to move to: ");
	
		MoveSpace = Position();
		printf("\n");

		MovePiece = IntBoard[MoveSpace];	//The value of the piece in IntBoard is the position of that piece in Piece array (the struct array)
		
		if (strcmp(Piece[MovePiece].color, player.color) == 0){
		
			ErrorInvalidInput = 1;
			printf("Invalid Move: Ally piece occupies space.\n");
		}
	
		else{
			ErrorInvalidInput = 0;
		}

	}while (ErrorInvalidInput);
	
	if (EndGame == true){
		break;
		}

	PieceVal = IntBoard[PieceSpace];

	if(((PieceVal>0) && (PieceVal<9)) || ((PieceVal>16) && (PieceVal<25))){
		
		printf("Moving Pawn.\n");
		if(MovePawn(PieceSpace,MoveSpace,IntBoard)){
			ErrorInvalidMove = 1;
		}
		else{
			logFile(PieceSpace, MoveSpace);
			ErrorInvalidMove =0;
		}
	}

	else if((PieceVal==wQn) || (PieceVal==wKn) || (PieceVal==bQn) || (PieceVal==bKn)){
		
		printf("Moving Knight.\n");
		if(MoveKnight(PieceSpace,MoveSpace,IntBoard)){
			ErrorInvalidMove = 1;
		}
		else{
			logFile(PieceSpace, MoveSpace);
			ErrorInvalidMove =0;
		}
	}

	else if((PieceVal==wQb) || (PieceVal==wKb) || (PieceVal==bQb) || (PieceVal==bKb)){
		
		printf("Moving Bishop.\n");
		if(MoveBishop(PieceVal, IntBoard, PieceSpace, MoveSpace)){
			ErrorInvalidMove = 1;
		}
		else{
			logFile(PieceSpace, MoveSpace);
			ErrorInvalidMove =0;
		}
	}

	else if((PieceVal==wQr) || (PieceVal==wKr) || (PieceVal==bQr) || (PieceVal==bKr)){
		
		printf("Moving Rook.\n");
		if(MoveRook(PieceVal, IntBoard, PieceSpace, MoveSpace)){
			ErrorInvalidMove = 1;
		}
		else{
			logFile(PieceSpace, MoveSpace);
			ErrorInvalidMove =0;
		}
	}
	
	else if((PieceVal==wQ) || (PieceVal==bQ)){
		
		printf("Moving Queen.\n");
		if(MoveQueen(PieceVal, IntBoard, PieceSpace, MoveSpace)){
			ErrorInvalidMove = 1;
		}
		else{
			logFile(PieceSpace, MoveSpace);
			ErrorInvalidMove =0;
		}
	}

	else if((PieceVal==wK) || (PieceVal==bK)){
		
		printf("Moving King.\n");
		if(MoveKing(PieceSpace,MoveSpace,IntBoard)){
			ErrorInvalidMove = 1;
		}
		else{
			logFile(PieceSpace, MoveSpace);
			ErrorInvalidMove =0;
		}
	}
	
}while(ErrorInvalidMove);
}




int Position(){
		
                // will hold value of space on board to then reference back to IntBoard[]
char user[50];          // user inout ex"a8"
int Error = 0;


scanf("%s",user); 

if(strcmp(user, "!q") == 0){	
	
	EndGame = true;
	return 0;
}

	for (int i=0; i<64 ; i++){    // runs through Spaces[] which is array of every space on board
		

		if (strcmp(user,Squares[i].sq) == 0){     // compares user input with spaces and returns 0 if they are equal
			Error++;
			return i;                       // value of the space to be used as PieceOnIntBOard parameter's
		}
 		
		}

	printf("Space does not exist\n");
	printf("Please reenter: ");
	


	return 0;
                   
}     
		





	


void PrintBoard(int arr[]){

int sq =0;                                           // position on board EX "a8", uses formula y+(x*8) to run through 1D arrayand generate 1 row at a time   
int ValueOfSq = 0;                                   /* gets set equal IntegerBoard[sq] which generates the value that is associated with space on board.
							This will be used to refer to the Pieces Piece[] array.*/ 

printf("\n");

for (int x = 0; x < 8; x++){ 
	
	printf("     +-----+-----+-----+-----+-----+-----+-----+-----+\n");   // Print statesment are just art to generate board
    printf("  %d",(8-x));
	printf("  |");                       
	
	for(int y = 0; y < 8; y++){
		
		if(y != 0){
			printf("|");
                }

		sq = y+(x * 8);                                 
		ValueOfSq = arr[sq];
		
		
		
			if(ValueOfSq == 0){                       
			printf("    ");
			}
			
			else{
				for (int z = 0; z < 33; z++){  
				
					if (ValueOfSq == Piece[z].value){
						printf(" %s ",Piece[z].name);
					

					}
				}		
			}
		
			printf(" ");
	}
			printf("|");
			printf("\n");
}
			printf("     +-----+-----+-----+-----+-----+-----+-----+-----+\n");
			printf("        a     b     c     d     e     f     g     h");
			printf("\n");

}
