#include <gtk/gtk.h>

#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "assert.h"
#include "Constants.h"
#include "User.h"

/*struct to hold user's name and password when passing to other functions*/
typedef struct User_Credentials {
	gchar  *username;
	gchar *password;
	GtkWidget *username_entry;
	GtkWidget *password_entry;
	GtkWidget *password_entry2;
}USER;


//surface for cairo images
typedef struct SURFACE{
  cairo_surface_t *image;  
} surface;


/*struct to hold data to pass to functions*/
typedef struct Data{
	gpointer *data1;
	gpointer *data2;
	gpointer *data3;
	gpointer *data4;
	gpointer *friendData;
}DATA;
DATA *friendLabel;

/* make structs called friends, friendslist, friendsentry for functions addfriend, deletefriend, etc.*/
typedef struct Friends
{
	gpointer *friends;
	int manage;
}FRIENDS;
//global declaration 
FRIENDS *friends_tmp;
int manage_friend;

/*quits the window*/
gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);

/*Checks the textbox entries and if they are filled attempts a mock login*/
void gui_login(GtkWidget *widget, gpointer user);

/*Asks a new user for username and password and registers the user.*/
void gui_registerUser(GtkWidget *widget, gpointer user);

/*Makes the register new user screen*/
void gui_registerScreen(GtkWidget *widget);

/*Makes the Log In screen*/
void gui_loginScreen(gpointer user);

/*returns to the already made log in screen. Log in screen is only hidden not destroyed*/
void gui_returnToLoginScreen(GtkWidget *window, GtkWidget *widget);
	
/*Makes the main screen of the program. From here the user can access contacts and send messages.*/
void gui_mainScreen(GtkWidget *widget, gpointer data);

/*Sends the message*/
void gui_sendMessage(GtkWidget *widget, gpointer data);

/*Displays the sent messages*/
void gui_displayMessage(gpointer data, Message *);

/*Requests login*/
void gui_requestLogin();

/*logs out user*/
void gui_logout();

/*contacts list*/
void gui_contactsList(GtkWidget *widget, gchar *friendsname);

/* enter username to delete or add friend */
void gui_manageFriends(GtkWidget *widget, gpointer friends);

/* window that manages friends*/
void gui_manageFriendsWindow(GtkWidget *widget);

/*Prints error messages*/
void gui_printError(gchar *text);

/*Checks for impending messages and displays them*/
gboolean gui_receivePendingMessage(gpointer data);

void gui_showText(GtkWidget *widget, char *text);

gboolean on_expose_event (GtkWidget *widget, GdkEvent *event, gpointer data);

void do_drawing(gpointer data, GtkWidget *widget);

void gui_logo (GtkWidget *window, GtkWidget *darea, GtkWidget *box);
void test_logo(void);


#endif

