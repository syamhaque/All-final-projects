#ifndef AIMOVEH
#define AIMOVEH
#include "ChessPieces.h"
#include <stdbool.h>

typedef struct NODELIST {
	int length;
	struct Node *first;
	struct Node *last;
}NODELIST;

typedef struct Node {
	struct NODELIST *list;
	struct Node *next;
	struct Node *prev;
	int board[64];
    int startLoc;     // indicates where the piece is starting from             
    int endLoc;       // indicates where the piece will be moving to
}Node;

typedef struct BestMove {
	int board[64];
	int score;
	int startLocation;     // indicates where the piece is starting from             
    int endLocation;       // indicates where the piece will be moving to	
}BESTMOVE;

extern BESTMOVE bestMove; //initialized in AI_Move.c

int tempCheckMate (int board[], char allyTeam[]);

/* Condition: plyOne should always be 0 when being called for the first time
   plyOne will be used for determining when you are in ply One, which represents the moves
   that will be made by the AI */
int minimax(int depth, int plyOne, int board[], int isMax, int alpha, int beta, char allyTeam[], char enemyTeam[]);

int findKing (int board[64], int startLocation); // this will find the king of the team based on the startLocation 

int isKingInCheckAI(int board[], int king_value, int position); //bases it off User_Move.c function, need new one for AI
int isKingInCheckMateAI(int board[],int king_value, int position);

NODELIST *createNodeList(); // creates the dynamically allocated array that will store the nodes

//void deleteNodeList(NODELIST *nodeList); //deletes the nodelist afterwards

// This function will create a valid move node that will be considered by the AI before it makes its move, and create a pointer to the first member of the struct
void createValidMove(int startLoc, int endLoc, NODELIST *nodeList, int board[64]);

// This function will delete a valid move node to free space
//void deleteMove(Node *node);

void deleteMove(Node *node);

void deleteNodeList (NODELIST *nodeList);

//this function is for debugging purposes
void printBestMove();

void printMove(int board[]);

//
void undoMove(int currentBoard[], int startLocation, int endLocation);

// This function will evalutate the board taking into account the result of the move and return a int score
int evalscore(int board[]);

/* This function will distinguish between pieces and activate the appropriate move function */
void MoveAI(char team[], NODELIST *nodeList, int board[64]);

// will perform the actual manipulation of the board to represent moving a piece once the AI has decided what its best move is
void MovePiece();

//scans the board to determine what pieces are on the AI's side
int * findTeam(char team[], int *length, int board[]);

/* Checks to see that the location is a valid entry within the bound of the array*/
bool isValid(int endLocation);

/* Checks to see whether or not a piece is occupying the tile*/
bool isOccupied(int endLocation, int board[]);

/* Checks to see whether or not the piece is an enemy */
bool isEnemy(int start, int endLocation, int board[]);

/* Utilizes isValid, isOccupied, and isEnemy to check if move is legal*/
bool isLegal(int startLocation, int endLocation, int board[]);

/* Each individual function calculates the positions that the specific piece can move to*/
void movePawn(int startLocation, NODELIST *nodeList, int board[64]);
void moveRook(int startLocation, NODELIST *nodeList, int board[64]);
void moveKnight(int startLocation, NODELIST *nodeList, int board[64]);
void moveBishop(int startLocation, NODELIST *nodeList, int board[64]);
void moveQueen(int startLocation, NODELIST *nodeList, int board[64]);
void moveKing(int startLocation, NODELIST *nodeList, int board[64]);



#endif
