#######################################################################
# Homework Assignment 5, for EECS 22, Fall 2017
#
# Author: Mohammed Haque 
# Date: 11/09/2017
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
CC     = gcc -g
MAIN  = -DMAIN
CFLAGS = -ansi -Wall -c
LFLAGS = -ansi -Wall

# Default target
all: MovieLab

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: MovieLab.c DIPs.h FileIO.h Image.h ImageList.h Movie.h Constants.h
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o

# Target for FileIO.o
FileIO.o: FileIO.h FileIO.c Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

# Target for DIPs.o
DIPs.o: DIPs.h DIPs.c Constants.h
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o

# Target for Image.o
Image.o: Image.h Image.c
	$(CC) $(CFLAGS)  Image.c -o Image.o

# Target for ImageList.o
ImageList.o: ImageList.h ImageList.c
	$(CC) $(CFLAGS)  ImageList.c -o ImageList.o

# Target for Movie.o
Movie.o: Movie.h Movie.c
	$(CC) $(CFLAGS)  Movie.c -o Movie.o

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: MovieLab.o FileIO.o Image.o ImageList.o Movie.o DIPs.o
	$(CC) $(LFLAGS) $(MAIN) MovieLab.o FileIO.o Image.o ImageList.o Movie.o DIPs.o -o MovieLab

###############################  others  ##############################
# Target for clean-up
clean:
	rm -f *.o *.yuv MovieLab
