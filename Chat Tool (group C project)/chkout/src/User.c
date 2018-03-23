#include "User.h"
#include <stdbool.h>
#ifdef USER_MAIN
int main()
{
	printf("Creating a new user...\n");
	User *tempUser = CreateUser();
	printf("Created new user at %p!\n", tempUser);

	printf("\n");
	printf("Deleting the user at %p...\n", tempUser);
	DeleteUser(tempUser);
	printf("Deleted user!\n");

	printf("\n");
	printf("Creating a new message...\n");
	Message *tempMess = CreateMessage();
	printf("Created a new message at %p!\n", tempMess);

	printf("\n");
	printf("Changing message type to Msg...\n");
	tempMess->type = Msg;
	printf("Type changed to msg!\n");

	printf("\n");
	printf("Changing message type to MUpdate...\n");
	tempMess->type = MUpdate;
	printf("Type changed to MUpdate!\n");	 
	
	printf("\n");
	printf("Changing message type to FriendRequest...\n");
	tempMess->type = FRequest;
	printf("Type changed to FriendRequest!\n");
	 
	printf("\n");
	printf("Changing message type to FAccept...\n");
	tempMess->type = FAccept;
	printf("Type changed to FAccept!\n");	 
	
	printf("\n");
	printf("Changing message type to FDecline...\n");
	tempMess->type = FDecline;
	printf("Type changed to FDecline!\n");	 
	
	printf("\n");
	printf("Changing message type to PRequest...\n");
	tempMess->type = PRequest;
	printf("Type changed to PRequest!\n");	 
	
	printf("\n");
	printf("Changing message type to PReset...\n");
	tempMess->type = PReset;
	printf("Type changed to PReset!\n");	 
	
	printf("\n");
	printf("Changing message type to Login...\n");
	tempMess->type = Login;
	printf("Type changed to Login!\n");	 
	
	printf("\n");
	printf("Changing message type to Logout...\n");
	tempMess->type = Logout;
	printf("Type changed to Logout!\n");	 
	
	printf("\n");
	printf("Changing message type to AccountCreate...\n");
	tempMess->type = AccountCreate;
	printf("Type changed to AccountCreate!\n");	 
	
	printf("\n");
	printf("Changing message type to AccountDelete...\n");
	tempMess->type = AccountDelete;
	printf("Type changed to AccountDelete!\n");	 
	
	printf("\n");
	printf("Changing message type to LsAvailUsers...\n");
	tempMess->type = LsAvailUsers;
	printf("Type changed to LsAvailUsers!\n");	 

	printf("\n");
	printf("Creating a new MessageList...\n");
	MessageList *tempMList = CreateMessageList();
	printf("MessageList created at %p!\n", tempMList);

	printf("\n");
	printf("Appending message at %p to list at %p...\n", tempMess, tempMList);
	AppendMessage(tempMList, tempMess);
	printf("Appended!\n");
	
	printf("\n");
	printf("Creating two test messages...\n");
	Message *tempMess1 = CreateMessage();
	Message *tempMess2 = CreateMessage();
	printf("Created messages at %p and %p!\n", tempMess1, tempMess2);

	printf("\n");
	printf("Appending messages at %p and %p to list at %p...\n", tempMess1, tempMess2, tempMList);
	AppendMessage(tempMList, tempMess1);
	AppendMessage(tempMList, tempMess2);
	printf("Successfully appended messages to the list!\n");

	printf("\n");
	printf("Popping middle message at %p from the list...\n", tempMess1);
	popMessage(tempMList, tempMess1);
	printf("Successfully popped message from list!\n");

	printf("\n");
	printf("Deleting MessageList at %p...\n", tempMList);
	DeleteMessageList(tempMList);
	printf("MessageList deleted!\n");	

	printf("\n");
	printf("Creating MessageListList...\n");
	MessageListList *tempMListList = CreateMessageListList();
	printf("MessageListList created at %p!\n", tempMListList);

	printf("\n");
	printf("Creating MessageList to append to MessageListList...\n");
	tempMList = CreateMessageList();
	printf("Created MessageList at %p!\n", tempMList);

	printf("\n");
	printf("Appending MessageList at %p to MessageListList at %p...\n", tempMList, tempMListList);
	AppendMessageList(tempMListList, tempMList);
	printf("Appended MessageList!\n");

	printf("\n");
	printf("Creating two test MessageLists...\n");
	MessageList *tempMList1 = CreateMessageList();
	MessageList *tempMList2 = CreateMessageList();
	printf("Created MessageLists at %p and %p!\n", tempMList1, tempMList2);

	printf("\n");
	printf("Appending MessageLists at %p and %p to MessageListList at %p...\n", tempMList1, tempMList2, tempMListList);
	AppendMessageList(tempMListList, tempMList1);
	AppendMessageList(tempMListList, tempMList2);
	printf("Appended MessageLists to the MessageListList!\n");

	printf("\n");
	printf("Deleting MessageListList at %p...\n", tempMListList);
	DeleteMessageListList(tempMListList);
	printf("MessageListList deleted!\n");

	printf("\nUser.c module test complete, we've passed in flying %sc%so%sl%so%sr%ss%s!\n", "\x1b[31m", "\x1b[32m", "\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m", "\x1b[0m");
	
}
#endif

//==================== User ====================
User *CreateUser(void)
{
	User *newUser = malloc(sizeof(User));
	memset(newUser, 0, sizeof(newUser));
	memset(newUser->friends, 0, sizeof(newUser->friends)); 
	memset(newUser->activeChat, 0, sizeof(newUser->activeChat));
	return newUser;	
}

void DeleteUser(User *del)
{
	free(del);
}

//==================== Message ====================
Message *CreateMessage(void)
{
	Message *newMsg = malloc(sizeof(Message));
	newMsg->type = Msg;
	newMsg->msg = NULL;
	newMsg->sent = false;	
	newMsg->next = NULL;
	newMsg->prev = NULL;

	return newMsg;
}

void DeleteMessage(Message *m)
{
	m->next = NULL;
	m->prev = NULL;
	if(m->msg != NULL)
		free(m->msg);
	free(m);
}

MessageType GetMtype(char *m)
{
	switch(*m)
	{
		case M_MUpdate:
			return MUpdate;
		case M_Message:
			return Msg;
		case M_FRequest:
			return FRequest;
		case M_FAccept:
			return FAccept;
		case M_PRequest:
			return PRequest;
		case M_PReset:
			return PReset;
		case M_Login:
			return Login;
		case M_Logout:
			return Logout;
		case M_AccountCreate:
			return AccountCreate;
		case M_AccountDelete:
			return AccountDelete;
		case M_LsAvUsers:
			return LsAvailUsers; 
		default:
			return Msg;
	}		
}

void mstrcpy(Message *m, char *s, int l)
{
	if(m->msg == NULL)
	{
		m->msg = malloc((l+1)*sizeof(char));
		memset(m->msg, 0, l+1);
		strcpy(m->msg, s);	
	}

	else
	{
		free(m->msg);
		m->msg = malloc((l+1)*sizeof(char));
		memset(m->msg, 0, l+1);
		strcpy(m->msg, s);
	}
}

//==================== MessageList ====================
MessageList *CreateMessageList(void)
{
	MessageList *newList = malloc(sizeof(MessageList));
	newList->length = 0;
	newList->first = NULL;
	newList->last = NULL;
	newList->from = NULL;
	newList->to = NULL;
	newList->next = NULL;
	newList->prev = NULL;
	newList->rst = true;
	return newList;
}

void AppendMessage(MessageList *l, Message *m)
{
	if(l->last == NULL)//if the list is empty
	{
		l->last = m;
		l->first = m;
		m->next = NULL;
		m->prev = NULL;
	}
	else//if the list is not empty
	{
		l->last->next = m;
		m->prev = l->last;
		m->next = NULL;
		l->last = m;
	}
	l->from = m->from;
	l->to = m->to;
	l->length++;	
}

Message *popMessage(MessageList *l, Message *m)
{
	if(l->length == 0)
		return NULL;

	Message *temp;

	if(m == l->first && l->length > 1)
	{
		temp = m->next;
		l->first = temp;
		temp->prev = NULL;
		DeleteMessage(m);
		l->length--;
		return temp;	
	}

	else if(m == l->last || l->length == 1)
	{
		DeleteLastMessage(l);
		return NULL;
	}

	else
	{
		temp = m->prev;
		temp->next = m->next;
		temp = m->next;
		temp->prev = m->prev;
		DeleteMessage(m);
		l->length--;
		return temp;
	}
}

void DeleteLastMessage(MessageList *l)
{
	if(!l->last)
		return;
	else if(l->length > 1)
	{
		Message *temp = l->last;
		l->last->prev->next = NULL;
		l->last = temp->prev;
		DeleteMessage(temp);
		l->length--;
	}
	
	else
	{
		DeleteMessage(l->first);
		l->length--;
		l->first = NULL;
		l->last = NULL;
	}
}

void DeleteMessageList(MessageList *l)
{
	unsigned short n;
	unsigned short const ll = l->length;

	for(n = 0; n < ll; n++)
	{
		DeleteLastMessage(l);
	}
	free(l);	
}

//==================== MessageListList ====================

MessageListList *CreateMessageListList(void)
{
	MessageListList *temp = malloc(sizeof(MessageListList));
	temp->length = 0;
	temp->first = NULL;
	temp->last = NULL;

	return temp;
}

void AppendMessageList(MessageListList *l, MessageList *m)
{
	if(l->length == 0)
	{
		l->first = m;
		l->last = m;
		m->next = NULL;
		m->prev = NULL;
	}

	else
	{
		l->last->next = m;
		m->prev = l->last;
		m->next = NULL;
		l->last = m;
	}

	l->length++;
}

void DeleteLastMessageList(MessageListList *l)
{
	if(l->length == 0)
	{
		return;
	}

	MessageList *temp = NULL;
	temp = l->last->prev;

	DeleteMessageList(l->last);
	l->last = temp;
	if(temp != NULL)
		temp->next = NULL;	
	
	l->length--;
}

void DeleteMessageListList(MessageListList *l)
{
	unsigned short n = 0;
	const unsigned short ll = l->length;
	for(n = 0; n < ll; n++)
	{
		DeleteLastMessageList(l);
	}
	free(l);
}

MessageList *getConversation(MessageListList *l, const char *name)
{
	if(l == NULL || name == NULL)
		return NULL;

	const unsigned short ll = l->length;
	unsigned short x, n = 0;
	MessageList *temp = l->first;

	if(ll == 0)
		return NULL;

	for(n = 0; n < ll && temp != NULL; n++)
	{	
		if((!strcmp(name, temp->from) || !strcmp(name, temp->to)))
		{
			return temp;	
		}
		temp = temp->next;	
	}
	return NULL;
}

void rstLists(MessageListList *l)
{
	unsigned short n = 0;
	MessageList *temp = NULL;
	if(l->length == 0)
		return;
	for(n = 0; n < l->length && temp != NULL; n++)
	{
		temp->rst = true;
		temp = temp->next;	
	}
}

//==================== Friend ====================

Friend *CreateFriend(char *friend)
{
	Friend *temp = calloc(sizeof(Friend), 1);
	temp->uname = calloc(sizeof(friend) + 1, 1);
	strcpy(temp->uname, friend);	
	return temp;
}

void FSetUname(Friend *f, char *s)
{
	if(f->uname == NULL)
	{
		f->uname = calloc(strlen(s) + 1, sizeof(char));
	}
	else
	{
		free(f->uname);
		f->uname = calloc(strlen(s) + 1, sizeof(char));
	}

	strcpy(f->uname, s);
}

void DeleteFriend(Friend *f)
{
	if(f->uname != NULL)
		free(f->uname);

	free(f);
}

FriendList *CreateFriendList(void)
{
	FriendList *temp = calloc(sizeof(FriendList), 1);
	temp->length = 0;
	return temp;
}

bool isFriend(FriendList *f, char *s)
{
	if(f->length == 0)
		return false;

	Friend *temp = f->first;
	const unsigned short ll = f->length;
	unsigned short n = 0;
	for(n = 0; temp->uname != NULL && strcmp(temp->uname, s) && n < ll; n++)
	{
		if(temp)
			temp = temp->next;
		else
			break;
	}	

	if(temp->uname != NULL && !strcmp(temp->uname, s))
		return true;
	return false;
}

void AppendFriend(FriendList *l, Friend *f)
{
	if(l->length == 0)
	{
		l->first = f;
		l->last = f;
		f->prev = NULL;
		f->next = NULL;
	}	

	else
	{
		l->last->next = f;
		f->prev = l->last;
		f->next = NULL;
		l->last = f;
	}
	
	l->length++;
}

Friend *popFriend(FriendList *l, char *s)
{
	if(l->length == 0)
		return NULL;

	if(strlen(s) == 0)
		return NULL;

	Friend *temp = l->first;
	Friend *ntemp;
	unsigned short n = 0;
	for(n = 0; n < l->length && temp != NULL; n++)
	{
		if(!strcmp(temp->uname, s))
		{
			ntemp = temp->next;
			if(temp->prev != NULL)
				temp->prev->next = temp->next;

			if(temp->next != NULL)
				temp->next->prev = temp->prev;
		
			if(temp != NULL)
				DeleteFriend(temp);
		
			l->length--;
			return ntemp;
		}
	}
	return NULL;
}

void DeleteLastFriend(FriendList *l)
{
	if(!l->last)
		return;
	else if(l->length > 1)
	{
		Friend *temp = l->last;
		l->last->prev->next = NULL;
		l->last = temp->prev;
		DeleteFriend(temp);
		l->length--;
	}
	
	else
	{
		DeleteFriend(l->first);
		l->length--;
		l->first = NULL;
		l->last = NULL;
	}
}

void DeleteFriendList(FriendList *l)
{
	const unsigned short ll = l->length;
	unsigned short n;
	for(n = 0; n < ll; n++)
	{
		DeleteLastFriend(l);
		if(l->last == NULL)
			break;
	} 
	free(l);
}

//==================== Friend ====================

FriendRequest *CreateFriendRequest(char *from, char *to)
{
	FriendRequest *temp = calloc(sizeof(FriendRequest), 1);
	temp->from = calloc(sizeof(from) + 1, sizeof(char));
	temp->to = calloc(sizeof(to) + 1, sizeof(char));
	strcpy(temp->from, from);
	strcpy(temp->to, to);
	return temp;	
}

void DeleteFriendRequest(FriendRequest *f)
{
	if(f->from != NULL)	
	{
		free(f->from);
		f->from = NULL;
	}

	if(f->to != NULL)
	{
		free(f->to);
		f->to = NULL;
	}

	free(f);
}

FriendRequestList *CreateFriendRequestList(void)
{
	FriendRequestList *temp = calloc(sizeof(FriendRequestList), 1);
	temp->length = 0;	
	return temp;
}

void DeleteLastFriendRequest(FriendRequestList *l)
{
	if(!l->last)
		return;
	else if(l->length > 1)
	{
		FriendRequest *temp = l->last;
		l->last->prev->next = NULL;
		l->last = temp->prev;
		DeleteFriendRequest(temp);
		l->length--;
	}
	
	else
	{
		DeleteFriendRequest(l->first);
		l->length--;
		l->first = NULL;
		l->last = NULL;
	}
}

FriendRequest *popFriendRequest(FriendRequestList *l, FriendRequest *m)
{
	if(l->length == 0)
		return NULL;

	FriendRequest *temp;

	if(m == l->first && l->length > 1)
	{
		temp = m->next;
		l->first = temp;
		temp->prev = NULL;
		DeleteFriendRequest(m);
		l->length--;
		return temp;	
	}

	else if(m == l->last || l->length == 1)
	{
		DeleteLastFriendRequest(l);
		return NULL;
	}

	else
	{
		temp = m->prev;
		temp->next = m->next;
		temp = m->next;
		temp->prev = m->prev;
		DeleteFriendRequest(m);
		l->length--;
		return temp;
	}
}

void AppendFriendRequest(FriendRequestList *l, FriendRequest *f)
{
	if(l->last == NULL)//if the list is empty
	{
		l->last = f;
		l->first = f;
		f->next = NULL;
		f->prev = NULL;
	}
	else//if the list is not empty
	{
		l->last->next = f;
		f->prev = l->last;
		f->next = NULL;
		l->last = f;
	}
	l->length++;	
}

void DeleteFriendRequestList(FriendRequestList *l)
{
	unsigned short n;
	unsigned short const ll = l->length;

	for(n = 0; n < ll; n++)
	{
		DeleteLastFriendRequest(l);
	}
	free(l);	
}

unsigned char RequestAlreadyExists(FriendRequestList *l, char *from, char *to)
{
	const unsigned short ll = l->length;
	unsigned short n;
	FriendRequest *temp = NULL;
	if(ll == 0)
		return 0;

	temp = l->first;
	
	for(n = 0; n < ll && temp != NULL; n++)
	{
		if(!strcmp(temp->to, from) && !strcmp(temp->from, to))
			return 2;
		else if(!strcmp(temp->to, to) && !strcmp(temp->to, to))
			return 1;
		temp = temp->next;		
	}
	return 0;
}

//EOF
//
//
//
//
//
//
//
//
//
//
