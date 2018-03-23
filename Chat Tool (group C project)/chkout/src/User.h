#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdbool.h>
#include "Constants.h"
#include <stdlib.h>
#include <string.h>

// Structs //

typedef struct lnkls LinkedList;
typedef struct user User;
typedef struct msg Message;
typedef struct msgl MessageList;
typedef struct msgll MessageListList;
typedef struct frnd Friend;
typedef struct flist FriendList;
typedef struct frq FriendRequest;
typedef struct frql FriendRequestList;

// Global Variables //
MessageListList *Conversations;
FriendList *Friends;
FriendList *PendingRequests;

//=========== LinkedList =============
struct lnkls{
	void *next;
	void *prev;
	void *element;
};

//=========== User =============

struct user{
	char uname[BSIZE];
	char friends[MAX_FRIEND][20];
	char activeChat[20];
};

User *CreateUser(void);
void DeleteUser(User *);

//=========== Message =============

typedef enum {
	Msg, 
	MUpdate,
	FRequest,
	FAccept,
	FDecline,
	PRequest,
	PReset,
	Login,
	Logout,
	AccountCreate,
	AccountDelete,
	LsAvailUsers,
	FileTransferReq,
	FileTransferAcc,
	FileTransferTS,
	FileTransferTC
}MessageType;

struct msg{
	MessageType type;
	char from[20];
	char to[20];
	char *msg;
	bool sent;
	bool sender;
	Message *next;
	Message *prev;
};

Message *CreateMessage(void);
void DeleteMessage(Message *);
MessageType GetMtype(char *);
void mstrcpy(Message *, char *, int);

//=========== Message List =============//

struct msgl{
	unsigned short length;
	Message *first;
	Message *last;
	char *from;
	char *to;
	MessageList *next;
	MessageList *prev;
	bool rst;
};

MessageList *CreateMessageList(void);
void AppendMessage(MessageList *, Message *);
Message *popMessage(MessageList *, Message *);
void DeleteLastMessage(MessageList *);
void DeleteMessageList(MessageList *);

//=========== MessageListList ============//

struct msgll{
	unsigned short length;
	MessageList *first;
	MessageList *last;	
};

MessageListList *CreateMessageListList(void);
void AppendMessageList(MessageListList *, MessageList *);
void DeleteLastMessageList(MessageListList *);
void DeleteMessageListList(MessageListList *);
MessageList *getConversation(MessageListList *, const char *);
void rstLists(MessageListList *);

//=========== Friend ============//

struct frnd{
	char *uname;
	Friend *next;
	Friend *prev;
};

Friend *CreateFriend(char *);
void FSetUname(Friend *, char *);
void DeleteFriend(Friend *);

struct flist{
	unsigned short length;
	Friend *first;
	Friend *last;
};

FriendList *CreateFriendList(void);
bool isFriend(FriendList *, char *);
void AppendFriend(FriendList *, Friend *);
Friend *popFriend(FriendList *, char *);
void DeleteLastFriend(FriendList *);
void DeleteFriendList(FriendList *);

//=========== FriendRequest ============//
struct frq{
	char *from;
	char *to;
	FriendRequest *next;
	FriendRequest *prev;
};

FriendRequest *CreateFriendRequest(char *, char *);
void AppendFriendRequest(FriendRequestList *, FriendRequest *);
void DeleteFriendRequest(FriendRequest *);

struct frql{
	unsigned short length;
	char *uname;
	FriendRequest *first;
	FriendRequest *last;
};

/*declare recvupdate() to use in other files*/
int RecvUpdate();

FriendRequestList *CreateFriendRequestList(void);
void DeleteLastFriendRequest(FriendRequestList *);
FriendRequest *popFriendRequest(FriendRequestList *, FriendRequest *);
void DeleteFriendRequestList(FriendRequestList *);

unsigned char RequestAlreadyExists(FriendRequestList *, char *, char *);
void AppendFriendRequest(FriendRequestList *, FriendRequest *);

#endif
