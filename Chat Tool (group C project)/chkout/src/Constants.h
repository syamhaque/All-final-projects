#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include "Constants.h"


#define M_Message 	1
#define M_FRequest 	2
#define M_FAccept	3
#define M_FDecline	4
#define M_PRequest	5
#define M_PReset	6
#define M_Login		7
#define M_Logout	8
#define M_AccountCreate	9
#define M_AccountDelete	10
#define M_LsAvUsers	11		
#define M_MUpdate	12

#define BSIZE 256
#define MAX_OL 20
#define ASCII_RST "\x1B[0m"
#define ASCII_RED "\x1B[31m"
#define ASCII_GRN "\x1B[32m"
#define MAX_FRIEND 20

#define PENDING_MESSAGE_INTERVAL 1

// GLOBAL VARIABLES //
bool logged_in;
struct sockaddr_in server_addr;
/*holds username of recipient to send message to*/
char RECIPIENT[BSIZE];
char SENDER[BSIZE];
/*holds message to be sent*/
char MESSAGE[BSIZE];
char MESSAGE_IN[BSIZE];
/*holds user name when attempting login or register*/
char USERNAME[BSIZE];
/*holds password when attempting login or register*/
char PASSWORD[BSIZE];
/*variable to check if user input has been given to the GUI*/
int INPUT;
int LOGGED_IN;
int REGISTER_REQUEST;
int LOGIN_REQUEST;
/*variable to end the client program when the user quits with GUI*/
int GUI_QUIT;

#endif
