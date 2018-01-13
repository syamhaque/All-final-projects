/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Mohammed Haque                                            */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "ImageList.h"

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	char *fin = NULL;
	char *fout = NULL;

	unsigned int width = 480;
	unsigned int height = 270;    

    int count = 0;
    IENTRY *curr = NULL;

    MOVIE *movie = NULL;

    int aging=0, hflip=0, edge=0;
    int crop=0, fast=0, reverse=0;
    int water=0, zoom = 0;    

    /* LoadMovie() parameters */
    unsigned int frameNum = 146;    

    /* Watermark() parameters */
    char *watermark = NULL;
    unsigned int topLeftX, topLeftY;        
    srand(time(NULL));

    /* CropImageList() parameters */
    int start, end;

    /* FastImageList() parameters */
    int factor;
    
    /* Zoom() parameters */
    int percentage = 0;

	/* the while loop to check options in the command line */
	while (x < argc) {
		/* the input file name */
        if (strcmp(argv[x], "-i") == 0){
			if (x < argc - 1) {
			    fin = argv[x + 1]; 
                x += 2;
	    	} /*fi*/
		    else {
			   	printf("Missing argument for the input file name!\n");
			    return 5;
			} /*esle*/
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0){
			if (x < argc - 1) {
			    fout = argv[x + 1];
                x += 2;
	    	} /*fi*/
		    else {
			    printf("Missing argument for the output file name!\n");
			    return 5;
    	    } /*esle*/
			continue;
		} /*fi*/
        if (strcmp(argv[x], "-f") == 0){
            if (sscanf(argv[x+1], "%u", &frameNum) == 1) {
                if (x < argc - 1) {
                    x += 2; 
                } /*fi*/
                else {
                    printf("Missing argument for the Frame Number!\n");
                    return 5;
                } /*esle*/
            }
            continue;
        }
        if (strcmp(argv[x], "-s") == 0){
            if (sscanf(argv[x+1], "%ux%u", &width, &height) == 2) {
                if (x < argc - 1) {
                    x += 2;
                } /*fi*/
                else {
                    printf("Missing argument for the WIDTHxHEIGHT!\n");
                    return 5;
                } /*esle*/
            }
            continue;
        }
		/* the help option */
		if (strcmp(argv[x], "-h") == 0) {
			PrintUsage();
			return 0;
		} /*fi*/
        if (strcmp(argv[x], "-aging") == 0){
            x += 1;
            aging += 1;
            continue;
        }            
        if (strcmp(argv[x], "-hflip") == 0){
            x += 1;        
            hflip = 1;
            continue; 
        }
        if (strcmp(argv[x], "-edge") == 0){    
            x += 1;
            edge = 1;
            continue;
        }
        if (strcmp(argv[x], "-crop") == 0){
            if (sscanf(argv[x+1], "%d-%d", &start, &end) == 2) {
                if (x < argc - 1) {
                    x += 2;
                } 
                else {
                    printf("Missing argument for the start-end!\n");
                    return 5;
                } 
            }
            crop = 1;
            continue;
        }
        if (strcmp(argv[x], "-fast") == 0){
            if (sscanf(argv[x+1], "%d", &factor) == 1) {
                if (x < argc - 1) {
                    x += 2;
                } /*fi*/
                else {
                    printf("Missing argument for Factor!\n");
                    return 5;
                } /*esle*/
            }
            fast = 1;
            continue;
        }
        if (strcmp(argv[x], "-reverse") == 0){
            x += 1;
            reverse = 1;
            continue;
        }
        if (strcmp(argv[x], "-watermark") == 0){
            if (x < argc - 1) {
                watermark = argv[x + 1];
                strcat(watermark, ".ppm"); 
            }
            else{
                printf("Missing argument for Watermark file!\n");
                return 5;
            }
            x += 2;
            water = 1;
            continue;
        }
        if (strcmp(argv[x], "-zoom") == 0){
            x += 1;
            zoom = 1;
            continue;
        }
		x++;
	} /*elihw*/

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		return 5;
	}

    movie = LoadMovie(fin, frameNum, width, height);

    if (aging == 1){
        YUV2RGBMovie(movie);
        count = 0;
        curr = movie->Frames->First;
        while (curr != NULL) {
            curr->RGBImage = Aging(curr->RGBImage);
            curr = curr->Next;
            count++;
        }
        RGB2YUVMovie(movie);
        printf("Operation Aging is done!\n");
        aging = 0; 
    }
    if (hflip == 1){
        YUV2RGBMovie(movie);
        count = 0;
        curr = movie->Frames->First;
        while (curr != NULL) {
            curr->RGBImage = HFlip(curr->RGBImage);
            curr = curr->Next;
            count++;
        }
        RGB2YUVMovie(movie);
        printf("Operation HFlip is done!\n");
        hflip = 0;
    }
    if (edge == 1){
        YUV2RGBMovie(movie);
        count = 0;
        curr = movie->Frames->First;
        while (curr != NULL) {
            curr->RGBImage = Edge(curr->RGBImage);
            curr = curr->Next;
            count++;
        }
        RGB2YUVMovie(movie);
        printf("Operation Edge is done!\n");
        edge = 0;
    }
    if (crop == 1){
        CropImageList(movie->Frames, start, end);
        printf("Operation Crop is done! New number of frames is %u\n", movie->Frames->Length);
        crop = 0;
    }
    if (fast == 1){
        FastImageList(movie->Frames, factor);
        printf("Operation Fast is done! New number of frames is %u\n", movie->Frames->Length);
        fast = 0;
    }
    if (reverse == 1){
        ReverseImageList(movie->Frames);
        printf("Operation Reverse is done!\n");
        reverse = 0;
    }
    if (water == 1){
        YUV2RGBMovie(movie);
        count = 0;
        curr = movie->Frames->First;
        while (curr != NULL) {
            if (count % 15 == 0){
                topLeftX = rand() % width;
                topLeftY = rand() % height;
            }
            curr->RGBImage = Watermark(curr->RGBImage, LoadImage(watermark), topLeftX, topLeftY);
            curr = curr->Next;
            count++;
        }
        RGB2YUVMovie(movie);
        printf("Operation Watermark is done!\n");
        water = 0;
    }
    if (zoom == 1){
        YUV2RGBMovie(movie);
        count = 0;
        curr = movie->Frames->First;
        while (curr != NULL) {
            if (count < 50) percentage += 2;
            if (count >= 50 && count < 100) percentage -= 2;
            if (count >= 100 && count < 146) percentage += 2;             
            curr->RGBImage = Zoom(curr->RGBImage, percentage);
            curr = curr->Next;
            count++;    
        }
        RGB2YUVMovie(movie);
        printf("Operation Zoom is done!\n");
        water = 0;
    }

    SaveMovie(fout, movie);
    DeleteMovie(movie);
   
	fin = NULL;
	fout = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-aging                Activate the aging filter on every movie frame\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-zoom                 Zoom in and out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{
    int count;
    MOVIE *movie = CreateMovie();    
 
    assert(fname);
    assert(frameNum >= 0 && width > 0 && height > 0);    
    
    if (movie == NULL) {
        DeleteMovie(movie);
        return NULL;
    }
     
    count = 0;
    while (count < frameNum){
        AppendYUVImage(movie->Frames, LoadOneFrame(fname, count, width, height)); 
        count++;
    }

    printf("The movie file %s has been read successfully!\n", fname);

    return movie;
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int count;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}

	count = 0;
	curr = movie->Frames->First;
	while (curr != NULL) {

		SaveOneFrame(curr->YUVImage, fname, file);
		curr = curr->Next;
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname);
	return 0;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}

/* EOF */
