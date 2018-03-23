#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdbool.h>

unsigned char encryptPass(char input[], char *encryptedPassword);
void decryptPass(unsigned char *encryptedPassword, unsigned char *decryptedPassword);
void printBook(char book[]);
int authenticateUser(char uname[], char password[]);
void createUser(char uname[20], char password[20]);
void deleteUser(char uname[]);
bool isValidName(char uname[]);
bool isValidPassword(char password[]);// 0,t  1, f
int addToThread(char theadName[], char uname[], char message[]);
void createThread(char uname1[], char uname2[]);
void threadN(char threadName[], char uname1[], char uname2[]);
void allLower(char input[]);

#endif
