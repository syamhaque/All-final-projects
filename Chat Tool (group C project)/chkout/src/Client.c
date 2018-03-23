/* Client.c */
/* Created by Team 6 */
/* All rights reserved */
/* Members: Jordan Bonecutter, Jesse Corrales-Lozano, Jose Padilla, Ralph Tran, Syam Hadique*/

/*header files for client*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include "User.h"
#include "Constants.h"
#include "encryption.h"
/*header files for client with GUI*/
#ifdef FULL_CLIENT
#include <gtk/gtk.h>
#include "GUI.h"
#endif

// GLOBAL VARIABLES //
char uname[BSIZE];
char book[1000];

// FUNCTIONS //
void dprint(char *db)
{
	printf("%s%s%s\n\n", ASCII_GRN, db, ASCII_RST);
}

void error(char *err)
{
	printf("%s\nError: %s\n\n%s", ASCII_RED, err, ASCII_RST);
	exit(1);
}

MessageType GetMType(void)
{
	printf("What would you like to do:");
	return 0;
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

void loadBook()
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

void SendMsg(char *msg, char *recipient)
{
	if(recipient[strlen(recipient) - 1] == '\n')
		recipient[strlen(recipient) - 1] = 0;
	
	int socketfd, string_l, string_l2;
	unsigned short n, ll;
	char send[BSIZE], recv[BSIZE];
	bool found = false;
	memset(send, 0, sizeof(send));
	Message *tempMessage = CreateMessage();
	tempMessage->sender = true;
	MessageList *tempList = NULL;	

	mstrcpy(tempMessage, msg, strlen(msg));
	strcpy(tempMessage->from, uname);
	strcpy(tempMessage->to, recipient);
	ll = Conversations->length;
	
	if(ll == 0)
	{
		AppendMessageList(Conversations, CreateMessageList());
		AppendMessage(Conversations->first, tempMessage);
		#ifdef FULL_CLIENT
		dprint("Conversation is now longer, new messagelist with new user added!");
		#endif
		Conversations->last->to = tempMessage->to;	
		Conversations->last->from = tempMessage->from;
	}

	else
	{
		tempList = Conversations->first;
		for(n = 0; n < ll && tempList != NULL; n++)
		{
			if(!strcmp(tempList->from, recipient) || !strcmp(tempList->to, recipient))
			{
				AppendMessage(tempList, tempMessage);
				found = true;
				#ifdef FULL_CLIENT 
				dprint("Appended to previously existing conversation");
				#endif
				break;
			}
			tempList = tempList->next;
		}
		if(!found)
		{
			AppendMessageList(Conversations, CreateMessageList());
			AppendMessage(Conversations->last, tempMessage);
			#ifdef FULL_CLIENT 
			dprint("Conversation is now longer, new messagelist with new user added!");
			#endif
			Conversations->last->from = tempMessage->from;
			Conversations->last->to = tempMessage->to;
		}
			tempList = tempList->next;
	}	

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	
	send[0] = M_Message;
	strcat(send, msg);
	
	string_l = strlen(send);
	if(send[string_l-1] == '\n')
		send[--string_l] = 0;
	#ifndef FULL_CLIENT
	string_l2 = strlen(recipient);
	if(recipient[string_l2 - 1] == '\n')
		recipient[--string_l2] = 0;
	#endif //FULL_CLIENT	

	#ifdef DEBUG
	dprint("Connecting...");
	#endif

	if(connect(socketfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		error("connect failed");

	#ifdef DEBUG
	dprint("Writing...");
	#endif

	for(n = 0; send[n] != 0; n++)
	{
		if(send[n] == '`')
		{
			send[n] = '\'';
			#ifdef DEBUG
			dprint("");
			#endif
		}
	}

	if(write(socketfd, send, string_l) < 0)
		error("write failed");

	#ifdef DEBUG
	dprint("Reading...");
	#endif

	if(read(socketfd, recv, sizeof(recv) - 1) < 0)
		error("read failed");

	if(recv[0] != 'S')
		error("message failed to send");

	#ifdef DEBUG
	dprint("Sending:");
	dprint(uname);
	#endif

	memset(send, 0, sizeof(send));	
	strcpy(send, uname);
	send[strlen(uname)] = '`';
	strcpy((char *)(send + strlen(uname) + 1), recipient);

	#ifdef DEBUG
	dprint(send);
	#endif
	
	if(write(socketfd, send, sizeof(send)) < 0)
		error("usernames failed to send");	
	
	memset(recv, 0, sizeof(recv));
	if(read(socketfd, recv, sizeof(recv) - 1) < 0)
		error("failed to communicate with server");

	if(recv[0] != 'S')
		error("failed to send recipient to server");

	#ifdef DEBUG
	dprint("Recieved feedback from server!");
	#endif
}

int RecvUpdate()
{
	char tmsg[BSIZE], tuname[BSIZE], send[BSIZE], recv[BSIZE];
	memset(tmsg, 0, sizeof(tmsg));
	memset(send, 0, sizeof(send));
	unsigned short i, n, x, ll = 0;
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	MessageList *convo = NULL;
	Message *temp = NULL;
	MessageList *tempL = NULL;

	Friend *ftemp = NULL;

	if(connect(socketfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		error("connect failed");

	// Messages
	send[0] = M_MUpdate;
	strcat(send, uname);
	#ifdef DEBUG
	dprint("preparing to send update request");
	dprint(send);
	#endif
	if(write(socketfd, send, strlen(send)) < 0)
		error("write failed");

	for(;;)
	{
		#ifdef DEBUG
		dprint("Reading from server...");
		#endif
		memset(recv, 0, sizeof(recv));
		if(read(socketfd, recv, sizeof(recv) - 1) < 0)
		{
			error("Not reading from server");
		}

		#ifdef DEBUG
		dprint("Recieved:");
		dprint(recv);
		#endif

		if(recv[0] == 'D')
			break;

		if(write(socketfd, "S", 1) < 0)
		{
			error("Not writing to server");
		}

		memset(tmsg, 0, sizeof(tmsg));
		for(i = 1; !(recv[i] == '`'); i++)
		{
			tmsg[i-1] = recv[i];
		}
		x = i + 1;

		#ifdef DEBUG
		dprint("Message:");
		dprint(tmsg);
		#endif

		#ifdef FULL_CLIENT	
		dprint("Message:");
		dprint(tmsg);
		#endif

		memset(tuname, 0, sizeof(tuname));
		for(i = x; recv[i] != 0; i++)
		{
			tuname[i-x] = recv[i];
		}

		#ifdef DEBUG
		dprint("sender:");
		dprint(tuname);
		#endif

		#ifdef FULL_CLIENT
		dprint("sender:");
		dprint(tuname);
		#endif

		if(Conversations->length == 0)
		{
			tempL = CreateMessageList();
			temp = CreateMessage();
			temp->sender = false;
			mstrcpy(temp, tmsg, strlen(tmsg));
			memset(temp->from, 0, sizeof(temp->from));
			strcpy(temp->from, tuname);
			memset(temp->to, 0, sizeof(temp->to));
			strcpy(temp->to, uname);
			tempL->from = &(temp->from[0]);
			tempL->to = &(temp->to[0]);
			AppendMessage(tempL, temp);
			#ifdef FULL_CLIENT
			dprint("Conversation is now longer, new messagelist with new user added!");
			#endif
			#ifdef DEBUG
			dprint("Appended message:");
			dprint(temp->msg);
			dprint("From user:");
			dprint(temp->from);
			#endif
			AppendMessageList(Conversations, tempL);
			#ifdef DEBUG
			dprint("Conversations->first->first->msg = ");
			dprint(Conversations->first->first->msg);
			#endif
		}
		
		else
		{
			ll = Conversations->length;
			convo = Conversations->first;
		
			for(i = 0; i < ll; i++)
			{
				if(convo != NULL && ((!strcmp(convo->from, tuname)) || (!strcmp(convo->to, tuname))))
				{
					temp = CreateMessage();
					temp->sender = false;
					mstrcpy(temp, tmsg, strlen(tmsg));
					memset(temp->from, 0, sizeof(temp->from));
					strcpy(temp->from, tuname);
					memset(temp->to, 0, sizeof(temp->to));
					strcpy(temp->to, uname);
					#ifdef DEBUG
					dprint("Appended message:");
					dprint(temp->msg);
					dprint("From user:");
					dprint(temp->from);
					#endif
					AppendMessage(convo, temp);
					#ifdef FULL_CLIENT
					dprint("Message appended to pre-existing conversation");
					#endif
					#ifdef DEBUG
					dprint("Conversations->last->first->msg = ");
					dprint(Conversations->last->first->msg);
					#endif
				}
				
				else if(i == Conversations->length - 1)
				{
					tempL = CreateMessageList();
					temp = CreateMessage();
					temp->sender = false;
					mstrcpy(temp, tmsg, strlen(tmsg));
					memset(temp->from, 0, sizeof(temp->from));
					strcpy(temp->from, tuname);
					memset(temp->to, 0, sizeof(temp->to));
					strcpy(temp->to, uname);
					tempL->from = &(temp->from[0]);
					tempL->to = &(temp->to[0]);
					AppendMessage(tempL, temp);
					#ifdef DEBUG
					dprint("Appended message:");
					dprint(temp->msg);
					dprint("From user:");
					dprint(temp->from);
					#endif
					AppendMessageList(Conversations, tempL);
					#ifdef FULL_CLIENT
					dprint("Conversation is now longer, new messagelist with new user added!");
					#endif
					#ifdef DEBUG
					dprint("Conversations->last->first->msg = ");
					dprint(Conversations->last->first->msg);
					#endif
				}
				if(convo != NULL)
					convo = convo->next;
			}
		}
	}	
	// EOMessages
	
	if(write(socketfd, "S", 1) < 0)
		error("success message not sent to server");

	//FriendRequests
	for(;;)
	{
		if(read(socketfd, recv, sizeof(recv) - 1) < 0)
			error("couldn't read from server");
	
		if(write(socketfd, "S", 1) < 0)
			error("server communication broken");
		
		if(recv[0] == 'D')
			break;
		
		ftemp = CreateFriend((char *)(recv + 1));
		AppendFriend(PendingRequests, ftemp);	
	}//EOFriendRequests
	
	return n;
}

void SendFriendRequest(char *friend)
{
	int sockfd;
	char send[BSIZE], recv[BSIZE];
	Friend *treq = CreateFriend(friend);
	AppendFriend(PendingRequests, treq);
	memset(send, 0, sizeof(send));
	
	send[0] = M_FRequest;
	strcat((char *)(send + 1), uname);
	send[strlen((char *)(send))] = '`';
	strcat((char *)(send + strlen((char *)(send + 3))), friend);
	#ifdef DEBUG
	dprint(send);
	#endif
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		error("connect failed");
	
	if(write(sockfd, send, strlen(send)) < 0)
		error("write failed!");

	memset(send, 0, sizeof(send));
	if(read(sockfd, recv, sizeof(recv) - 1) < 0)
		error("read failed!");

	if(recv[0] != 'S')
		error("server sent failure!");	
}

int main(int argc, char *argv[])
{
	Conversations = CreateMessageListList();
	Friends = CreateFriendList();
	PendingRequests = CreateFriendList();
	int socketfd, string_l, portno, uname_l;
	struct hostent *server;
	char log, trash, choice, temp[BSIZE], send[BSIZE], recv[BSIZE], pass[BSIZE], recip[BSIZE];
	#ifdef FULL_CLIENT
	char temp_Message[BSIZE], temp_Recipient[BSIZE];
	#endif //FULL_CLIENT
	Message *tempMessage = NULL;
	logged_in = false;
	INPUT = 0;
	GUI_QUIT = 0;
	REGISTER_REQUEST = 0;
	LOGIN_REQUEST = 0;
	log = 'l';

	#ifdef FULL_CLIENT
	USER *user_data = g_malloc(sizeof(*user_data));
	user_data->username = NULL;
	user_data->password = NULL;
	user_data->username_entry = NULL;
	user_data->password_entry = NULL;
	user_data->password_entry2 = NULL;
	#endif //FULL_CLIENT

	// SETUP //
	#ifdef FULL_CLIENT
	/*initialize gtk*/
	gtk_init(&argc, &argv);
	#endif //FULL_CLIENT

	if(argc < 3)
		error("incorrect usage, use ./Client hostname portno");

	if(!strcmp(argv[1], "-h"))
	{
		printf("Usage: ./Client hostname portno\t portno must be 1024 < portno < 65535\n\n");
		return 0;
	}

	printf("Launching...\n");

	server = gethostbyname(argv[1]);
	if(!server)
		error("Server not found");

	portno = atoi(argv[2]);
	if(portno < 1025)
		error("Port reserved");

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);
	server_addr.sin_addr = *(struct in_addr*)server->h_addr_list[0];

	// MAIN LOOP //
	#ifdef FULL_CLIENT
	/*Shows the login screen and from there calls other functions as needed.*/
	gui_loginScreen(user_data);
	#endif //FULL_CLIENT

	do{
		#ifndef FULL_CLIENT
		if(!logged_in)
		{
			printf("Would you like to (l)ogin or (c)reate an account?");
			scanf("%c", &log);
			scanf("%c", &trash);
		}
		#endif

		#ifdef FULL_CLIENT
		while(gtk_events_pending()){
			gtk_main_iteration();
		}
		#endif //FULL_CLIENT

		#ifdef FULL_CLIENT
		while(!logged_in){
		#ifdef FULL_CLIENT
		while(gtk_events_pending()){
			gtk_main_iteration();
		}
		#endif //FULL_CLIENT
		while(!logged_in && REGISTER_REQUEST){
		#endif
		#ifndef FULL_CLIENT
		while(!logged_in && (log == 'c' || log == 'C')){
		#endif
			memset(uname, 0, sizeof(uname));
			memset(pass, 0, sizeof(pass));
			#ifndef FULL_CLIENT
			printf("\nEnter your desired username:\t");
			fgets(uname, sizeof(uname), stdin);

			printf("\nEnter your desired password:\t");
			fgets(pass, sizeof(pass), stdin);
			#endif

			#ifdef FULL_CLIENT
			while(!INPUT && !GUI_QUIT){
				if(gtk_events_pending()){
					gtk_main_iteration();
				}
				if(INPUT){
					strcpy(uname, USERNAME);
					strcpy(pass, PASSWORD);
				}
				if(GUI_QUIT){
					break;
				}
			}
			if(GUI_QUIT){
				break;
			}
			INPUT = 0;
			#endif //FULL_CLIENT

			string_l = strlen(uname);
			#ifndef FULL_CLIENT
			if(uname[string_l-1] == '\n')
				uname[string_l-1] = 0;
			#endif //FULL_CLIENT
			memset(send, 0, BSIZE);
			send[0] = M_AccountCreate;
			strcat(send, uname);
			socketfd = socket(AF_INET, SOCK_STREAM, 0);

			// CONNECT TO SERVER //
			if(socketfd < 0)
				error("socket not created on login");

			if(connect(socketfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
				error("connect failed");

			write(socketfd, send, string_l + 1);

			string_l = strlen(pass);
			if(pass[string_l-1] == '\n')
				pass[string_l-1] = 0;

			memset(send, 0, BSIZE);
			encryptPass(pass, send);
			//strcpy(send, pass);

			#ifdef DEBUG
			dprint("Encrypted!");
			#endif

			memset(recv, 0, BSIZE);
			if(read(socketfd, recv, sizeof(recv) - 1) < 0)
				error("username not recieved by server");

			if(recv[0] != 'S'){
				printf("Server: invalid username\n");
				#ifdef FULL_CLIENT
				gui_printError("Invalid username");
				#endif
				continue;
			}

			write(socketfd, send, strlen(send));

			#ifdef DEBUG
			dprint("Password sent!");
			#endif

			memset(recv, 0, BSIZE);
			if(read(socketfd, recv, sizeof(recv) - 1) < 0)
				error("password not recieved by server");

			if(recv[0] == 'S'){
				#ifndef FULL_CLIENT
				logged_in = true;
				#endif
				#ifdef FULL_CLIENT
				REGISTER_REQUEST = 0;
				#endif
			}

			#ifdef DEBUG
			dprint("Created account with creds:");
			dprint(uname);
			dprint(pass);
			#endif

			#ifndef FULL_CLIENT
			if(!logged_in)
				printf("Invalid credentials, try again\n\n");
			#endif
			#ifdef FULL_CLIENT
			if(REGISTER_REQUEST){
				printf("Invalid credentials, try again\n\n");
				gui_printError("Invalid credentials.\nPassword must be at least 8 characters long, have uppercase and lowercase characters, and contain at least 1 number and 1 special character.");
			}
			else if(!REGISTER_REQUEST){
				printf("Registered successfully\n");
				g_list_foreach(gtk_window_list_toplevels (), (GFunc)gui_returnToLoginScreen, user_data->username_entry);
			}
			#endif
			#ifdef DEBUG
			else
				dprint("Logged In!!!!!!!!!");
			#endif

			uname_l = strlen(uname);
		}

		// LOGIN //
		#ifdef FULL_CLIENT
		while(!logged_in){
		#endif
		#ifndef FULL_CLIENT
		while(!logged_in && (log == 'l' || log == 'L')){
		#endif
			#ifdef FULL_CLIENT
			//printf("Login stage\n");
			while(gtk_events_pending()){
				gtk_main_iteration();
			}
			if(REGISTER_REQUEST){
				break;
			}
			#endif //FULL_CLIENT
			memset(uname, 0, sizeof(uname));
			memset(pass, 0, sizeof(pass));
			#ifndef FULL_CLIENT
			printf("Enter your username:\t");
			fgets(uname, sizeof(uname), stdin);
			#endif //FULL_CLIENT
			#ifdef FULL_CLIENT
			while(!INPUT && !GUI_QUIT){
				if(gtk_events_pending()){
					gtk_main_iteration();
				}
				if(INPUT){
					strcpy(uname, user_data->username);
					strcpy(pass, user_data->password);
				}
				if(REGISTER_REQUEST){
					break;
				}
				if(GUI_QUIT){
					break;
				}
			}
			if(GUI_QUIT){
				break;
			}
			if(REGISTER_REQUEST){
				break;
			}
			INPUT = 0;
			#endif //FULL_CLIENT
			string_l = strlen(uname);
			#ifndef FULL_CLIENT
			if(uname[string_l-1] == '\n')
				uname[string_l-1] = 0;
			#endif //FULL_CLIENT
			#ifndef FULL_CLIENT
			printf("Enter your password:\t");
			fgets(pass, sizeof(pass), stdin);
			#endif //FULL_CLIENT

			memset(send, 0, BSIZE);
			send[0] = M_Login;
			strcat(send, uname);
			socketfd = socket(AF_INET, SOCK_STREAM, 0);
			
			memset(temp, 0, BSIZE);
			pass[strlen(pass)] = 0;
			encryptPass(pass, temp);		
			//strcpy(send, pass);

			#ifdef DEBUG
			dprint("Encrypted!");
			#endif

			// CONNECT TO SERVER //
			if(socketfd < 0)
				error("socket not created on login");

			if(connect(socketfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
				error("connect failed");

			write(socketfd, send, string_l + 1);

			string_l = strlen(pass);
			if(pass[string_l-1] == '\n')
				pass[string_l-1] = 0;


			memset(recv, 0, BSIZE);
			if(read(socketfd, recv, sizeof(recv) - 1) < 0)
				error("username not recieved by server");

			if(recv[0] != 'S'){
				error("Server: invalid username");
				#ifdef FULL_CLIENT
				gui_printError("Invalid username");
				#endif
			}

			#ifdef DEBUG
			dprint("Sending String:");
			dprint(temp);
			#endif

			write(socketfd, temp, strlen(pass) + 2);

			#ifdef DEBUG
			dprint("Sent!");
			#endif

			memset(recv, 0, BSIZE);
			if(read(socketfd, recv, sizeof(recv) - 1) < 0)
				error("password not recieved by server");

			if(recv[0] == 'S'){
				logged_in = true;
				#ifdef FULL_CLIENT
				LOGGED_IN = 1;
				gtk_widget_hide(gtk_widget_get_toplevel (user_data->username_entry));
				gui_mainScreen(NULL, NULL);
				#endif
			}
		
			#ifdef DEBUG
			dprint("Logging in with creds:");
			dprint(uname);
			dprint(pass);
			#endif

			if(!logged_in){
				printf("Incorrect credentials, try again\n\n");
				#ifdef FULL_CLIENT
				gui_printError("Incorrect credentials, try again");
				#endif
			}

			#ifdef DEBUG
			else
				dprint("Logged In!!!!!!!!!");
			#endif

			uname_l = strlen(uname);
			#ifdef FULL_CLIENT
			while(gtk_events_pending()){
				gtk_main_iteration();
			}
			#endif //FULL_CLIENT
		}// LOGGED IN //
		#ifdef FULL_CLIENT
		if(GUI_QUIT){
			break;
		}
		}//while loop that makes sure user logs in with gui
		#endif	

		#ifndef FULL_CLIENT
		RecvUpdate();
		printf("(D)elete accout or (S)end message?");
		scanf("%c", &choice);
		scanf("%c", &trash);
		while(choice == 'd' || choice == 'D')
		{
			socketfd = socket(AF_INET, SOCK_STREAM, 0);

			if(connect(socketfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
				error("connect failed");

			memset(send, 0, sizeof(send));
			send[0] = M_AccountDelete;
			strcat(send, uname);
			#ifdef DEBUG
			dprint("string to be sent:");
			dprint(send);
			#endif

			if(write(socketfd, send, strlen(send)) < 0)
				error("server not written to");

			memset(recv, 0, sizeof(recv));
			if(read(socketfd, recv, sizeof(recv) - 1) < 0)
				error("username not recieved by server");

			if(recv[0] != 'S')
				error("invalid username, account not deleted");

			memset(send, 0, sizeof(send));
			encryptPass(pass, send);
			
			#ifdef DEBUG
			dprint("Encrypted!");
			#endif
			
			//strcpy(send, pass);
			if(write(socketfd, send, strlen(pass)) < 0)
				error("server not written to");

			#ifdef DEBUG
			dprint("Sent!");
			#endif
			
			memset(recv, 0, sizeof(recv));
			if(read(socketfd, recv, sizeof(recv) - 1) < 0)
				error("password not recieved by server");

			if(recv[0] != 'S')
				error("invalid creds, account not deleted");

			else
			{
				GUI_QUIT = 1;
				break;
			}
		}
		#endif


		if(GUI_QUIT){
			break;
		}
		#ifdef FULL_CLIENT
		while(gtk_events_pending()){
			gtk_main_iteration();
		}
		memset(temp_Message, 0, sizeof(temp_Message));
		memset(temp_Recipient, 0, sizeof(temp_Recipient));
		#endif //FULL_CLIENT
		#ifndef FULL_CLIENT
		memset(temp, 0, sizeof(temp));
		#endif //FULL_CLIENT
		memset(send, 0, sizeof(send));
		#ifndef FULL_CLIENT
		printf("Enter a message:\n");
		fgets(temp, sizeof(temp), stdin);
		#endif //FULL_CLIENT
		#ifdef FULL_CLIENT
		while(!INPUT && !GUI_QUIT){
			if(gtk_events_pending()){
				gtk_main_iteration();
			}
			if(INPUT){
				strcpy(temp_Message, MESSAGE);
				strcpy(temp_Recipient, RECIPIENT);
			}
			if(GUI_QUIT){
				break;
			}
			if(!LOGGED_IN){
				logged_in = false;
				g_list_foreach(gtk_window_list_toplevels (), (GFunc)gui_returnToLoginScreen, user_data->username_entry);
				break;
			}
		}
		if(!LOGGED_IN)
			continue;
		if(GUI_QUIT){
			break;
		}
		INPUT = 0;
		#endif //FULL_CLIENT
		
		#ifdef FULL_CLIENT
		if(!strcmp(temp_Message, "quit\n") || !strcmp(temp_Message, "quit"))
		{
			printf("Bye!\n");
			break;
		}
		#endif //FULL_CLIENT
		#ifndef FULL_CLIENT
		if(!strcmp(temp, "quit\n") || !strcmp(temp, "quit"))
		{
			printf("Bye!\n");
			break;
		}
		#endif //FULL_CLIENT
		#ifndef FULL_CLIENT
		memset(recip, 0, sizeof(recip));
		printf("Enter the username of the recipient of the message:\t");
		fgets(recip, sizeof(recip), stdin);
		#endif //FULL_CLIENT
		if(string_l)
		{
			#ifdef FULL_CLIENT
			SendMsg(temp_Message, temp_Recipient);
			#endif

			#ifndef FULL_CLIENT
			SendMsg(temp, recip);
			#endif
		}

		#ifndef FULL_CLIENT
		RecvUpdate();
		#endif

	}while(!GUI_QUIT);
	#ifdef FULL_CLIENT
	g_free(user_data);
	user_data = NULL;
	#endif //FULL_CLIENT
	return 0;
}
