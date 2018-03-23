README.txt

Authors:

Jesse Corrales-Lozano
Mohammed Haque
Jose Alberto Padilla
Jordan Paul Bonecutter
Ralph Hieu Cao Tran

Version: Beta 

Date: 3/4/2018

General Instructions:

1. Start by downloading and installing the tar file, refer to INSTALL.txt for more information on installation.

2. Navigate to the bin directory in order to begin running the programs.

3. Begin running the server on one window by typing "./Server <portnum>" into the command line.

4. In another window (and on the same account if desired) type "./Client <hostname> <portnum>" into the command line.

5. In the window running the client, you will be prompted to enter a Username and Password.

6. Once a username and password have been entered, you may begin messaging other users by first typing in your message, and then typing in the username of the person you are sending the message to.

*Current unimplemented features include all those related to friends (friend request, delete friend, contact list, etc.), saving messages, saving users, and GUI.
*For more information please refer to the User Manual.

More:
	Client:
		Navigate to the bin directory and type the command:
			
			[user@server] ./Client <servername> <portno>

		The program will then ask for your login credentials. At this point, the server recieves your credentials but does not
		check them against any database, so you will login successfully no matter what. Then you may request to send a message.
		It will ask for the message body and the username of the recipient, which will then be stored on the server and recieved
		by the recipient once they log on. To exit the program, do the following:

			
			[user@server] Enter your message:	
			[user@server] quit	
			[user@server] bye!


	Full_Client:
		Navigate to the bin directory and type the following command:
		
			[user@server] ./Full_Client <servername> <portno>

		Ensure you are connected with X11 forwarding enabled so that the GUI window will pop up. Enter your username and password
		and login. To create an account, use the register button (beta). For now, recieved messages will display in the terminal
		like so:


		Message:
		
		<message body>	

		Sender:
	
		<username of sender>

	
		To quit, simply hit the 'X' button.	

	Server:
		Navigate to the bin directory and type the command:
	
			[user@server] ./Server <portno>

		The server will then start up and automatically cycle through clients. Debug information is printed to the command line
		in green while warnings and errors are printed in red. As the server file is a somewhat repurposed version of the clock
		server example, it displays the time by default per Doemer's code. This will be removed in a successive update but for
		now it serves as an easy way of checking if the server is still running. Currently, the server can handle sending messages
		to multiple users. For example, if I login using the username jordan and a message pending for the user with username
		jordan is being held on the server, I will recive that message once my client file automatically checks for pending
		messages.

	GUI:
		Currently, the GUI is not connected to the server features yet. However typing "make GUI_Client" will creaet a proof
		of concept GUI execuatble running with GTK. This will be connected with the server by the beta release.

Bugs:
	Some memory leaks and more.

Features not implemented:
	A MessageLog stored in a text file, displaying message log on user side, friends.
