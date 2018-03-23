/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/*                                                                   */
/* Author: Mohammed Haque                                             */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw4.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include "Image.h"
#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Test.h"
/*** function declarations ***/

/* print a menu */
void PrintMenu();

/* Test all functions */
int main()
{

#ifdef DEBUG
	AutoTest();
	
#else
	int option;			/* user input option */
    char fname[SLEN];		/* input file name */
	IMAGE *image = NULL;

	PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);
    
	/* ColorFilter() parameters */
    int target_r, target_g, target_b, threshold;
    double factor_r, factor_g, factor_b;
    
	/* Noise() parameter */
	int n;

	/* Posterize() parameters */
	unsigned char rbits, gbits, bbits;	 			

	/* Crop() parameters */
	int x, y, W, H;

	/* Resize() parameters */
	int percentage;
	
	/* BrightnessAndContrast() parameters*/	
	int brightness, contrast;

	/* Equate to SaveImage() */
	int result;

	/* Watermark() parameters */
	IMAGE *watermark_Image = NULL;
	const char watermarkImgName[SLEN] = "watermark_template";	

	while (option != EXIT) {
		if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%79s", fname);
			image = LoadImage(fname);
		}
        
		/* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option <= 18) {
            if (! image)	 {
                printf("No image to process!\n");
            }
            /* now image is loaded */
            else {	
				switch (option) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%s", fname);
						result = SaveImage(fname, image);
						break;
					case 3:
                        BlackNWhite(image);
                        printf("\"Black & White\" operation is done!\n");
                        break;
					case 4:
                        Negative(image);
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
						
                        ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                        printf("\"Color Filter\" operation is done!\n");
                        break;
                    case 6:
                        Edge(image);
                        printf("\"Edge\" operation is done!\n");
                        break;
                    case 7:
                        Shuffle(image);
                        printf("\"Shuffle\" operation is done!\n");
                        break;
					case 8:
                        VFlip(image);
                        printf("\"VFlip\" operation is done!\n");
                        break;
					case 9:
                        VMirror(image);
                        printf("\"Vertically Mirror\" operation is done!\n");
                        break;
					case 11: 
						printf("Please input noise percentage: ");
						scanf("%d", &n);
						Noise(n, image);
						printf("\"Noise\" operation is done!\n");
						break;
					case 12:
						Sharpen(image);
						printf("\"Sharpen\" operation is done!\n"); 
						break;		
					case 13:
						printf("Enter the number of posterization bits for R chennel (1 to 8):");
						scanf("%hhu", &rbits);
						printf("Enter the number of posterization bits for G chennel (1 to 8):");
						scanf("%hhu", &gbits);
						printf("Enter the number of posterization bits for B chennel (1 to 8):");
						scanf("%hhu", &bbits);
						Posterize(image, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n");
						break;
					case 15:
						printf("Please enter the X offset value: ");
						scanf("%d", &x);
						printf("Please enter the Y offset value: ");
                        scanf("%d", &y);
						printf("Please input the crop width: ");
						scanf("%d", &W);
						printf("Please input the crop height: ");
                        scanf("%d", &H);
						image = Crop(image, x, y, W, H);
						printf("\"Crop\" operation is done!\n");
						break;
					case 16:
						printf("Please input the resizing percentage (integer between 1 - 500): ");
						scanf("%d", &percentage);
						image = Resize(image, percentage);
						printf("\"Resizing the image\" operation is done!\n");
                        break;
					case 17:
						printf("Please input the brightness level (integer between -255 - 255): ");
						scanf("%d", &brightness);
						printf("Please input the contrast level (integer between -255 - 255): ");
                        scanf("%d", &contrast);
						BrightnessAndContrast(image, brightness, contrast);
						printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
                        break;
					case 18:
						watermark_Image = LoadImage(watermarkImgName);
						Watermark(image, watermark_Image);
						DeleteImage(watermark_Image);
						watermark_Image = NULL;
						printf("\"Watermark\" operation is done!\n");
						break;
					case 19:
						AutoTest();
						if (AutoTest() != 0) {printf("AutoTest failed, error code %d", AutoTest());}
						else {printf("AutoTest finished successfully.");}
						break;
					
					default:
						break;

				}
			}
		}

		else if (option == 19) {
            AutoTest();
			if (AutoTest() != 0) {printf("AutoTest failed, error code %d", AutoTest());}
            else {printf("AutoTest finished successfully.");}
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
	printf("10: Add border to an image(not implemented)\n");
    printf("11: Add Noise to an image\n");
	printf("12: Sharpen an image\n");
	printf("13: Posterize an image\n");
	printf("14: Blur an image(not implemented)\n");
	printf("15: Crop an image\n");
	printf("16: Resize an image\n");
	printf("17: Adjust the Brightness and Contrast an image\n");
	printf("18: Add Watermark to an image\n");	
	printf("19: Test all functions\n");
    printf("20: Exit\n");
}

/* vim: set tabstop=4 softtabstop=4 shiftwidth=4 noexpandtab : */
