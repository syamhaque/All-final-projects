### MAKEFILE ###

#VARIABLES
ODIR	= ../bin/
FLAG 	= -Wall -ansi -std=c99
CFLAG 	= -c $(FLAG)
SRC 	= CatChat
GTKINC	= `pkg-config --cflags gtk+-2.0`
GTKLIBS	= `pkg-config --libs gtk+-2.0`
CAIROLIBS = `pkg-config --cflags --libs cairo`
DEBUG	= -O2
GTKCFLAGS = -g -Wall -ansi -std=c99 $(DEBUG) $(GTKINC) -c
GTKLFLAGS = -g -Wall -ansi -std=c99 $(DEBUG) $(GTKLIBS)
### TARGETS ###

#Target for usage help
h:
	@echo ""
	@echo "Type \"make all\" to create both the client and server executables"
	@echo "Type \"make server\" to create the server execuatble"
	@echo "Type \"make client\" to create the client executable"	
	@echo "Type \"make GUI_Client\" to create the GUI version of the client program"
	@echo "Type \"make clean\" to delete all *.o and executable files"
	@echo "All executable files will be found in the $(ODIR) directory and all *.o files will be found in the ./src/ directory"
	@echo ""

#Target to make all
Full_Client: Full_Client.o Full_GUI.o User.o encryption.o RandBook.o
	gcc $(GTKLFLAGS) Full_GUI.o Full_Client.o User.o encryption.o RandBook.o -o $(ODIR)Full_Client

server: Server.o User.o Constants.h encryption.o RandBook.o
	gcc $(FLAG) Server.o User.o encryption.o RandBook.o -o $(ODIR)Server

encryption_test: encryption_test.o RandBook.o
	gcc encryption_test.o RandBook.o -o $(ODIR)encryption_test

client: User.o encryption.o Client.o User.o RandBook.o
	gcc $(FLAG) Client.o User.o encryption.o RandBook.o -o $(ODIR)Client

GUI_Client: GUI.o GUI_Client.o User.o
	gcc $(GTKLFLAGS) $(CAIROLIBS) GUI.o GUI_Client.o User.o -o $(ODIR)GUI_Client
	
Test_GUI: Test_GUI.o Test_GUI_Client.o User.o
	gcc $(GTKLFLAGS) Test_GUI.o Test_GUI_Client.o User.o -o $(ODIR)Test_GUI

Test_Contacts: Test_Contacts.o Test_GUI_Client.o User.o
	gcc $(GTKLFLAGS) Test_Contacts.o Test_GUI_Client.o User.o -o $(ODIR)Test_Contacts

Server.o: Server.c User.h Constants.h encryption.h
	gcc $(CFLAG) Server.c -o Server.o

Client.o: Client.c User.h Constants.h encryption.h
	gcc $(CFLAG) Client.c -o Client.o

encryption.o: encryption.c encryption.h RandBook.h
	gcc $(CFLAG) encryption.c -o encryption.o

encryption_test.o: encryption.c encryption.h RandBook.h
	gcc $(CFLAG) -DENCRYPTION encryption.c -o encryption_test.o
	
Full_Client.o: Client.c User.h Constants.h GUI.h
	gcc $(GTKCFLAGS) -DFULL_CLIENT Client.c -o Full_Client.o
	 
User.o: User.c User.h
	gcc $(CFLAG) User.c -o User.o

GUI.o: GUI.c GUI.h User.h
	gcc $(GTKCFLAGS) GUI.c -o GUI.o
	
Full_GUI.o: GUI.c GUI.h Constants.h User.h
	gcc $(GTKCFLAGS) -DFULL_CLIENT GUI.c -o Full_GUI.o

GUI_Client.o: GUI_Client.c GUI.h User.h
	gcc $(GTKCFLAGS) GUI_Client.c -o GUI_Client.o

Test_Contacts.o: GUI.c GUI.h User.h
	gcc $(GTKCFLAGS) -DTEST_CONTACTS GUI.c -o Test_Contacts.o

Test_GUI.o: GUI.c GUI.h User.h
	gcc $(GTKCFLAGS) -DTEST_GUI GUI.c -o Test_GUI.o

Test_GUI_Client.o: GUI_Client.c GUI.h User.h
	gcc $(GTKCFLAGS) -DTEST_GUI GUI_Client.c -o Test_GUI_Client.o

RandBook.o: RandBook.c RandBook.h
	gcc $(CFLAG) RandBook.c -o RandBook.o

Test_User: User.c User.h
	gcc $(FLAG) -DUSER_MAIN User.c -o $(ODIR)UserTest

Logo_Test: logotest.c
	gcc -ansi -Wall -std=c99 `pkg-config --libs --cflags cairo` `pkg-config --libs --cflags gtk+-2.0` logotest.c -o $(ODIR)Logo_Test

clean:
	rm -f *.o
	rm -f $(ODIR)Server
	rm -f $(ODIR)Client
	rm -f $(ODIR)GUI_Client
	rm -f $(ODIR)Test_GUI
	rm -f $(ODIR)Full_Client
	rm -f $(ODIR)UserTest
	rm -f $(ODIR)logotest
