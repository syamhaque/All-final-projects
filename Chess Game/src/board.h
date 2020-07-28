#include "constants.h"
#include <stdio.h>
#ifndef BOARD_H_
#define BOARD_H_

struct Spaces                                           // made struct to represent every square on board which i plan to use to string compare to user input 
{
	Space val;
        char sq[50];
};


extern int IntBoard[64];  // initialized in board.c

extern int reIntBoard[64]; //board we will use to reinitialize IntBoard

/*
extern Node *root_Node = NULL;
extern Node *bestMove = NULL;
*/
extern struct Spaces Squares[64]; // initialized in board.c


#endif //BOARD_H_
