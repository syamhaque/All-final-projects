#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "ChessPieces.h"
#include "constants.h"
#include "User_Move.h"

//included AI_Move.h to allow some functions like findKing and isKingInCheckAI
#include "AI_Move.h"
#include "board.h"

struct Pieces Piece[33] = {{0,"None", "Nothing",0},
			   {1,"White","wP",1},{2,"White","wP",1},{3,"White","wP",1},         
			   {4,"White","wP",1},{5,"White","wP",1},{6,"White","wP",1},
			   {7,"White","wP",1},{8,"White","wP",1},
			   {9,"White","wR",1},{10,"White","wN",1},{11,"White","wB",1},
			   {12,"White","wQ",1},{13,"White","wK",1},{14,"White","wB",1},
			   {15,"White","wN",1},{16,"White","wR",1},
			   {17,"Black","bP",1},{18,"Black","bP",1},{19,"Black","bP",1},
			   {20,"Black","bP",1},{21,"Black","bP",1},{22,"Black","bP",1},
			   {23,"Black","bP",1},{24,"Black","bP",1},
			   {25,"Black","bR",1},{26,"Black","bN",1},{27,"Black","bB",1},
			   {28,"Black","bQ",1},{29,"Black","bK",1},{30,"Black","bB",1},
			   {31,"Black","bN",1},{32,"Black","bR",1}};

int En_Passant_Flag = 0;

int En_Passant_Square = 99;

char white[50] = "White";
char black[50] = "Black";



int PiecePosition(int ValueofSpace){

int i;
int x;
	for(x=0;x<33;x++){
		
			if(ValueofSpace == Piece[x].value){
				i=x;
				return i;
			}
	}
	return 99;
}

int enPassant(int piece, int Space){ //returns 0 if error


		int enPassantSpace = Space;
		
	
	En_Passant_Flag +=2;
	return enPassantSpace;
}

void PawnPromotion(int PawnSpace,int board[]){
	
	printf("Pawn to be Promoted....\n");
	int InvalidEntry;
	char user[50];   

	int BlackPromo = 0;
	int WhitePromo = 0;

	do{

	InvalidEntry = 0;

	if(PawnSpace > 55){
	
		printf("bQ - Black Queen \nbR - Black Rook \nbN - Black Knight \nbB - Black Bishop\n");
		BlackPromo++;

	}
	else if (PawnSpace < 8){

		printf("wQ - White Queen \nwR - White Rook \nwN - White Knight \nwB - White Bishop\n");
		WhitePromo++;
	}

	printf("Enter the 2-letter tag associated with piece: ");
	       

	scanf("%s",user); 

	if ((strcmp(user,"wQ") == 0) && (WhitePromo == 1)){
		
		board[PawnSpace] = wQ;
	}
	else if ((strcmp(user,"bQ") == 0)&& (BlackPromo == 1)){
		
		board[PawnSpace] = bQ;
	}
	else if ((strcmp(user,"wR") == 0) && (WhitePromo == 1)){
		
		board[PawnSpace] = wQr;
	}
	else if ((strcmp(user,"bR") == 0) && (BlackPromo == 1)){
		
		board[PawnSpace] = bQr;
	}
	else if ((strcmp(user,"wN") == 0) && (WhitePromo == 1)){
		
		board[PawnSpace] = wQn;
	}
	else if ((strcmp(user,"bN") == 0)&& (BlackPromo == 1)){
		
		board[PawnSpace] = bQn;
	}
	else if ((strcmp(user,"wB") == 0) && (WhitePromo == 1)){
		
		board[PawnSpace] = wQb;
	}
	else if ((strcmp(user,"bB") == 0) && (BlackPromo == 1)){
		
		board[PawnSpace] = bQb;
	}
	else{
		printf("Invalid Entry.\n");
		InvalidEntry++;
	}
	
	}while(InvalidEntry == 1);
							
}
	
		
/*Moves Pawn. Returns 0 if no error. Returns -10 if invalid move*/
int MovePawn(int PieceSq,int MoveSq,int board[]){  // PieceSq is the square that contains the piece the user wants to move, 
					 // MoveSq is the square that user inputs for where piece will move

	//stuff ralph added to try to check check
	int boardTemp[64];
	memcpy (boardTemp, board, sizeof (boardTemp)); //stores the board into a temporary board to save it
	int kingposition = findKing (board, PieceSq); //finds the position of the king to check check
	int kingvalue = boardTemp[kingposition];     //stores the value of which king depending on the startLocation provided by kingposition

int jump;
int dblJump;
int rightDiag;
int leftDiag;
int jumpOK = 0;
int moveOK =0;
int rightDiagOK =0;
int leftDiagOK =0;
int pawn = board[PieceSq];
int En_Passant_Sq; // this variable is used to identify the space where EnPassant happens depending on Player(Black and White)
int PromotionFLAG = 0;
//This sets up either side of board
	int PosofPiece = PiecePosition(pawn); //this is piece user selected. 

/* Determines direction of movement */
	
	if (strcmp(white,Piece[PosofPiece].color) == 0){
		jump = PieceSq - 8;
		dblJump = PieceSq - 16;
		rightDiag = PieceSq - 7;
		leftDiag = PieceSq - 9;
		En_Passant_Sq = En_Passant_Square - 8;
		
		if(MoveSq < 8){
			PromotionFLAG++;
		}

		}

	if (strcmp(black,Piece[PosofPiece].color) == 0){
		jump = PieceSq + 8;
		dblJump = PieceSq + 16;
		rightDiag = PieceSq + 7;
		leftDiag = PieceSq + 9;
		En_Passant_Sq = En_Passant_Square + 8; 
		
		if(MoveSq > 55){
			PromotionFLAG++;
		}

		}	



int rhtDiagPiece = board[rightDiag];  // these are used to confirm we aren't capturing ally pieces
int lftDiagPiece = board[leftDiag];
	
	/*Checks if pawn already moves so that it can no longer move 2 spaces*/
	if((strcmp(white,Piece[PosofPiece].color) == 0 && PieceSq < 48) || (strcmp(black,Piece[PosofPiece].color) == 0 && PieceSq > 15)){
		Piece[PosofPiece].Pawnflag = 0; // this is done because the moment pawn makes movement it can't move 2 spots anymore
	}
	
	/* Sets flags for the four possible movements */
	
		if ((board[jump] == 0) && (board[dblJump] == 0) && (Piece[PosofPiece].Pawnflag == 1)){          // what i need is that pawn hasn't moved, so can't i just use OG postion, but also that space in front is not occupied
			
			jumpOK++; // this checks if this movement follows chess rules then it unlocks another if statement
		}
		
		if(board[jump] == 0){                // if square in front is free
			
			moveOK++;
			
		}
		/* for capturing, if right diagonal space is not empty you can move and capture piece or if EnPassant flag greater than 0 then you move onto empy space and capture*/
		if ((board[rightDiag] != 0) || ((En_Passant_Flag != 0) && (MoveSq==En_Passant_Sq))) {       
			
			rightDiagOK++;
			rhtDiagPiece = PiecePosition(board[rightDiag]);
			
		}
		/* for capturing, if rleft diagonal space is not empty you can move and capture piece or if EnPassant flag greater than 0 then you move onto empy space and capture*/

		if( (board[leftDiag] != 0) || ((En_Passant_Flag != 0) && (MoveSq==En_Passant_Sq))) {	  
			
			leftDiagOK++;
			lftDiagPiece = PiecePosition(board[leftDiag]);

			
		}

		

			/* Matches users input for movement with viable moves */
			
			if((jumpOK ==1) && (MoveSq == dblJump)){  //if dblJump possible and if user input equals the square 2 spaces above then movement happens 
				
				board[MoveSq] = board[PieceSq];      // sets new position value to old position, thus copying piece
				board[PieceSq] = 0;			    // sets old space to 0 so its empty, thus deleting leftover pawn and completing movement
				
				/*En Passat is active and I add the piece and location to enpassat function. */
				En_Passant_Square = enPassant(PosofPiece, MoveSq);
			}
			
			else if((moveOK == 1) && (MoveSq == jump)){ // if move (1 space above) possible and if user input equals 1 space above
			
				board[MoveSq] = board[PieceSq];     
				board[PieceSq] = 0;

				if(PromotionFLAG == 1){
					PawnPromotion(MoveSq,board);
					if (isKingInCheckAI (board, kingvalue, kingposition) == 1) {
						memcpy (IntBoard, boardTemp, sizeof (IntBoard));
						printf ("Invalid Move: must move King out of check\n");
						return -100;
					}	
				}
				
			}

			else if((rightDiagOK == 1) && (MoveSq == rightDiag) && (strcmp(Piece[PosofPiece].color,Piece[rhtDiagPiece].color))){ 

				board[MoveSq] = board[PieceSq];  // captures by setting array value to pawn value
				board[PieceSq] = 0;
                                  
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
				if((En_Passant_Flag > 0) && (En_Passant_Square < 64) && (MoveSq != En_Passant_Square)){ // only activates if flag is enabled and if EnPassantSq is within range to avoid seg fault
				
					board[En_Passant_Square] = 0;
				}
				
				if(PromotionFLAG == 1){
					 PawnPromotion(MoveSq,board);
					 if (isKingInCheckAI (board, kingvalue, kingposition) == 1) {
						memcpy (IntBoard, boardTemp, sizeof (IntBoard));
						printf ("Invalid Move: must move King out of check\n");
						return -100;
					}	
				}					

			}

			else if((leftDiagOK == 1) && (MoveSq == leftDiag) && (strcmp(Piece[PosofPiece].color,Piece[lftDiagPiece].color))){

				board[MoveSq] = board[PieceSq];	// captures but setting array value to pawn value
				board[PieceSq] = 0;
				
				if((En_Passant_Flag > 0) && (En_Passant_Square < 64)&& (MoveSq != En_Passant_Square)){ // only activates if flag is enabled and if EnPassantSq is within range to avoid seg fault
				
					board[En_Passant_Square] = 0;
					printf("%d\n",En_Passant_Square);
				}

				if(PromotionFLAG == 1){
					 PawnPromotion(MoveSq,board);
					 if (isKingInCheckAI (board, kingvalue, kingposition) == 1) {
						memcpy (IntBoard, boardTemp, sizeof (IntBoard));
						printf ("Invalid Move: must move King out of check\n");
						return -100;
					}	
				}
			}
			
			else{

				printf("Invalid movement.\n");
				return -10;
			}
if (isKingInCheckAI (board, kingvalue, kingposition) == 1) {
	memcpy (IntBoard, boardTemp, sizeof (IntBoard));
	printf ("Invalid Move: must move King out of check\n");
	return -100;
}
return 0;
}
/*Moves Knight. Returns 0 if no error. Returns -10 if Invalid Move.*/
// PieceSq is the position of the knight, MoveSq is the position to move to
int MoveKnight (int PieceSq,int MoveSq, int board[]){
int Upperlft = PieceSq - 17;
int Upperrht = PieceSq - 15;
int Uprht = PieceSq - 6;
int Uplft = PieceSq - 10;
int Lowlft = PieceSq + 6;
int Lowrht = PieceSq + 10;
int Lowerlft = PieceSq + 15; 
int Lowerrht = PieceSq + 17;
int UperlftOK = 0;
int UperrhtOK =0;
int UprhtOK =0;
int UplftOK =0;
int LolftOK = 0;
int LorhtOK = 0;
int LoerlftOK =0;
int LoerrhtOK =0;
int knight = board[PieceSq];

	//stuff ralph added to try to check check
	int boardTemp[64];
	memcpy (boardTemp, board, sizeof (boardTemp)); //stores the board into a temporary board to save it
	int kingposition = findKing (board, PieceSq); //finds the position of the king to check check
	int kingvalue = boardTemp[kingposition];     //stores the value of which king depending on the startLocation provided by kingposition

//This a link to the struct of piece player selected
	int PosofPiece = PiecePosition(knight); //this is piece user selected. 


/* Below are int values that connect a space on board to the chess piece, thus allowing me to access chess pieces individually*/

int UpperlftPiece = PiecePosition(board[Upperlft]);
int UpperrhtPiece = PiecePosition(board[Upperrht]);
int UprhtPiece = PiecePosition(board[Uprht]);
int UplftPiece = PiecePosition(board[Uplft]);
int LowlftPiece = PiecePosition(board[Lowlft]);
int LowrhtPiece = PiecePosition(board[Lowrht]);
int LowerlftPiece = PiecePosition(board[Lowerlft]);
int LowerrhtPiece = PiecePosition(board[Lowerrht]);



	/* Sets flags for the 8 possible movements, confirms position is within range and confirms that if another piece is on space that it is not ally */
	
		if ((Upperlft < 64) && (Upperlft > 0) && (strcmp(Piece[PosofPiece].color,Piece[UpperlftPiece].color))){         
			
			UperlftOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
		
		if ((Upperrht < 64) && (Upperrht > 0) && (strcmp(Piece[PosofPiece].color,Piece[UpperrhtPiece].color))){           
			
			UperrhtOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
		
		if ((Uprht < 64) && (Uprht > 0) && (strcmp(Piece[PosofPiece].color,Piece[UprhtPiece].color))){        
			
			UprhtOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}

		if ((Uplft < 64) && (Uplft > 0) && (strcmp(Piece[PosofPiece].color,Piece[UplftPiece].color))){         
			
			UplftOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}		
		
		if ((Lowlft < 64) && (Lowlft > 0) && (strcmp(Piece[PosofPiece].color,Piece[LowlftPiece].color))){        
			
			LolftOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
		
		if ((Lowrht < 64) && (Lowrht > 0) && (strcmp(Piece[PosofPiece].color,Piece[LowrhtPiece].color))){         			
			LorhtOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
	
		if ((Lowerlft < 64) && (Lowerlft > 0) && (strcmp(Piece[PosofPiece].color,Piece[LowerlftPiece].color))){          			
			LoerlftOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
		
		if ((Lowerrht < 64) && (Lowerrht > 0) && (strcmp(Piece[PosofPiece].color,Piece[LowerrhtPiece].color))){           			
			LoerrhtOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}


		/* Matches users input for movement with valid moves based on flags */
			
			if((UperlftOK ==1) && (MoveSq == Upperlft)){  				
				board[MoveSq] = board[PieceSq];      
				board[PieceSq] = 0;			    
			}
			
			else if((UperrhtOK == 1) && (MoveSq == Upperrht)){ // if move (1 space above) possible and if user input equals 1 space above
				
				board[MoveSq] = board[PieceSq];     
				board[PieceSq] = 0;
				
			}

			else if((UprhtOK == 1) && (MoveSq == Uprht)){ 

				board[MoveSq] = board[PieceSq];  // captures by setting array value to pawn value
				board[PieceSq] = 0;

			}

			else if((UplftOK == 1) && (MoveSq == Uplft)){

				board[MoveSq] = board[PieceSq];	// captures but setting array value to pawn value
				board[PieceSq] = 0;

			}
	
			else if((LolftOK == 1) && (MoveSq == Lowlft)){ // if move (1 space above) possible and if user input equals 1 space above
				
				board[MoveSq] = board[PieceSq];     
				board[PieceSq] = 0;
				
			}

			else if((LorhtOK == 1) && (MoveSq == Lowrht)){ 

				board[MoveSq] = board[PieceSq];  // captures by setting array value to pawn value
				board[PieceSq] = 0;

			}

			else if((LoerlftOK == 1) && (MoveSq == Lowerlft)){

				board[MoveSq] = board[PieceSq];	// captures but setting array value to pawn value
				board[PieceSq] = 0;

			}
			
			else if((LoerrhtOK == 1) && (MoveSq == Lowerrht)){

				board[MoveSq] = board[PieceSq];	// captures but setting array value to pawn value
				board[PieceSq] = 0;

			}

			
			else{

				printf("Invalid movement.\n");
				return -10;
			}
if (isKingInCheckAI (board, kingvalue, kingposition) == 1) {
	memcpy (IntBoard, boardTemp, sizeof (IntBoard));
	printf ("Invalid Move: must move King out of check\n");
	return -100;
}
return 0;
}


//returns PossibleCastle if castle possible or returns 0 if not at all.
int castle( int ChessPiece, int board[]){  

//int King = board[PieceSq];

//White right castling return 1, white left castling return 2, if both return 3. Black right castling return -1, black left castling return -2, if both return -3.
int PossibleCastle = 0; 

// White side, right castle
int KingF1_OK;
int KingG1_OK;

// White side, left castle
int KingD1_OK;
int KingC1_OK;

// Black side, right castle
int KingF8_OK;
int KingG8_OK;

// Black side, left castle
int KingD8_OK;
int KingC8_OK;




	if (strcmp(white,Piece[ChessPiece].color) == 0){
		
		if ((board[h1] == wKr) && (board[e1] == wK) && (board[f1] == 0) && (board[g1]==0)){
			
			KingF1_OK = isKingInCheck(wK, f1);
			KingG1_OK = isKingInCheck(wK, g1);
			
			if ((KingF1_OK == 0) && (KingG1_OK == 0)){
				PossibleCastle++;
			}
			
		}
		
		else if ((board[a1] == wQr) && (board[e1] == wK) && (board[b1] == 0) && (board[c1]==0) && (board[d1]==0)){
			
			KingD1_OK = isKingInCheck(wK, d1);
			KingC1_OK = isKingInCheck(wK, c1);
			
			if ((KingD1_OK == 0) && (KingC1_OK == 0)){
				PossibleCastle += 2;
			}

		return PossibleCastle;
		}
	}
	if (strcmp(black,Piece[ChessPiece].color) == 0){

		if ((board[h8] == bKr) && (board[e8] == bK) && (board[f8] == 0) && (board[g8]==0)){
			
			KingF8_OK = isKingInCheck(bK, f8);
			KingG8_OK = isKingInCheck(bK, g8);
			
			if ((KingF8_OK == 0) && (KingG8_OK == 0)){
				PossibleCastle--;
			}
			
		}
		
		else if ((board[a8] == bQr) && (board[e8] == bK) && (board[b8] == 0) && (board[c8]==0) && (board[d8]==0)){
			
			KingD8_OK = isKingInCheck(bK, d8);
			KingC8_OK = isKingInCheck(bK, c8);
			
			if ((KingD8_OK == 0) && (KingC8_OK == 0)){
				PossibleCastle -= 2;
				
			}
			return PossibleCastle;
		}
		
	
	}
	// if above conditions not met then 0 is returned meaning castling not possible. 
	return PossibleCastle;
}


int MoveKing (int PieceSq,int MoveSq, int board[]){

/* Below are values that represent the square of movements around the king*/
int Uplft = PieceSq - 7;
int Up = PieceSq - 8;
int Uprht = PieceSq - 9;
int lft = PieceSq - 1;
int rht = PieceSq + 1;
int Dwnlft = PieceSq + 7;
int Dwn = PieceSq + 8;
int Dwnrht = PieceSq + 9;
/* flags to be set to 1 if move follows rules, can't move onto ally occupied spot and can check oneself*/
int UplftOK = 0;
int UpOK =0;
int UprhtOK =0;
int lftOK =0;
int rhtOK = 0;
int DwnlftOK = 0;
int DwnOK =0;
int DwnrhtOK =0;
int King = board[PieceSq];




//This a link to the struct of piece player selected
	int PosofPiece = PiecePosition(King); //this is piece user selected. 

//Below are the castle flags
int Castling;
int WhiteCastleRht_OK = 0;
int WhiteCastleLft_OK = 0;
int BlackCastleRht_OK = 0;
int BlackCastleLft_OK = 0;


Castling = castle(PosofPiece, board);
printf("%d\n", Castling);

//Below is if statesments that depending on castle(int ChessPiece, int board[]) will set them = 1 meaning movement is possible
//White side castling flags
if (Castling == 1){
	
	WhiteCastleRht_OK++;
}

else if (Castling == 2){
	
	WhiteCastleLft_OK++;
}

else if (Castling == 3){
	
	WhiteCastleRht_OK++;
	WhiteCastleLft_OK++;
}

//Black side castling flags
if (Castling == -1){
	
	BlackCastleRht_OK++;
}

else if (Castling == -2){
	
	BlackCastleLft_OK++;
	
}

else if (Castling == -3){
	
	BlackCastleRht_OK++;
	BlackCastleLft_OK++;
}
	
	

/* Below are int values that connect a space on board to the chess piece, thus allowing me to access chess pieces individually*/

int UplftPiece = PiecePosition(board[Uplft]);
int UpPiece = PiecePosition(board[Up]);
int UprhtPiece = PiecePosition(board[Uprht]);
int lftPiece = PiecePosition(board[lft]);
int rhtPiece = PiecePosition(board[rht]);
int DwnlftPiece = PiecePosition(board[Dwnlft]);
int DwnPiece = PiecePosition(board[Dwn]);
int DwnrhtPiece = PiecePosition(board[Dwnrht]);



	/* Sets flags for the 8 possible movements, confirms position is within range and confirms that if another piece is on space that it is not ally */
	
		if ((Uplft < 64) && (Uplft > 0) && (isKingInCheck(King, Uplft) == 0) && (strcmp(Piece[PosofPiece].color,Piece[UplftPiece].color))){         
			
			UplftOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
		
		if ((Up < 64) && (Up > 0) && (isKingInCheck(King, Up) == 0)&& (strcmp(Piece[PosofPiece].color,Piece[UpPiece].color))){           
			
			UpOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
		
		if ((Uprht < 64) && (Uprht > 0) && (isKingInCheck(King, Uprht) == 0) && (strcmp(Piece[PosofPiece].color,Piece[UprhtPiece].color))){        
			
			UprhtOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}

		if ((lft < 64) && (lft > 0) && (isKingInCheck(King, lft) == 0) && (strcmp(Piece[PosofPiece].color,Piece[lftPiece].color))){         
			 
			lftOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}		
		
		if ((rht < 64) && (rht > 0) && (isKingInCheck(King, rht) == 0) && (strcmp(Piece[PosofPiece].color,Piece[rhtPiece].color))){        
			
			rhtOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
		
		if ((Dwnlft < 64) && (Dwnlft > 0) && (isKingInCheck(King, Dwnlft) == 0) && (strcmp(Piece[PosofPiece].color,Piece[DwnlftPiece].color))){         			
			DwnlftOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
	
		if ((Dwn < 64) && (Dwn > 0) && (isKingInCheck(King, Dwn) == 0) && (strcmp(Piece[PosofPiece].color,Piece[DwnPiece].color))){          			
			DwnOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}
		
		if ((Dwnrht < 64) && (Dwnrht > 0) && (isKingInCheck(King, Dwnrht) == 0) && (strcmp(Piece[PosofPiece].color,Piece[DwnrhtPiece].color))){           			
			DwnrhtOK++; // this checks if this movement follows chess rules then it unlocks another if statement
			}


		/* Matches users input for movement with valid moves based on flags */
			
			if((UplftOK ==1) && (MoveSq == Uplft)){  				
				
				
				board[MoveSq] = board[PieceSq];      
				board[PieceSq] = 0;
				return 0;		
							    
			}
			
			else if((UpOK == 1) && (MoveSq == Up)){ // if move (1 space above) possible and if user input equals 1 space above
				
				board[MoveSq] = board[PieceSq];     
				board[PieceSq] = 0;
				return 0;	
			}

			else if((UprhtOK == 1) && (MoveSq == Uprht)){ 

				board[MoveSq] = board[PieceSq];  // captures by setting array value to pawn value
				board[PieceSq] = 0;
				return 0;
			}

			else if((lftOK == 1) && (MoveSq == lft)){

				board[MoveSq] = board[PieceSq];	// captures but setting array value to pawn value
				board[PieceSq] = 0;
				return 0;
			}
	
			else if((rhtOK == 1) && (MoveSq == rht)){ // if move (1 space above) possible and if user input equals 1 space above
				
				board[MoveSq] = board[PieceSq];     
				board[PieceSq] = 0;
				return 0;	
			}

			else if((DwnlftOK == 1) && (MoveSq == Dwnlft)){ 

				board[MoveSq] = board[PieceSq];  // captures by setting array value to pawn value
				board[PieceSq] = 0;
				return 0;
			}

			else if((DwnOK == 1) && (MoveSq == Dwn)){

				board[MoveSq] = board[PieceSq];	// captures but setting array value to pawn value
				board[PieceSq] = 0;
				return 0;
			}
			
			else if((DwnrhtOK == 1) && (MoveSq == Dwnrht)){

				board[MoveSq] = board[PieceSq];	// captures but setting array value to pawn value
				board[PieceSq] = 0;
				return 0;
			}

			
			else if((WhiteCastleRht_OK == 1) && (MoveSq == g1)){

				board[MoveSq] = board[PieceSq];	// moves king to g1( right castle)
				board[PieceSq] = 0;
				board[f1] = board[h1]; // puts rook at f1 and sets h1 to nothing 
				board[h1] = 0;
				return 0;
			}

			else if((WhiteCastleLft_OK == 1) && (MoveSq == c1)){

				board[MoveSq] = board[PieceSq];	// moves king to c1( left castle)
				board[PieceSq] = 0;
				board[d1] = board[a1]; // puts rook at d1 and sets a1 to nothing 
				board[a1] = 0;
				return 0;
			}

			else if((BlackCastleRht_OK == 1) && (MoveSq == g8)){

				board[MoveSq] = board[PieceSq];	// moves king to g8( right castle)
				board[PieceSq] = 0;
				board[f8] = board[h8]; // puts rook at f8 and sets h8 to nothing 
				board[h8] = 0;
				return 0;
			}

			else if((BlackCastleLft_OK == 1) && (MoveSq == 2)){

				board[MoveSq] = board[PieceSq];	// moves king to c8( left castle)
				board[PieceSq] = 0;
				board[d8] = board[a8]; // puts rook at d8 and sets a8 to nothing 
				board[a8] = 0;
				return 0;
			}
			
			
			else{

				printf("Invalid movement.\n");
				return -10;
			}
			
return 0;
}


