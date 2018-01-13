/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Mohammed Haque                                            */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"
#include <stdio.h>
/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
    MOVIE *movie = malloc(sizeof(MOVIE));

    if (movie == NULL){
        return NULL;
    }
    
    movie->Frames = CreateImageList();
   
    return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
    assert(movie);
    assert(movie->Frames);

    DeleteImageList(movie->Frames);

    movie->Frames = NULL;    

    free(movie);
    movie = NULL;
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
    assert(movie);
    assert(movie->Frames);
    IENTRY *curr;
    int x, y;
    int R, G, B;
    int Y, U, V;
    YUVIMAGE *tmpYUVimage;

    curr = movie->Frames->First;
    while (curr != NULL){
        tmpYUVimage = curr->YUVImage;
        curr->RGBImage = CreateImage(tmpYUVimage->W, tmpYUVimage->H);
        for (y = 0; y < tmpYUVimage->H; y++){
            for (x = 0; x < tmpYUVimage->W; x++){
                Y = GetPixelY(tmpYUVimage, x, y) - 16;
                U = GetPixelU(tmpYUVimage, x, y) - 128;
                V = GetPixelV(tmpYUVimage, x, y) - 128;       

                R = clip((298 * Y + 409 * V + 128) >> 8);
                G = clip((298 * Y - 100 * U - 208 * V + 128) >> 8);
                B = clip((298 * Y + 516 * U + 128) >> 8);
                
                SetPixelR(curr->RGBImage, x, y, R);
                SetPixelG(curr->RGBImage, x, y, G);
                SetPixelB(curr->RGBImage, x, y, B);
            }
        }        
        DeleteYUVImage(tmpYUVimage);
        curr->YUVImage = NULL;       
        curr = curr->Next; 
    }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{

    IENTRY *curr;
    int count, x, y;
    int R, G, B;
    int Y, U, V;
    IMAGE *tmpimage;    

    curr = movie->Frames->First;
    while (curr != NULL){
        tmpimage = curr->RGBImage;
        curr->YUVImage = CreateYUVImage(tmpimage->W,tmpimage->H);
        for (y = 0; y < tmpimage->H; y++){
            for (x = 0; x < tmpimage->W; x++){
                R = GetPixelR(tmpimage, x, y);
                G = GetPixelG(tmpimage, x, y);    
                B = GetPixelB(tmpimage, x, y);

                Y = clip(((66 * R + 129 * G + 25 * B + 128) >> 8) + 16);
                U = clip(((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128);
                V = clip(((112 * R - 94 * G - 18 * B + 128) >> 8) + 128);

                SetPixelY(curr->YUVImage, x, y, Y);
                SetPixelU(curr->YUVImage, x, y, U);
                SetPixelV(curr->YUVImage, x, y, V);
            }
        }  
        DeleteImage(tmpimage);
        curr->RGBImage = NULL;  
        curr = curr->Next;
        count++;
    }
}

int clip(int x){

    if (x < 0) return 0;
    else if (x > 255) return 255;
    else return x;

}

/* EOF */
