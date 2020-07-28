




#ifndef CHESSPIECES_H_
#define CHESSPIECES_H_

struct Pieces    // struct that will be used for all pieces  
{

int value;       // This value is the pieces particular enum value
char color[50];  // Black or white used identify players
char name[50];   // used to generate a tag to identify piece on board
int Pawnflag;        // at the moment no use, but thinking flags can be assembled to enable other functions depending on piece
int AIvalues;

};

extern struct Pieces Piece[33];

//returns position in struct Pieces array that a constant enum value is associated with.
int PiecePosition(int ValueofSpace);


int enPassant(int Piece, int Space);

//If player reaches 8th rank for pawn they are able to promote pawn to bishop,queen,rook or knight
void PawnPromotion(int PawnSpace,int board[]);

int castle( int ChessPiece, int board[]);

/*Moves Pawn. Returns 0 if no error. Returns -10 if invalid move*/
int MovePawn(int PieceSq,int MoveSq, int board[]);

/*Moves Knight. Returns 0 if no error. Returns -10 if Invalid Move.*/
int MoveKnight (int PieceSq,int MoveSq, int board[]);

/*Moves King. Returns 0 if no error. Returns -10 if Invalid Move.*/
int MoveKing (int PieceSq,int MoveSq, int board[]);

//global variables

/* This flag is set to 2 in EnPassant() and decrements every turn till equals 0. Thus allow opponent 1 turn to perform operation*/
extern int En_Passant_Flag;

/* This value holds the piece that just performed a double space jumped thus allowing EnPassant, initally set outside board range*/
extern int En_Passant_Square;

extern char white[50];
extern char black[50];



#endif //CHESSPIECES_H_
