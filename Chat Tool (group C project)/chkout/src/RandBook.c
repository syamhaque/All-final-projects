#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned char *generateBook()
{
	unsigned char seed = (unsigned short)clock();
	srand(seed);
	unsigned short k, n = 0;
	unsigned char *book = calloc(sizeof(unsigned char), 256);
	book[0] = seed;
	for(n = 1; n < 256; n++)
	{
		book[n] = rand()%256;
		for(k = 0; k < n; k++)
		{
			if(book[k] == book[n])
				n--;
		}
	}
	return book;
}

unsigned char *recoverBook(unsigned char seed)
{	
	srand(seed);
	unsigned short k, n = 0;
	unsigned char *book = calloc(sizeof(unsigned char), 256);
	book[0] = seed;
	for(n = 1; n < 256; n++)
	{
		book[n] = rand()%256;
		for(k = 0; k < n; k++)
		{
			if(book[k] == book[n])
				n--;
		}
	}
	return book;
	
}

#ifdef RANDBOOK_C
int main()
{
	unsigned char *book = generateBook();
	unsigned char *book2 = recoverBook(book[0]);	

	unsigned short k, n = 0;
	for(n = 0; n < 256; n++)
	{
		for(k = 0; k < 256; k++)
		{
			if(k == book[n])
			{
				//printf("Worked at %d!\n", k);
				break;
			}
			else if(k == 255)
				printf("Failed at %d\n", k);
		}
		if(book[n] != book2[n])
			printf("Heck at %d!\n", n);
	}	

	printf("\n\n");
	free(book2);
	free(book);
	return 0;
}
#endif
