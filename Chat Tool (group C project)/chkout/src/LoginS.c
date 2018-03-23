#include "LoginS.h"

bool AuthUser(char *uname, char *pass)
{
	FILE load = fopen(FPATH, 'r');
	int stop = 0;	

	char cuser[30];
	char cpass[30];
	while(!strcmp(uname, cuser))
	{
		for(unsigned char n = 0; cuser[n] != '\\'; n++)
		{
			cuser[n] = fgetc(load);
		}
		bzero(cuser, sizeof(cuser));
		if(fgetc(load) == 'u')
		{	
			for(unsigned char n = 0; cuser[n] != '\\'; n++)
			{
				cuser[n] = fgetc(load);			
				stop = n;
			}
			cuser[stop] = 0;
		}
	}
	for(unsigned char n = 0; cpass[n] != '\\'; n++)
	{
		cpass[n] = fgetc(load);
		stop = n;
	}	
	cpass[stop] = 0;

	fclose(load);	

	if(!strcmp(cpass, pass))
		return true;
	return false;
}
