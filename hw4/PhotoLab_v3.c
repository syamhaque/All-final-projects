/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/*                                                                   */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

/* Test all functions */
void AutoTest(void);

int main()
{
	int rc ;


#ifdef DEBUG
	AutoTest();
	rc = 0 ;
	
#else
	unsigned char R[WIDTH][HEIGHT];
	unsigned char B[WIDTH][HEIGHT];
	unsigned char G[WIDTH][HEIGHT];
 
	int option;			/* user input option */
    char fname[SLEN];		/* input file name */
    char colorOption[SLEN];	

	rc = 1 ;
	PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);

    
	/* ColorFilter() parameters */
    int target_r, target_g, target_b, threshold;
    double factor_r, factor_g, factor_b;
    
	/* AddBorder() parameter */
    int border_width;
    unsigned char rbits, gbits, bbits;
    
	/* Noise() parameter */
	int n;
	
	/* MotionBlur() parameter */
	int motion_amount; 
    
	 				
	while (option != EXIT) {
		if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            rc = LoadImage(fname, R, G, B);
		}
        
		/* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option <= 14) {
            if (rc != SUCCESS)	 {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else {	
				switch (option) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%s", fname);
						SaveImage(fname, R, G, B);
						break;
					case 3:
                        BlackNWhite(R, G, B);
                        printf("\"Black & White\" operation is done!\n");
                        break;
					case 4:
                        Negative(R,G,B);
                        printf("\"Negative\" operation is done!\n");
                        break;
                    case 5:
                        printf("Enter Red   component for the target color: ");
                        scanf("%d", &target_r);
                        printf("Enter Green component for the target color: ");
                        scanf("%d", &target_g);
                        printf("Enter Blue  component for the target color: ");
                        scanf("%d", &target_b);
                        printf("Enter threshold for the color difference: ");
                        scanf("%d", &threshold);
                        printf("Enter value for Red component in the target color: ");
                        scanf("%lf", &factor_r);
                        printf("Enter value for Green component in the target color: ");
                        scanf("%lf", &factor_g);
                        printf("Enter value for Blue  component in the target color: ");
                        scanf("%lf", &factor_b);
						
                        ColorFilter(R, G, B, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                        printf("\"Color Filter\" operation is done!\n");
                        break;
                    case 6:
                        Edge(R, G, B);
                        printf("\"Edge\" operation is done!\n");
                        break;
                    case 7:
                        Shuffle(R, G, B);
                        printf("\"Shuffle\" operation is done!\n");
                        break;
					case 8:
                        VFlip(R, G, B);
                        printf("\"VFlip\" operation is done!\n");
                        break;
					case 9:
                        VMirror(R, G, B);
                        printf("\"Vertically Mirror\" operation is done!\n");
                        break;
                    case 10:
                        printf("Enter border width:");
                        scanf("%d", &border_width);
                        printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                        printf("Select border color from the options: ");
                        scanf("%s",colorOption);
                        AddBorder(R, G, B, colorOption, border_width);
                        printf("\"Border\" operation is done!\n");
                        break;
					case 11: 
						printf("Please input noise percentage: ");
						scanf("%d", &n);
						Noise(n, R, G, B);
						printf("\"Noise\" operation is done!\n");
						break;
					case 12:
						Sharpen(R, G, B);
						printf("\"Sharpen\" operation is done!\n"); 
						break;		
					case 13:
						printf("Enter the number of posterization bits for R chennel (1 to 8):");
						scanf("%hhu", &rbits);
						printf("Enter the number of posterization bits for G chennel (1 to 8):");
						scanf("%hhu", &gbits);
						printf("Enter the number of posterization bits for B chennel (1 to 8):");
						scanf("%hhu", &bbits);
						Posterize(R, G, B, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n");
						break;
					case 14: 
						printf("Please input motion blur amount: ");
						scanf("%d", &motion_amount);
						MotionBlur(motion_amount, R, G, B);
						printf("\"Motion Blur\" operation is done!\n"); 
						break;

					case 15:
						AutoTest();
						rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
						break;
					
					default:
						break;

				}
			}
		}

		else if (option == 15) {
            AutoTest();
            rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }
		
		/* Process finished, waiting for another input */
        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
	}
    printf("You exit the program.\n");
#endif

	return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Make a negative of an image\n");
    printf(" 5: Color filter an image\n");
    printf(" 6: Sketch the edge of an image\n");
    printf(" 7: Shuffle an image\n");
    printf(" 8: Flip an image vertically\n");
    printf(" 9: Mirror an image vertically\n");
    printf("10: Add border to an image\n");
    printf("11: Add Noise to an image\n");
	printf("12: Sharpen an image\n");
	printf("13: Posterize an image\n");
	printf("14: Add Motion Blur to an image\n");
	printf("15: Test all functions\n");
    printf("16: Exit\n");
}


/* auto test*/

void AutoTest(void) {
	unsigned char R[WIDTH][HEIGHT] , G[WIDTH][HEIGHT], B[WIDTH][HEIGHT];     
    char fname[SLEN] = "HSSOE";


    LoadImage(fname, R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
    printf("Black & White tested!\n\n");
	
	LoadImage(fname, R, G, B);
    Negative(R, G, B);
    SaveImage("negative", R, G, B);
    printf("Negative tested!\n\n");

    LoadImage(fname, R, G, B);
    ColorFilter(R, G, B, 190, 100, 150, 60, 0, 0, 255);
    SaveImage("colorfilter", R, G, B);
    printf("Color Filter tested!\n\n");

    LoadImage(fname, R, G, B);
    Edge(R, G, B);
    SaveImage("edge", R, G, B);
    printf("Edge Detection tested!\n\n");

    LoadImage(fname, R, G, B);
    VMirror(R, G, B);
    SaveImage("vmirror", R, G, B);
    printf("VMirror tested!\n\n");

    
    LoadImage(fname, R, G, B);
    VFlip(R, G, B);
    SaveImage("vflip", R, G, B);
    printf("VFlip tested!\n\n");

    LoadImage(fname, R, G, B);
    Shuffle(R, G, B);
    SaveImage("shuffle", R, G, B);
    printf("Shuffle tested!\n\n");	
	
    LoadImage(fname, R, G, B);
    AddBorder (R, G, B, "yellow", 32);
    SaveImage("border", R, G, B);
    printf("Border tested!\n\n");

	LoadImage(fname, R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B);
    printf("Sharpen tested!\n\n");

	LoadImage(fname, R, G, B);
    Posterize(R, G, B, 7, 7, 7);
    SaveImage("posterize", R, G, B);
    printf("Posterize tested!\n\n");

	LoadImage(fname, R, G, B);
    Noise(90, R, G, B);
    SaveImage("noise", R, G, B);
    printf("Noise tested!\n\n");

	LoadImage(fname, R, G, B);
    MotionBlur(50, R, G, B);
    SaveImage("blur", R, G, B);
    printf("MotionBlur tested!\n\n");
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
