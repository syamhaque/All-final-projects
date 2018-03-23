/* Server.c */
/* Created by Crystal Kingsmen */
/* Jordan Bonecutter, Jesse Corrales, Jose Padilla, Ralph Tran, Syam Haque*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "encryption.h"
#include "Constants.h"
#include "User.h"
#include "encryption.h"

//Global Variables
unsigned char QUIT = 0;
char online_users[MAX_OL][20], book[1000];
unsigned char n_online_users = 0;
MessageList *MStack;
FriendRequestList *PFStack, *AFStack;
unsigned short portno;

//Typedefs
typedef void (*ClientHandler)(int DataSocketFD);
typedef void (*TimeoutHandler)(void);

void warning(char *err)
{
	printf("\n%sWarning: %s%s\n\n", ASCII_RED, err, ASCII_RST);
}

void error(char *err)
{
	printf("\n%sError: %s\n\n%s", ASCII_RED, err, ASCII_RST);
	exit(1);
}

void dprint(char *db)
{       
        printf("\t%s%s%s\n\n", ASCII_GRN, db, ASCII_RST);
}

bool strcontchr(char *master, char test) 
{
	unsigned short n;
	for(n = 0; n < strlen(master); n++)
	{
		if(master[n] == test)
			return true;
	}
	return false;
}

bool isLoggedIn(char *uname)
{
	unsigned char n;
	for(n = 0; n < MAX_OL; n++)
	{
		if(!strcmp(uname, online_users[n]))
			return true;
	}
	return false;
}

int login(char *uname, char *pass)
{
	if(n_online_users >= MAX_OL)
		return -1;
	if(!isLoggedIn(uname))
	{
		if(online_users[n_online_users][0] == 0)
		{
			if(authenticateUser(uname, pass) == 0){
				strcpy(online_users[n_online_users], uname);
				n_online_users++;
				return 0;
			}

			else
				return -1;


		}
		return -1;
	}
	return 1;			
}

int logout(char *uname)
{
	unsigned char n;

	if(n_online_users == 0)
		return -2;

	if(!isLoggedIn(uname))
		return -1;
	
	for(n = 0; n < MAX_OL; n++)
	{
		if(!strcmp(online_users[n], uname))
		{
			memset(online_users[n], 0, 20);
			n_online_users--;
			return 0;
		}
	}
	return 1;
}

void loadBook(void)
{
	FILE *fp;
	int x, offset = 0;
	
	fp = fopen("../src/meinkampf.txt", "r"); //opens the .txt file
	if(fp == NULL){
		printf("Error opening file.\n");
	}

	fseek(fp, offset, SEEK_SET);
	fread(book, sizeof(char), 1000, fp);
}

int makeServer(uint16_t portno)
{
	int serverfd;
	struct sockaddr_in server;

	//Create Socket
	#ifdef DEBUG
	dprint("Creating socket...");
	#endif
	serverfd = socket(PF_INET, SOCK_STREAM, 0);
	if(serverfd < 0)
		error("socket not created");

	//Bind to Socket
	server.sin_family = AF_INET;
	server.sin_port = htons(portno);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	#ifdef DEBUG
	dprint("Binding to socket...");
	#endif
	if(bind(serverfd, (struct sockaddr*)&server, sizeof(server)) < 0)
		error("bind failure");

	//Listen on Socket
	#ifdef DEBUG
	dprint("Listening on socket...");
	#endif
	if(listen(serverfd, 5) < 0)
		error("listen failure");

	return serverfd;	
}

void ProcessMessage(int datafd)
{
	int n, x, fstate;
	unsigned short ll;
	bool cont = true;	
	char send[2*BSIZE], recv[BSIZE], recv_tmp[BSIZE], uname[BSIZE], pass[BSIZE];
	char gen_resp = 1;
	Message *temp = NULL;
	FriendRequest *ftemp = NULL;
	#ifdef DEBUG
	dprint("Reading from client");
	#endif

	memset(recv, 0, sizeof(recv));	
	n = read(datafd, recv, sizeof(recv) - 1);
	if(n < 0)
		error("read failure");

	#ifdef DEBUG
	dprint("Recieved string:");
	dprint(recv);
	#endif
	
	//Process Recv'd string
	//...
	switch(GetMtype(recv))
	{
		case MUpdate:
		{
			#ifdef DEBUG
			dprint("Update Request");
			dprint(recv);
			#endif
			temp = MStack->first;
			ll = MStack->length;
			for(n = 0; n < ll && temp != NULL; n++)
			{
				#ifdef DEBUG
				dprint("Comparing username to:");
				dprint((char *)(recv + 1));
				dprint(temp->to);
				#endif
				if(!strcmp(temp->to, (char *)(recv + 1)))
				{
					#ifdef DEBUG
					dprint("MATCH!");
					#endif
					memset(send, 0, sizeof(send));
					send[0] = 'S';
					strcat(send, temp->msg);
					strcat(send, "`");
					strcat(send, temp->from);
					#ifdef DEBUG
					dprint("Sending...");
					dprint(send);
					#endif
					if(write(datafd, send, strlen(send)) < 0)
					{
						warning("couldn't write to client");
						cont = false;
						break;
					}

					memset(recv_tmp, 0, sizeof(recv_tmp));
					#ifdef DEBUG
					dprint("Recieving confirmation from client");
					#endif
					if(read(datafd, recv_tmp, sizeof(recv_tmp) - 1) < 0)
					{
						warning("read error from client");
						cont = false;
						break;
					}
					#ifdef DEBUG
					dprint("Client:");
					dprint(recv_tmp);
					#endif

					if(temp)
						temp = popMessage(MStack, temp); 
					else
						break;
				}
			}
			
			if(!cont)
				break;
				
			memset(send, 0, sizeof(send));
			#ifdef DEBUG
			dprint("Sending success message");
			#endif
			if(write(datafd, "D", 1) < 0)
				warning("success message not sent");	
			
			memset(recv, 0, sizeof(recv));
			if(read(datafd, recv, sizeof(recv) - 1) < 0)
				warning("no success read from client");
		
			if(recv[0] != 'S')
				break;		

			ll = PFStack->length;
			
			ftemp = PFStack->first;
			for(n = 0; n < ll && ftemp != NULL; n++)
			{
				if(!strcmp(ftemp->to, (char *)(recv + 1)))
				{
					memset(send, 0, sizeof(send));
					send[0] = 'S';
					strcat(send, temp->from);
					if(write(datafd, send, strlen(send)) < 0)
					{	
						warning("username not sent, client connection broken");
						break;
					}

					memset(recv_tmp, 0, sizeof(recv_tmp));
					if(read(datafd, recv_tmp, strlen(recv_tmp) - 1) < 0)
					{
						warning("client connection broken");
						break;
					}	

					if(recv_tmp[0] != 'S')
						break;
				}
				ftemp = ftemp->next;
			}		

			if(write(datafd, "D", 1) < 0)
			{
				warning("success message not sent");
				break;	
			}			

			break;
		}		
	
		case Msg:
		{
			temp = CreateMessage();
			#ifdef DEBUG
			dprint("Message Created");
			#endif
			mstrcpy(temp, (char *)(recv + 1), strlen((char *)(recv + 1)));
			#ifdef DEBUG
			dprint("Appended message:");
			dprint(temp->msg);
			#endif
			if(write(datafd, "S", 1) < 0)
			{
				warning("client message lost");
				break;
			}
			
			memset(recv_tmp, 0, sizeof(recv_tmp));
			if(read(datafd, recv_tmp, sizeof(recv_tmp)-1) < 0)
			{
				warning("client username lost");
				break;
			}
			
			if(write(datafd, "S", 1) < 0)
			{
				warning("client communication broken");
				break;
			}
	
			memset(temp->from, 0 , sizeof(temp->from));
			memset(temp->to, 0, sizeof(temp->to));
			for(n = 0; recv_tmp[n] != '`'; n++)
			{
				temp->from[n] = recv_tmp[n];
			}
			x = n;

			for(n = 0; recv_tmp[n+x+1] != 0; n++)
			{
				temp->to[n] = recv_tmp[n+x+1];	
			}

			#ifdef DEBUG
			dprint("Message from:");
			dprint(temp->from);
			#endif

			#ifdef DEBUG
			dprint("Message to:");
			dprint(temp->to);
			#endif

			temp->sent = false;
			AppendMessage(MStack, temp);			
			#ifdef DEBUG
			dprint("Added Message to stack");
			#endif	
			// if (thread! exist)
			// {
			// 	createThread(temp->from, temp->to)
			// }
			// addToThread(threadName(temp->from, temp->to), temp->from, temp->msg)
			break;
		}

		case FRequest:
		{
			if(write(datafd, "S", 1) < 0)
			{
				warning("Unable to send success message");
				break;
			}

			memset(recv_tmp, 0, sizeof(recv_tmp));
			memset(uname, 0, sizeof(uname));
			for(n = 0; recv[n] != '`'; n++)
			{
				recv_tmp[n] = recv[n];
			}
			
			x = n;

			for(n = x + 1; recv[n] != 0; n++)
			{
				uname[n-x-1] = recv[n];	
			}

			#ifdef DEBUG
			dprint("Friend Request sent from:");
			dprint(recv_tmp);
			dprint("to:");
			dprint(uname);
			#endif
		
			fstate = RequestAlreadyExists(PFStack, recv_tmp, uname);	
			if(fstate == 0)
			{
				ftemp = CreateFriendRequest(recv_tmp, uname);
				AppendFriendRequest(PFStack, ftemp);
			}
			
			else if(fstate == 2)
			{
				//Delete existing rq and add new rq to AFStack	
			}	
			
			break;
		}

		case FAccept:
		{	
			memset(recv_tmp, 0, sizeof(recv_tmp));
			memset(uname, 0, sizeof(uname));
			for(n = 0; recv[n] != '`'; n++)
			{
				recv_tmp[n] = recv[n];
			}
			
			x = n;

			for(n = x; recv[n] != 0; n++)
			{
				uname[n-x] = recv[n];	
			}

			break;
		}

		case FDecline:
		{
			break;
		}
	
		case PRequest:
		{
			break;
		}

		case PReset:
		{
			break;
		}

		case Login:
		{
			#ifdef DEBUG
			dprint("Login request recieved");	
			dprint(recv);
			#endif
		
			recv[0] = '0';
			strcpy(uname, (char *)(recv + 1));	

			if(write(datafd, "S", 1) < 1)		
			{
				warning("couldn't communicate to client");
				break;
			}

			#ifdef DEBUG
			dprint("Wrote S to client!");
			#endif

			memset(recv, 0, BSIZE);
			if(read(datafd, recv, sizeof(recv) - 1) < 0)
			{
				warning("couldn't read from client");
				break;
			}	

			#ifdef DEBUG
			dprint("Password recieved!");
			dprint(recv);
			#endif
	
			decryptPass(recv, pass);
			//strcpy(pass, recv);
			if(login(uname, pass) == 0){
				#ifdef DEBUG
				dprint("login successful");
				#endif
				if(write(datafd, "S", 1) < 0)
				{
					warning("couldn't communicate to client");
					break;
				}
			}
			
			else
			{
				#ifdef DEBUG
				dprint("login failed");
				#endif
				if(write(datafd, "F", 1) < 0)
				{
					warning("couldn't communicate to client");
					break;
				}
			}
			#ifdef DEBUG	
			dprint(uname);
			dprint(pass);
			#endif	
			break;
		}

		case Logout:
		{
			#ifdef DEBUG
			dprint("Logout request recieved!");
			#endif			

			if(write(datafd, "S", 1) < 0);
				warning("User not logged out!");
			logout((char *)(recv + 1));		
			break;
		}

		case AccountCreate:
		{
			recv[0] = '0';
			strcpy(uname, (char *)(recv + 1));	

			if(isValidName(uname) == true)
			{
				#ifdef DEBUG
				dprint("Valid username!");
				#endif
				if(write(datafd, "S", 1) < 1)
				{
					warning("couldn't communicate to client");
					break;
				}
			}
			
			else
			{		
				#ifdef DEBUG
				dprint("Invalid username!");
				#endif
				if(write(datafd, "F", 1) < 1)
				{
					warning("couldn't communicate to client");
					break;
				}
				break;
			}

			memset(recv, 0, BSIZE);
			if(read(datafd, recv, sizeof(recv) - 1) < 0)
			{
				warning("couldn't read from client");
				break;
			}	
			
			#ifdef DEBUG
			dprint("Password recieved!");
			dprint(recv);
			#endif
	
			decryptPass(recv, pass);
			//strcpy(pass, recv);
			if(isValidPassword(pass) == true)
			{
				#ifdef DEBUG
				dprint("Creating account!");
				#endif
				createUser(uname, pass);
				if(write(datafd, "S", 1) < 0)
				{
					warning("couldn't communicate to client");
					break;
				}
			}
			
			else
			{
				if(write(datafd, "F", 1) < 0)
				{
					warning("couldn't communicate to client");
					break;
				}
			}

			break;
		}

		case AccountDelete:
		{
			recv[0] = '0';
			strcpy(uname, (char *)(recv + 1));	

			#ifdef DEBUG
			dprint("username to delete:");
			dprint(uname);
			#endif

			if(isValidName(uname) == false)
			{
				if(write(datafd, "S", 1) < 1)
				{
					warning("couldn't communicate to client");
					break;
				}
			}
			
			else
			{
				if(write(datafd, "F", 1) < 1)
				{
					warning("couldn't communicate to client");
					break;
				}
				break;
			}

			memset(recv, 0, BSIZE);
			if(read(datafd, recv, sizeof(recv) - 1) < 0)
			{
				warning("couldn't read from client");
				break;
			}	
			
			#ifdef DEBUG
			dprint("Password recieved!");
			dprint(recv);
			#endif
	
			decryptPass(recv, pass);
			//strcpy(pass, recv);
			if(authenticateUser(uname, pass) == 0)
			{
				#ifdef DEBUG
				dprint("Deleting account!");
				#endif
				deleteUser(uname);
				if(write(datafd, "S", 1) < 1)
				{
					warning("couldn't communicate to client");
					break;
				}
			}

			else
			{
				if(write(datafd, "F", 1) < 1)
				{
					warning("couldn't communicate to client");
					break;
				}
			}

			break;
		}

		case LsAvailUsers:
		{
			break;
		}
	}		

	#ifdef DEBUG
	dprint("Responding to client...");
	#endif
}

void PrintTimeoutEvent(void)     /*  print/update the current real time */
{    
    char   Wheel[3],
           *WheelChars = "   .  .. ...";
    static unsigned char cycle = 0;
    static int WheelIndex = 0;

    cycle = (cycle + 1)%3;
    if(cycle == 2)
    	WheelIndex = (WheelIndex+1) % 4;
    Wheel[0] = *(WheelChars + WheelIndex*3);
    Wheel[1] = *(WheelChars + WheelIndex*3 + 1);
    Wheel[2] = *(WheelChars + WheelIndex*3 + 2);
    printf("\rServer at port %d%s",    /* print from beginning of current line */
         portno, Wheel);    /* print Server...*/
    fflush(stdout);
} /* end of PrintTimeoutEvent */


void loop(int serverfd, ClientHandler HandleClient, TimeoutHandler HandleTimeout, unsigned timeout)
{
	int datafd, rst, i;
	socklen_t cli_len;
	struct sockaddr_in cli_addr;
	fd_set activefds, readfds;
	struct timeval t_val;
	MStack = CreateMessageList();
	PFStack = CreateFriendRequestList();
	AFStack = CreateFriendRequestList();	

	FD_ZERO(&activefds);
	FD_SET(serverfd, &activefds);
	while(!QUIT)
	{
		readfds = activefds;
		t_val.tv_sec = timeout / 1000000;
		t_val.tv_usec = timeout % 1000000;
		rst = select(FD_SETSIZE, &readfds, NULL, NULL, &t_val);
		
		if(rst < 0)
			error("select failed");
		
		if(rst == 0)
		{
			#ifdef DEBUG
			//dprint("Handling Timeout...");
			#endif

			HandleTimeout();
		}

		else
		{
			for(i = 0; i < FD_SETSIZE; i++)
			{
				if(FD_ISSET(i, &readfds))
				{
					if(i == serverfd)
					{
						#ifdef DEBUG
						dprint("Accepting client...");
						#endif
				
						cli_len = sizeof(cli_addr);
						datafd = accept(serverfd, (struct sockaddr*)&cli_addr, &cli_len);
						if(datafd < 0)
							error("accept failed");

						FD_SET(datafd, &activefds);
					}
					
					else
					{
						#ifdef DEBUG
						dprint("Handling client...");
						#endif
			
						HandleClient(i);
					
						#ifdef DEBUG
						dprint("Closing client...");
						#endif
		
						close(i);
						FD_CLR(i, &activefds);
					}
				}
			}
		}
	}	
}

int main(int argc, char *argv[])
{
	unsigned short serverfd;	

	//if not enough arguments are provided
	if(argc < 2)
		error("incorrect usage, run with -h for help");

	//if the program is run in help mode
	if(!strcmp(argv[1], "-h"))
	{
		printf("Usage: ./CatChat portno\n\n");
		return 0;
	}
	
	portno = atoi(argv[1]);
	if(portno <= 1024)
		error("port reserved, use 1024 - 65535");
	
	#ifdef DEBUG
	dprint("Creating Server...");
	#endif
	
	serverfd = makeServer(portno);
	printf("Server Launched at port %d\n\n", portno);
	
	#ifdef DEBUG
	dprint("Entering main loop...");
	#endif

	loop(serverfd, ProcessMessage, PrintTimeoutEvent, 250000);
	
	printf("Shutting Down...\n\n");
	return 0;
}













