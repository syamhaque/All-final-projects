#######################################################################
# Project1, for EECS 22L, Winter 2017
#
# Author: Team 19
# Date: 1/20/2018
#
#
#######################################################################

# Variables
DESIGN = Chess
CC = gcc
CFLAGS = -Wall -ansi -c -std=c99 -g
LFLAGS = -ansi -Wall -g
EXE = ../bin/
#TAR = ../chess/
# Default target

all: $(EXE)Chess
######################### Generate object files #######################

board.o: constants.h board.h board.c
		$(CC) $(CFLAGS) board.c -o board.o

User_Move.o: User_Move.h User_Move.c AI_Move.h constants.h board.h
		$(CC) $(CFLAGS) User_Move.c -o User_Move.o	

ChessPieces.o: ChessPieces.h ChessPieces.c AI_Move.h constants.h User_Move.h board.h
		$(CC) $(CFLAGS) ChessPieces.c -o ChessPieces.o

Chess.o: Chess.c ChessPieces.h board.h User_Move.h AI_Move.h constants.h 
		$(CC) $(CFLAGS) Chess.c -o Chess.o
   
#AI_Random.o: AI_Random.c ChessPieces.h board.h constants.h User_Move.h
#		$(CC) $(CFLAGS) AI_Random.c -o AI_Random.o
AI_Move.o: AI_Move.h AI_Move.c board.h ChessPieces.h User_Move.h constants.h
	$(CC) $(CFLAGS) AI_Move.c -o AI_Move.o

######################### Generate the executable #####################

$(EXE)Chess: Chess.o ChessPieces.o User_Move.o board.o AI_Move.o
	$(CC) $(LFLAGS) Chess.o ChessPieces.o User_Move.o board.o AI_Move.o -o $(EXE)Chess

#$(EXE)Chess: Chess.o ChessPieces.o User_Move.o board.o AI_Random.o
		#$(CC) $(LFLAGS) Chess.o ChessPieces.o User_Move.o board.o AI_Random.o -o $(EXE)Chess 
tar: 
	tar -cvf Chess_V1.0_src.tar.gz ~/chess/
	tar -cvf Chess_V1.0.tar.gz ~/user/

clean:
	rm -f *.o $(EXE)Chess $(DESIGN)
