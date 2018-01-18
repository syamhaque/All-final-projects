#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Image.h"

IMAGE *CreateImage(unsigned int Width, unsigned int Height){

	IMAGE *image;
	image = malloc(sizeof(IMAGE));
	
	if (!image){

		perror("Out of memory! Aborting...");
        exit(10);
            
	}
    if(!(image->R = (unsigned char*)malloc(sizeof(unsigned char)*Width*Height))) return NULL;
	if(!(image->G = (unsigned char*)malloc(sizeof(unsigned char)*Width*Height))) return NULL;
    if(!(image->B = (unsigned char*)malloc(sizeof(unsigned char)*Width*Height))) return NULL;

    image->W = Width;
    image->H = Height;
    	
	return image;
}

void DeleteImage(IMAGE *image){
	
	assert(image);

    assert(image->R);
    assert(image->G);
    assert(image->B);

    free(image->R);
    free(image->G);
    free(image->B);
    
    image->R = NULL;
    image->G = NULL;
    image->B = NULL;

	free(image);

}

unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y){
    assert(image);
	assert(x < ImageWidth(image));
    assert(y < ImageHeight(image));
    assert(image->R);    

    unsigned char *r = image->R;
    return *(r+x+(ImageWidth(image)*y));    

}

unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y){
    assert(image);
    assert(x < ImageWidth(image));
    assert(y < ImageHeight(image));
    assert(image->G);

    unsigned char *g = image->G;
    return *(g+x+(ImageWidth(image)*y));
}


unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y){
    assert(image); 
    assert(x < ImageWidth(image));
    assert(y < ImageHeight(image));
    assert(image->B);

    unsigned char *b = image->B;
    return *(b+x+(ImageWidth(image)*y));
}


void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r){
    assert(image);
    assert(x < ImageWidth(image));
    assert(y < ImageHeight(image));
    assert(image->R);
    assert(r <= 255);
    assert(r >= 0);

    *(image->R + x + ImageWidth(image)*y) = r;    
}


void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g){
    assert(image);
    assert(x < ImageWidth(image));
    assert(y < ImageHeight(image));
    assert(image->G);
    assert(g <= 255);
    assert(g >= 0);

    *(image->G + x + ImageWidth(image)*y) = g;
}


void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b){
    assert(image);
    assert(x < ImageWidth(image));
    assert(y < ImageHeight(image));
    assert(image->G);
    assert(b <= 255);
    assert(b >= 0);

    *(image->B + x + ImageWidth(image)*y) = b;
}

unsigned int ImageWidth(const IMAGE *image){

	return image->W;

}

unsigned int ImageHeight(const IMAGE *image){

	return image->H;

}
