#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#include "RandBook.h"
#include "encryption.h"
// need to create a function that converts all unames to lowercase and replaces
// (spaces) with underscores

#ifdef ENCRYPTION
int main() {
	/* Stuff to be changed */
	char input[20], uname1[20], uname2[20];
	bool val_name, val_pass;
	printf("insert passwword: ");
	scanf("%s", input);
	/**/


	char *book, decryptedPassword[200];
	char encryptedPassword[200];
	memset(decryptedPassword, 0, 20);
	memset(encryptedPassword, '\0', 20);

	unsigned char seed = encryptPass(input, encryptedPassword);
	
	printf("\n******* Testing encryptPass() *******\n");
	printf("Password before encryption: %s\n", input);
	//encryptPass(input, book, encryptedPassword);
	printf("\nPassword after Encryption: %s", encryptedPassword);
	// for(int i = 0; i < strlen(input); i++){
	// 	x = (encryptedPassword[2*i] << 8 | encryptedPassword[2*i +1]);
	// 	printf("%d-", x);
	// }
	printf("\n");
	printf("\nLength of encryptedPassword: %d\n", strlen(encryptedPassword));
	printf("\n******* Testing decryptPass() *******\n");
	printf("Encrypted password: ");

	// for(int i = 0; i < strlen(input); i++){
	// 	x = (encryptedPassword[2*i] << 8 | encryptedPassword[2*i +1]);
	// 	printf("%d-", x);
	// }
	decryptPass(encryptedPassword, decryptedPassword);
	printf("\nAfter Decrypting: ");
	// for(int i = 0; i < strlen(decryptedPassword); i++){
	// 	printf("%c", decryptedPassword[i]);
	// }
	
	printf("%s", decryptedPassword);

	printf("\nLength of decryptedPassword: %d\n", strlen(decryptedPassword));

	// /***** Testing authenticateUser() function *****/  
	// printf("\n******* Testing authenticateUser() *******\n");
	// printf("Inputs: \nUsername: jesse\nPassword: Womton1!\n");
	// strcpy(uname1, "jesse");
	// strcpy(uname2, "Womton1!");
	// if(authenticateUser(uname1, uname2) == 0)
	// 	printf("Access Granted!\n\n");
	// else if(authenticateUser(uname1, uname2) == 1)
	// 	printf("Access Denied\n\n");
	// else
	// 	printf("User could not be found\n\n");
	
	// printf("Verify authenticateUser() function with \nUsername: jordan\nPassword: bonecutter\n");
	// strcpy(uname1, "jordan");
	// strcpy(uname2, "bonecutter");
	// if(authenticateUser(uname1, uname2) == 0)
	// 	printf("Access Granted!\n\n");
	// else if(authenticateUser(uname1, uname2) == 1)
	// 	printf("Access Denied\n\n");
	// else
	// 	printf("User could not be found\n\n");

	// printf("Verify authenticateUser() function with faulty info\nUsername: booby\nPassword: butt\n");
	// strcpy(uname1, "booby");
	// strcpy(uname2, "butt");
	// if(authenticateUser(uname1, uname2) == 0)
	// 	printf("Access Granted!\n\n");
	// else if(authenticateUser(uname1, uname2) == 1)
	// 	printf("Access Denied\n\n");
	// else
	// 	printf("User could not be found\n\n");

	// /*** Testing createUser() function ***/
	// printf("*****Testing createUser() function*****\n");
	// printf("Choose a username: ");
	// scanf("%s", uname1);
	// if(isValidName(uname1) == true)
	// 	val_name = true;
	// else
	// 	printf("Not a valid username, user already exists!\n");
	
	// printf("Choose a password: ");
	// scanf("%s", uname2);
	// if(isValidPassword(uname2) == true)
	// 	val_pass = true;
	// else 
	// 	printf("Invalid password. Does not meet the password requirements\n");
	// if(val_name && val_pass == true){
	// 	createUser(uname1, uname2);
	// 	printf("User successfully created.\n");
	// }

	// printf("\nTesting with an invalid username\n");
	// printf("Username: jordan, password: Qwerty1!\n");
	// strcpy(uname1, "jordan");
	// strcpy(uname2, "Qwerty1!");
	// if(isValidName(uname1) == true)
	// 	val_name = true;
	// else
	// 	printf("Not a valid username, user already exists!\n");
	
	// if(isValidPassword(uname2) == true)
	// 	val_pass = true;
	// else 
	// 	printf("Invalid password. Does not meet the password requirements\n");

	// printf("\nTesting with an invalid password\n");
	// printf("Username: abcde, password: aaaaa\n");
	// strcpy(uname1, "abcde");
	// strcpy(uname2, "aaaaa");
	// if(isValidName(uname1) == true)
	// 	val_name = true;
	// else
	// 	printf("Not a valid username, user already exists!\n");
	
	// if(isValidPassword(uname2) == true)
	// 	val_pass = true;
	// else 
	// 	printf("Invalid password. Does not meet the password requirements\n");

	// /***** Testing deleteUser() function *****/
	// printf("\n****** Testing deleteUser() *******\n");
	// printf("Pick the user you want to delete\n");
	// scanf("%s", input);
	// deleteUser(input);
	// fclose(fp);

	// /***** Testing createThread() function *****/
	// printf("\n*******Testing createThread() *******\n");
	// printf("The thread will be made between two users, Jesse and Nisha\n");
	// strcpy(uname1, "Jesse");
	// strcpy(uname2, "Nisha");
	// printf("The resulting filename will be: ");
	// createThread(uname1, uname2);

	// /***** Testing allLower() function *****/
	// printf("\n\n******* Testing allLower() *******");
	// char temp[] = "QWEasd Rt5%thb";
	// printf("\nInput before allLower(): %s", temp);
	// allLower(temp);
	// printf("\nInput after allLower() : ");
	// for(int i = 0; i < strlen(temp); i++){
	// 	printf("%c", temp[i]);
	// }
	
	// printf("\n");

	// /***** teasting addToThread() function *****/
	// printf("\n*****Testing addToThread() *******\n");
	// printf("Text being added from jesse: hello Nisha<3\n");
	// printf("Text being added from nisha: hello jesse<3 ur the best and better than me.\n");
	// addToThread("jessenisha.txt", "jesse", "hello Nisha<3");
	// addToThread("jessenisha.txt", "nisha", "hello jesse<3 ur the best and better than me.");	
}
#endif


void decryptPass(unsigned char *encryptedPassword, unsigned char *decryptedPassword){
	unsigned char *book = recoverBook(encryptedPassword[0]);
	int x, n = 0;

	for(n = 0; n < encryptedPassword[1]; n++)
	{
		decryptedPassword[n] = book[encryptedPassword[n + 2]];	
		x = n;
	}

	decryptedPassword[x + 1] = 0;
	
	free(book);
	//return &encryptedP;
}// end encrypt password

//void encryptPass(char input[], char book[], char *encryptedPassword){
unsigned char encryptPass(char input[], char *encryptedPassword){
	unsigned char *book = generateBook();
	unsigned char seed = book[0];	
	unsigned n, x;

	encryptedPassword[0] = seed;
	encryptedPassword[1] = strlen(input);

	for(n = 0; n < strlen(input); n++)
	{
		for(x = 0; x < 256; x++)
		{
			if(input[n] == book[x])
			{
				encryptedPassword[n + 2] = x;
				break;
			}
		}
	}
	free(book);
	return seed;
}// end encrypt password

void printBook(char book[]){
	printf("%s\n", book);
	// for(int i = 0; i < 1000; i++){
	// 	printf("%c ,", book[i]);
	// }
}

// this function accepts the already encrypted password
int authenticateUser(char uname[], char password[]){
	FILE *fp;
	char userInfo[20], temp[20];
	memset(temp, 0, sizeof(temp));
	if(password[strlen(password)] == '\n'){
		password[strlen(password)] = 0;
	}
	fp = fopen("../src/UserLoginInfo.txt", "r"); //opens the .txt file
	if(fp == NULL){
		printf("Error opening file accesing user login info.\n");
		return -1;
	}
	
	/* convert uname to lower case */
	allLower(uname);

	/* determines the length of the file*/
	fseek(fp, 0, SEEK_END);
	int fileLen = ftell(fp);
	rewind(fp);

	for(int i = 0; i < fileLen; i += 40){
		fseek(fp, i, SEEK_SET); // resets the file position indicater
		fgets(userInfo, strlen(uname)+1, fp); // reads the user name into the user info array
		printf("User name found: %s\n", userInfo);
		
		if(strcmp(userInfo, uname) == 0){ // if you find the desired user
			fseek(fp, i + 20, SEEK_SET); // move the pointer up 20 characters to where the password will be located
			int x, k;
			for(k = 0; k < 20; k++)
			{
				char c = fgetc(fp);
				if(c != '`')
				{
					userInfo[k] = c;
				}
				else
				{
					x = k;
					break;
				}
			}	
				
			memcpy(temp, userInfo, x*sizeof(char));
		
			temp[strlen(temp)] = 0;
	
			printf("Password found: %s\n", temp);
			printf("Password entered: %s\n", password);
			
			if(strcmp(temp, password) == 0){
				printf("Access granted\n");	
				fclose(fp);
				return 0; // access granted
			}
			else{
				printf("Access denied\n");	
				fclose(fp);
				return 1; // access denied	
			}
		}
	}
	fclose(fp);
	return -1; // this means that the user could not be found
}

void createUser(char uname[], char password[]){
	//char uname[20], password[20];
	//inputs are pre-verified	
	FILE *fp;
	fp = fopen("../src/UserLoginInfo.txt", "a");
	fseek(fp, 0, SEEK_END);	
	
	fwrite(uname, sizeof(char), strlen(uname), fp);
	fputc('`', fp);

	if(uname[strlen(uname)] == '\n')
		uname[strlen(uname)] = 0;

	if(uname[0] == '\n')
		uname[0] = 0;
	
	for(int i = 0; i < 20 - strlen(uname) - 1; i++){
		fputc('x', fp);
	}

	fwrite(password, sizeof(char), strlen(password), fp);
	
	fputc('`', fp);
	
	for(int i = 0; i < 20 - strlen(password) - 1; i++){
		fputc('x', fp);
	}
	fclose(fp);
}// end createUser()

void deleteUser(char uname[]){
	FILE *fp1, *fp2;
	fp1 = fopen("../src/UserLoginInfo.txt", "r");
	int startPos, endPos, endOfFile;
	char userInfo[20];

	/* determines the length of the file*/
	fseek(fp1, 0, SEEK_END);
	int fileLen = ftell(fp1);
	rewind(fp1);

	/* convert uname to lowercase */
	allLower(uname);

	for(int i = 0; i < fileLen; i += 40){
		fseek(fp1, i, SEEK_SET); // resets the file position indicater
		fgets(userInfo, strlen(uname)+1, fp1); // reads the user name into the user info array
		printf("User name found: %s\n", userInfo);
		if(strcmp(userInfo, uname) == 0){ // if you find the desired user
			startPos = i;
			endPos = i + 40;
			printf("Start Position: %d\nEnd Position: %d\n", startPos, endPos);
			break;
		}
	}

	fseek(fp1, 0, SEEK_SET); // reset the file pointer

	/* open up a nex text file to store all the data, except for the user being deleted */
	fp2 = fopen("../src/tmp.txt", "w");
	char c;
	// appends everything before the specificed user into the tmp.txt file
	for(int i = 0; i < startPos; i++){
		c = fgetc(fp1);
		fputc(c, fp2);
	}

	/* Determines the length of the original file */
	fseek(fp1, 0, SEEK_END); // set the file pointer to the end of file
	endOfFile = ftell(fp1);
	fseek(fp1, endPos, SEEK_SET); // reset the file pointer to endPos	
	// appends everything after the specificed user into the tmp.txt file
	for(int i = endPos; i < endOfFile; i++){
		c = fgetc(fp1);	
		fputc(c, fp2);
	}
	printf("\n");

	/* update info by deleting old file and renaming new one */
	if(remove("../src/UserLoginInfo.txt") != 0)
		perror("Error deleting ../src/UserLoginInfo.txt\n");
	else{
		if(rename("../src/tmp.txt", "../src/UserLoginInfo.txt") != 0){
			perror("Error in renaming tmp.txt\n");
		}
		printf("User successfully deleted\n");
	}

	fclose(fp1);
	fclose(fp2);
	printf("\n");
}

bool isValidName(char uname[]){
	FILE *fp;
	fp = fopen("../src/UserLoginInfo.txt", "r");
	char temp[20];

	/* determines the length of the file*/
	fseek(fp, 0, SEEK_END);
	int fileLen = ftell(fp);
	rewind(fp);

	for(int i = 0; i < fileLen; i += 40){
		fseek(fp, i, SEEK_SET); // resets the file position indicater
		fgets(temp, strlen(uname)+1, fp); // reads the user name into the temp array
		printf("User name found: %s\n", temp);
		if(strcmp(temp, uname) == 0){ // if you find the desired user
			fclose(fp);
			return false;
		}
	}
	fclose(fp);
	return true;
}

bool isValidPassword(char password[]){
	bool c_special, c_upper, c_lower; // password requirement flags
	char specialChar[] = {'!', '@', '#', '$', '%', '^', '&', '*', '`', '~', '.', '-', '?'};
	char upper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	char lower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	/* checks to make sure the password meets the length requirement */
	if(!(strlen(password) >= 8 && strlen(password) <= 20))
		return false;

	for(int i = 0; i < strlen(password); i++){
		/* checks if the password meets the special character requirement */
		for(int k = 0; k < strlen(specialChar); k++){
			if(password[i] == specialChar[k]){
				c_special = true;
				break;
			}
		}

		/* checks if the password meets the upper-case character requirement */
		for(int k = 0; k < strlen(upper); k++){
			if(password[i] == upper[k]){
				c_upper = true;
				break;
			}
		}

		/* checks if the password meets the lower-case character requirement */
		for(int k = 0; k < strlen(lower); k++){
			if(password[i] == lower[k]){
				c_lower = true;
				break;
			}
		}
	}

	if(c_special == true && c_upper == true && c_lower == true)
		return true; // if all requirements are met, then the password is valid
	else 
		return false;

	return true;
}

void createThread(char uname1[], char uname2[]){
	char *threadName;
	FILE *fp;
	int totalLen = strlen(uname1) + strlen(uname2);

	// // allocate space for the new char array
	threadName = malloc(totalLen + 5); // add 5 for .txt

	threadN(threadName, uname1, uname2);

	printf("%s", threadName);
	fp = fopen(threadName, "a");
	if(fp == NULL){
		printf("Error creating message thread.\n");
	}
	free(threadName);
	fclose(fp);
}

void threadN(char threadName[], char uname1[], char uname2[]){
	/* convert user names to lowercase */
	allLower(uname1);
	allLower(uname2);

	/* sort tha names in akphabetical order for naming convention */
	if(strcmp(uname1, uname2) < 0){
		strcpy(threadName, uname1);
		strcat(threadName, uname2);
	}else if(strcmp(uname1, uname2) > 0){
		strcpy(threadName, uname2);
		strcat(threadName, uname1);
	}
	strcat(threadName, ".txt");
}

int addToThread(char threadName[], char uname[], char message[]){
	FILE *fp;
	char *temp;
	temp = malloc(strlen(threadName) + 7); //  7 bytes for the path
	strcat(temp, "../src/");
	strcat(temp, threadName);

	fp = fopen(temp, "a");
	if(fp == NULL){
		printf("Error opening message thread.\n");
		return -1;
	}
	printf("Source for the file will be: %s", temp);
	/* start a new line, add user name, put a colon, append the message*/
	fputc('\n', fp);
	fwrite(uname, sizeof(char), strlen(uname), fp);
	fputs(": ", fp);
	fwrite(message, sizeof(char), strlen(message), fp);

	free(temp);
	fclose(fp);
	return 0;
}

void allLower(char input[]){
	/* converts every character to lowercase */
	for(int i = 0; i < strlen(input); i++){
		input[i] = tolower(input[i]);
	}
}
