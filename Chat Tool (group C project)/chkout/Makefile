### MAKEFILE ###

#VARIABLES
SDIR 	= ./src/

### TARGETS ###

#Target for usage help
h:
	@echo ""
	@echo "Type \"make all\" to create both the client and server executables"
	@echo "Type \"make server\" to create the server execuatble"
	@echo "Type \"make client\" to create the client executable"	
	@echo "Type \"make Full_Client\" to create the GUI version of the client program"
	@echo "Type \"make Test_User\" to create the User.c unit test"
	@echo "Type \"make GUI_Client\" to create the GUI test"
	@echo "Type \"make clean\" to delete all *.o and executable files"
	@echo "Type \"make tar\" to create Chat_Alpha_src.tar.gz"
	@echo "All executable files will be found in the $(ODIR) directory and all *.o files will be found in the $(SDIR) directory"
	@echo ""

#Target to make all
all:
	cd $(SDIR) && make server && make Full_Client && make client && make Test_User

Full_Client:
	cd $(SDIR) && make Full_Client

server:
	cd $(SDIR) && make server

encryption_test:
	cd $(SDIR) && make encryption_test

client:
	cd $(SDIR) && make client

GUI_Client: 
	cd $(SDIR) && make GUI_Client
	
Test_Contacts:
	cd $(SDIR) && make Test_Contacts
	
Test_GUI:
	cd $(SDIR) && make Test_GUI

Test_User:
	cd $(SDIR) && make Test_User
Logo_Test:
	cd $(SDIR) && make Logo_Test

clean:
	cd $(SDIR) && make clean

clean_tar:
	rm *.gz

tar_user:
	make clean
	make client
	make Full_Client
	make server
	gtar -cvzf Chat_V1.0.tar.gz doc bin README.txt INSTALL.txt COPYRIGHT.txt src --exclude=src/*.o --exclude=src/*.c --exclude=src/*.h
	make clean

tar:
	make clean
	make server
	make client
	make Full_Client
	gtar -cvzf Chat_V1.0_src.tar.gz doc bin src Makefile README.txt INSTALL.txt COPYRIGHT.txt
	make clean
