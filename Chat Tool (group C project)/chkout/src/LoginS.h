#ifndef LOGINS_H
#define LOGINS_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define FUFLAG \u
#define FPATH ./files/uinfos.chat

bool AuthUser(char *uname, char *pass);

bool NewUser(char *uname, char *pass, char *sQuestion, char *sQAnswer);

char *RetrievePassword(char *uname);
#endif
