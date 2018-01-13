/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Mohammed Haque                                            */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* allocate a new image entry */
static IENTRY *CreateImageEntry(void){
    
    IENTRY *e;
    e = malloc(sizeof(IENTRY));
    if (!e){
        perror("Out of memory! Aborting...");
        exit(10);
    }
    e->List = NULL;
    e->Next = NULL;
    e->Prev = NULL;
    
    return e;
}

/* delete an image entry */
static IMAGE *DeleteRGBImageEntry(IENTRY *e){

    IMAGE *image;
    assert(e);
    image = e->RGBImage;
    free(e);
    return image;
} 

static YUVIMAGE *DeleteYUVImageEntry(IENTRY *e){

    YUVIMAGE *YUVimage;
    assert(e);
    YUVimage = e->YUVImage;
    free(e);
    return YUVimage;
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *list;
    list = malloc(sizeof(ILIST));
    if (!list){
        perror("Out of memory! Aborting...");
        exit(10);
    }
    list->Length = 0;
    list->First = NULL;
    list->Last = NULL;
    return list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
    IENTRY *e, *n;

    assert(list);
    e = list->First;
    while (e){
        n = e->Next;
        if (e->RGBImage != NULL){
            e->RGBImage = DeleteRGBImageEntry(e);
            DeleteImage(e->RGBImage);
        }
        if (e->YUVImage != NULL){
            e->YUVImage = DeleteYUVImageEntry(e);
            DeleteYUVImage(e->YUVImage);
        }
        e = n; 
    }
    free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
    IENTRY *e = NULL;
    assert(list);  
    assert(RGBimage);
    e = CreateImageEntry();
    if (list->Last){
        e->List = list;   
        e->Next = NULL;
        e->Prev = list->Last;
        e->RGBImage = RGBimage;
        e->YUVImage = NULL;
        list->Last->Next = e;
        list->Last = e;
    }
    else{
        e->List = list;
        e->Next = NULL;
        e->Prev = NULL;
        e->RGBImage = RGBimage;
        e->YUVImage = NULL;
        list->First = e;
        list->Last = e;
    }
       
    list->Length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{   
    IENTRY *e = NULL;
    assert(list);
    assert(YUVimage);
    e = CreateImageEntry();    
    if (list->Last){
        e->List = list;
        e->Next = NULL;
        e->Prev = list->Last;
        e->YUVImage = YUVimage;
        e->RGBImage = NULL;
        list->Last->Next = e;
        list->Last = e;
    }
    else{
        e->List = list;
        e->Next = NULL;
        e->Prev = NULL;
        e->YUVImage = YUVimage;
        e->RGBImage = NULL;
        list->First = e;
        list->Last = e;
    }

    list->Length++;
}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
    assert(list);
    assert(start < end);
    assert(end <= list->Length);
    IENTRY *e, *n;
    unsigned int count = 0;    

    e = list->First;
    while (e){
        n = e->Next;        
        if (count < start){
            e->YUVImage = DeleteYUVImageEntry(e);
            e = n;
            list->First = e;
            count++;
            list->Length--;
            continue; 
        }
        else if (count >= start && count <= end){
            if (count <= end) list->Last = e;
            e = n;
            count++;
            continue;
        }
        else{
            e->YUVImage = DeleteYUVImageEntry(e);
            e = n;
            count++;
            list->Length--;
            continue;
        }
    }
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
    assert(list);
    assert(factor);
    IENTRY *e, *n;
    int count = 0;

    e = list->First;
    while (e){
        n = e->Next;
        if (count % factor != 0){
            e->YUVImage = DeleteYUVImageEntry(e);
            list->Length--;
            e = n;
            count++;
            continue;
        }
        e = n;
        count++;
    }
    list->Last = e;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
    assert(list);
    IENTRY *e, *n, *g, *h;
    ILIST *tmplist = CreateImageList();
    unsigned int count = list->Length;

    e = list->Last;
    while (count > 0){
        AppendYUVImage(tmplist, e->YUVImage);
        n = e->Prev;
        e = n;
        count--;
    }
    e = list->First;
    g = tmplist->First;
    while (e){
        n = e->Next;
        h = g->Next;
        e = g;
        e = n;
        g = h;
    }
    DeleteImageList(tmplist);
}

/* EOF */
