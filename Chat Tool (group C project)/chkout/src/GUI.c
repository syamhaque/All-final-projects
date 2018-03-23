#include "GUI.h"
#include "Constants.h"
#include "User.h"

char uname[BSIZE];

/*Checks the textbox entries and if they are filled attempts a mock login*/
void gui_login(GtkWidget *widget, gpointer user){
	USER *user_tmp = (USER*) user;
	friendLabel = g_malloc(sizeof(*friendLabel));
	friendLabel->friendData = NULL;
	if(gtk_entry_get_text_length(GTK_ENTRY(user_tmp->username_entry)) == 0){
		g_print("Please enter an username.\n");
		gui_printError("Please enter an username.\n");
	}
	else if(gtk_entry_get_text_length(GTK_ENTRY(user_tmp->password_entry)) == 0){
		g_print("Please enter a password.\n");
		gui_printError("Please enter a password.\n");
	}
	else{
		user_tmp->username = gtk_entry_get_text(GTK_ENTRY(user_tmp->username_entry));
		strcpy(uname, user_tmp->username);
		user_tmp->password = gtk_entry_get_text(GTK_ENTRY(user_tmp->password_entry));
		#ifdef FULL_CLIENT
		INPUT = 1;
		#endif //FULL_CLIENT
		#ifdef TEST_GUI
		g_print("Login attempted with username %s and password %s\n", user_tmp->username, user_tmp->password);
		#endif //TEST_GUI
		//gtk_widget_hide(gtk_widget_get_toplevel (widget));
		#ifdef FULL_CLIENT
		if(LOGGED_IN){
			gtk_widget_hide(gtk_widget_get_toplevel (widget));
			gui_mainScreen(NULL, NULL);
		}
		#endif
		#ifndef FULL_CLIENT
		gui_mainScreen(NULL, NULL);
		#endif
	}
}

void gui_requestLogin(){
	LOGIN_REQUEST = 1;
}

void memserverq()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	char buff[BSIZE];
	memset(buff, 0, sizeof(buff));	
	buff[0] = M_Logout;

	strcat(buff, uname);	

	if(!(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0))
	{
		if(write(sockfd, buff, strlen(buff)) < 0)
		{
			printf("BAD WRITE\n\n\n\n");
		}
	
		g_print("Wrote string: %s\n\n", buff);
	
		memset(buff, 0, sizeof(buff));	
		if(read(sockfd, buff, sizeof(buff)) < 0)
		{
			printf("BAD READ\n\n\n\n");
		}

		g_print("Recived string: %s\n\n", buff);

		if(buff[0] != 'S')
			printf("BAD STUFF\n\n\n\n");
	}
	exit(0);
}

/*quits the window*/
gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data){
	#ifndef FULL_CLIENT
	gtk_main_quit();
	#endif
	
	#ifdef FULL_CLIENT
	GUI_QUIT = 1;
	#endif
	return FALSE;
}

/*Makes the register new user screen*/
void gui_returnToLoginScreen(GtkWidget *window, GtkWidget *widget){
	if(window != gtk_widget_get_toplevel (widget)){
		gtk_widget_destroy(window);
	}
	gtk_widget_show_all(gtk_widget_get_toplevel (widget));
}

/*Asks a new user for username and password and registers the user.*/
void gui_registerUser(GtkWidget *widget, gpointer user){
	USER *user_tmp = (USER*) user;
	if(gtk_entry_get_text_length(GTK_ENTRY(user_tmp->username_entry)) == 0){
		g_print("Please enter an username.\n");
		gui_printError("Please enter an username.\n");
	}
	else if(gtk_entry_get_text_length(GTK_ENTRY(user_tmp->password_entry)) == 0){
		g_print("Please enter a password.\n");
		gui_printError("Please enter a password.\n");
	}
	else if(gtk_entry_get_text_length(GTK_ENTRY(user_tmp->password_entry2)) == 0){
		g_print("Please confirm password.\n");
		gui_printError("Please confirm password.\n");
	}
	else if(!g_strcmp0(gtk_entry_get_text(GTK_ENTRY(user_tmp->password_entry)), gtk_entry_get_text(GTK_ENTRY(user_tmp->password_entry2)))){
		user_tmp->username = gtk_entry_get_text(GTK_ENTRY(user_tmp->username_entry));
		user_tmp->password = gtk_entry_get_text(GTK_ENTRY(user_tmp->password_entry));
		#ifdef TEST_GUI
		g_print("Registration attempted with username %s and password %s\n", user_tmp->username, user_tmp->password);
		#endif
		#ifdef FULL_CLIENT
		strcpy(USERNAME, user_tmp->username);	
		strcpy(PASSWORD, user_tmp->password);
		
		INPUT = 1;
		#endif
		//g_free(user_tmp);
		//gtk_widget_destroy(gtk_widget_get_toplevel (widget));
		//g_list_foreach(gtk_window_list_toplevels (), (GFunc)gtk_widget_show_all, NULL);
	}
	else{
		#ifdef TEST_GUI
		g_print("Password fields do not match!\n");
		#endif
		#ifdef FULL_CLIENT
		gui_printError("Password fields do not match!");
		#endif
	}
}

/*Makes the Log In screen*/
void gui_loginScreen(gpointer user){
	GtkWidget *window;
	GtkWidget *user_entry, *pass_entry;
	GtkWidget *button;
	GtkWidget *box;
	GtkWidget *label;
	GtkWidget *text_view;
	GtkTextBuffer *buffer;

	//for logo
	GtkWidget *darea;
	GtkImage *logo ;
	GtkImage *loginbutton;
	GdkPixbuf *pixbuf;

	USER *user_data = (USER*) user;
	
	/*Create window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	
	/*Connects delete_event signal to main window so that it closes when the X is clicked*/
	//g_signal_connect(window, "delete_event", G_CALLBACK(memserverq), NULL);
	g_signal_connect(window, "delete_event", G_CALLBACK(delete_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	
	/*Create a vertical box (vbox) to put the text entry fields and login, register, etc. buttons*/
	box = gtk_vbox_new(FALSE, 0);

	//creates logo at top
	// surface *surface_tmp = g_malloc(sizeof(*surface_tmp));
	// surface_tmp->image = NULL;
	// surface_tmp->image = cairo_image_surface_create_from_png("logo.png");
	// darea = gtk_drawing_area_new();
	// gui_logo (window, darea, box);
	// pixbuf = gdk_pixbuf_new_from_file ("logo.bmp", error);
	logo = gtk_image_new_from_file ("logo.png");
    label = gtk_label_new("CatChat");
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,10);
	gtk_widget_show(label);
	// gtk_image_set_from_file (logo, "logo.png");
	gtk_box_pack_start(GTK_BOX(box), GTK_IMAGE(logo), FALSE, FALSE, 10);
	gtk_widget_show(logo);
	// g_signal_connect(G_OBJECT(darea), "expose-event", G_CALLBACK(on_expose_event), surface_tmp); 
	// test_logo();
	loginbutton = gtk_image_new_from_file("tigerbutton.png");

	/*Creates text view*/
	buffer = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text (buffer, "For admin accounts use Name: amadeos Pass: Lobo123! or Name: jesse Pass: Womton1!", -1);
	text_view = gtk_text_view_new_with_buffer (buffer);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
	gtk_box_pack_start(GTK_BOX(box), text_view, FALSE, FALSE, 0);
	gtk_widget_show(text_view);
	
	/*Creates entry for username*/
	label = gtk_label_new("Username");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	user_entry = gtk_entry_new();
	user_data->username_entry = user_entry;
	g_signal_connect_swapped(user_entry, "activate", G_CALLBACK(gui_requestLogin), NULL);
	g_signal_connect(user_entry, "activate", G_CALLBACK(gui_login), user_data);
	gtk_box_pack_start(GTK_BOX(box),user_entry,FALSE,FALSE,10);
	gtk_widget_show(user_entry);
		
	/*Creates entry for password*/
	label = gtk_label_new("Password");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	pass_entry = gtk_entry_new();
	user_data->password_entry = pass_entry;
	gtk_entry_set_visibility(GTK_ENTRY(pass_entry), FALSE);
	g_signal_connect_swapped(pass_entry, "activate", G_CALLBACK(gui_requestLogin), NULL);
	g_signal_connect(pass_entry, "activate", G_CALLBACK(gui_login), user_data);
	gtk_box_pack_start(GTK_BOX(box),pass_entry,FALSE,FALSE,0);
	gtk_widget_show(pass_entry);
	
	/*Creates login button*/
	button = gtk_button_new_with_label("Login");
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gui_requestLogin), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(gui_login), user_data);
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);

    gtk_button_set_image (GTK_BUTTON (button), GTK_IMAGE(loginbutton));

	gtk_widget_show(button);
	
	/*Creates register button*/
	button = gtk_button_new_with_label("Register");
	g_signal_connect(button, "clicked", G_CALLBACK(gui_registerScreen), NULL);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), window);
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
	gtk_widget_show(button);
	
	gtk_widget_show(box);
	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_widget_show(window);
}

/*Makes the register new user screen*/
void gui_registerScreen(GtkWidget *widget){ 
	REGISTER_REQUEST = 1;
	GtkWidget *register_window;
	GtkWidget *name_entry, *pass_entry1, *pass_entry2;
	GtkWidget *button;
	GtkWidget *box;
	GtkWidget *label;
	USER *user_tmp = g_malloc(sizeof(*user_tmp));
	user_tmp->username_entry = NULL;
	user_tmp->password_entry = NULL;
	/*Create new window*/
	register_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*) register_window, 500, 500);
	//g_signal_connect(register_window, "delete_event", G_CALLBACK(memserverq), NULL);
	g_signal_connect(register_window, "delete_event", G_CALLBACK(delete_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(register_window), 10);
	/*Create a vertical box (vbox) to put the text entry fields and register button*/
	box = gtk_vbox_new(FALSE, 0);
	/*Creates entry for username*/
	label = gtk_label_new("Username");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	name_entry = gtk_entry_new();
	user_tmp->username_entry = name_entry;
	g_signal_connect(name_entry, "activate", G_CALLBACK(gui_registerUser), user_tmp);
	gtk_box_pack_start(GTK_BOX(box),name_entry,FALSE,FALSE,0);
	gtk_widget_show(name_entry);
	/*Creates entry for password*/
	label = gtk_label_new("Password");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	pass_entry1 = gtk_entry_new();
	user_tmp->password_entry = pass_entry1;
	gtk_entry_set_visibility(GTK_ENTRY(pass_entry1), FALSE);
	g_signal_connect(pass_entry1, "activate", G_CALLBACK(gui_registerUser), user_tmp);
	gtk_box_pack_start(GTK_BOX(box),pass_entry1,FALSE,FALSE,0);
	gtk_widget_show(pass_entry1);
	/*Creates entry for password*/
	label = gtk_label_new("Confirm Password");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	pass_entry2 = gtk_entry_new();
	user_tmp->password_entry2 = pass_entry2;
	gtk_entry_set_visibility(GTK_ENTRY(pass_entry2), FALSE);
	g_signal_connect(pass_entry2, "activate", G_CALLBACK(gui_registerUser), user_tmp);
	gtk_box_pack_start(GTK_BOX(box),pass_entry2,FALSE,FALSE,0);
	gtk_widget_show(pass_entry2);
	/*Creates register button*/
	button = gtk_button_new_with_label("Register");
	g_signal_connect(button, "clicked", G_CALLBACK(gui_registerUser), user_tmp);
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
	gtk_widget_show(button);
	/*Show window*/
	gtk_widget_show(box);
	gtk_container_add(GTK_CONTAINER(register_window), box);
	gtk_widget_show(register_window);
}

void gtk_entry_buffer_set_text_clr(void *l, GtkEntryBuffer *b)
{
	gtk_entry_buffer_set_text(b, (gchar *)"", 0);
}

/*Makes the main screen of the program. From here the user can access contacts and send messages.*/
void gui_mainScreen(GtkWidget *widget, gpointer data){
	GtkWidget *window, *scrolled_window;
	GtkWidget *button;
	GtkWidget *box, *box2, *hbox, *vbox1, *vbox2;
	GtkWidget *entry, *name_entry;
	GtkWidget *label;
	

	// GtkWidget *darea;
	// GtkWidget *chatwindow;
	// cairo_surface_t *surface;
	// cairo_t *cr;

	GtkEntryBuffer *buffer;
	DATA *data_tmp = g_malloc(sizeof(*data_tmp));
	data_tmp->data1 = NULL;
	data_tmp->data2 = NULL;
	data_tmp->data3 = NULL;

	/*Create window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*) window, 500, 500);
	
	/*Connects delete_event signal to main window so that it closes when the X is clicked*/
	g_signal_connect(window, "delete_event", G_CALLBACK(memserverq), NULL);
	g_signal_connect(window, "delete_event", G_CALLBACK(delete_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	
	/*Create a vertical box  to put the text entry fields and login, register, etc. buttons*/
	box = gtk_vbox_new(FALSE, 0);
	/*Creates vertical box to be put inside scrolled window to display messages in*/
	box2 = gtk_vbox_new(FALSE, 0);
	/*horizontal box to put inside previous vertical box*/
	hbox = gtk_hbox_new(FALSE, 0);
	/*vbox to put inside previous hbox*/
	vbox1 = gtk_vbox_new(FALSE, 0);
	/*vbox to put inside previous hbox*/
	vbox2 = gtk_vbox_new(FALSE, 0);
	
	/*put boxes inside of each other*/
	gtk_box_pack_start(GTK_BOX(box2), hbox, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), vbox1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), vbox2, FALSE, FALSE, 0);
	
	/*Creates a scroll window to display the sent and received messages.*/
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request (scrolled_window, scrolled_window->allocation.width-1+500, scrolled_window->allocation.height-1+300);
	gtk_box_pack_start(GTK_BOX(box),scrolled_window, FALSE, FALSE, 0);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), box2);
	gtk_widget_show(scrolled_window);
	gtk_widget_show(box2);
	gtk_widget_show(hbox);
	gtk_widget_show(vbox1);
	gtk_widget_show(vbox2);
	data_tmp->data3 = vbox2;
	data_tmp->data4 = vbox1;
		
	/*Creates text entry for the username to send the message to*/
	label = gtk_label_new("Username");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	name_entry = gtk_entry_new();
	if(data){
		gtk_entry_set_text(name_entry, data);
		data_tmp->data1 = name_entry;	
		g_signal_connect(name_entry, "activate", G_CALLBACK(gui_sendMessage), data_tmp);
		gtk_box_pack_start(GTK_BOX(box),name_entry,FALSE,FALSE,0);
		gtk_widget_show(name_entry);
	}
	else{
		data_tmp->data1 = name_entry;
		g_signal_connect(name_entry, "activate", G_CALLBACK(gui_sendMessage), data_tmp);
		gtk_box_pack_start(GTK_BOX(box),name_entry,FALSE,FALSE,0);
		gtk_widget_show(name_entry);
	}
		
	/*Creates text entry for writing messages*/	
	DATA *param = calloc(sizeof(DATA), 1);
	label = gtk_label_new("Message");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	buffer = gtk_entry_buffer_new(NULL, -1);
	param->data1 = buffer;
	data_tmp->data2 = buffer;
	entry = gtk_entry_new_with_buffer (buffer);
	g_signal_connect(entry, "activate", G_CALLBACK(gui_sendMessage), data_tmp);
	g_signal_connect(entry, "activate", G_CALLBACK(gtk_entry_buffer_set_text_clr), buffer);
	gtk_box_pack_start(GTK_BOX(box),entry,FALSE,FALSE,0);
	gtk_widget_show(entry);
	
	/*Creates button to send messages*/
	button = gtk_button_new_with_label("Send");
	if(g_signal_connect(button, "clicked", G_CALLBACK(gui_sendMessage), data_tmp)){
		if(data){
			g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), window);
		}
	}
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
	gtk_widget_show(button);
	
	/*function to call to check for incoming messages*/
	g_timeout_add_seconds (PENDING_MESSAGE_INTERVAL, gui_receivePendingMessage, data_tmp);

	/*button for contacts*/
	button = gtk_button_new_with_label("Contacts");
	g_signal_connect(button, "clicked", G_CALLBACK(gui_contactsList), NULL);
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
	gtk_widget_show(button);
	
	/*button for log out*/
	button = gtk_button_new_with_label("Log out");
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gui_logout), NULL);
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
	gtk_widget_show(button);

	/*window for chat */

	// chatwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 //    gtk_window_set_default_size((GtkWindow*) chatwindow, 500, 500);
	// gtk_container_set_border_width(GTK_CONTAINER(chatwindow), 10);
	// darea = gtk_drawing_area_new();
 //    gtk_container_add(GTK_CONTAINER(chatwindow), darea);
 //    cr = gdk_cairo_create (gtk_widget_get_window (chatwindow));
	// data_tmp->data3 = cr;
 //    g_signal_connect(darea,"expose-event",G_CALLBACK(on_expose_event),data_tmp);
 //    //gtk_widget_show(darea);
 //    gtk_widget_show(chatwindow);    
	
	gtk_widget_show(box);
	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_widget_show(window);
}

/*Receives pending messages and displays them*/
gboolean gui_receivePendingMessage(gpointer data){
	#ifdef FULL_CLIENT
	DATA *data_tmp = (DATA*) data;
	Message *temp = NULL;
	RecvUpdate();
	if(Conversations->first)
		temp = Conversations->first->first;
	while(temp){
		if(!temp->sent){
			gui_displayMessage(data_tmp, temp);
			temp->sent = TRUE;
		}
		temp = temp->next;
	}
	#endif
		
	#ifdef TEST_GUI
	g_print("Checking for incoming messages.\n");
	#endif
	return TRUE;
}

/*Prints error message*/
void gui_printError(gchar *text){
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 text);

	/* Destroy the dialog when the user responds to it (e.g. clicks a button) */
	g_signal_connect_swapped (dialog, "response",
                          G_CALLBACK (gtk_widget_destroy),
                          dialog);
	gtk_widget_show(dialog);

}

/*Sends the message*/
void gui_sendMessage(GtkWidget *widget, gpointer data){
	DATA *data_tmp = (DATA*) data;
	GtkEntryBuffer *buffer = (GtkEntryBuffer*) data_tmp->data2;
	gchar *username;
	gchar *text;
	// GtkWidget *darea;

	// darea = gtk_drawing_area_new();
 //  gtk_container_add(GTK_CONTAINER(widget), darea);
	
	if(gtk_entry_get_text_length(GTK_ENTRY(data_tmp->data1)) == 0){
		g_print("Please enter an username.\n");
		gui_printError("Please enter an username.\n");

	}
	else if(gtk_entry_buffer_get_length(buffer) == 0){
		g_print("Please enter a message.\n");
		gui_printError("Please enter a message.\n");

	}
	else{
		username = gtk_entry_get_text(GTK_ENTRY(data_tmp->data1));
		text = gtk_entry_buffer_get_text(buffer);
		#ifdef FULL_CLIENT
		strcpy(RECIPIENT, username);
		strcpy(MESSAGE, text);
		INPUT = 1;
		#endif //FULL_CLIENT
		#ifdef TEST_GUI
		g_print("Username: %s Message: %s\n", username, text);	
		#endif //TEST_GUI
		//gui_showText(widget,data_tmp);

	}
}

/*Displays the sent messages*/
void gui_displayMessage(gpointer data, Message *m){
	GtkWidget *text_view;
	GtkTextBuffer *buffer;
	
	gchar *to = g_strdup ("To: ");
	gchar *nl = g_strdup ("\n");
	gchar *from = g_strdup("From: ");
	DATA *data_tmp = (DATA*) data;
	
	buffer = gtk_text_buffer_new(NULL);
	if(m->sender == true)
		gtk_text_buffer_set_text (buffer, g_strconcat (to,(gchar *)m->to,nl,(gchar *)(m->msg),nl,NULL), -1);
	else
		gtk_text_buffer_set_text (buffer, g_strconcat (from,(gchar *)m->from,nl,(gchar *)(m->msg),nl,NULL), -1);
	
	text_view = gtk_text_view_new_with_buffer (buffer);
	
	//printf ("%d	%d	%d\n",text_view->allocation.width,text_view->allocation.height,text_view->allocation.height+100);
	//gtk_widget_set_size_request (text_view, text_view->allocation.width+100, text_view->allocation.height+100);

	gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
	if(m->sender == true)
		gtk_box_pack_start(GTK_BOX(data_tmp->data3),text_view, FALSE, FALSE, 0);
	else
		gtk_box_pack_start(GTK_BOX(data_tmp->data3),text_view, FALSE, FALSE, 0);
	gtk_widget_show(text_view);
	
}

/*logs out user*/
void gui_logout(){
	#ifdef TEST_GUI
	g_print("Logging out\n");
	g_list_foreach(gtk_window_list_toplevels (), (GFunc)gtk_widget_destroy, NULL);
	gui_loginScreen(user_data);
	#endif
	#ifdef FULL_CLIENT
	LOGGED_IN = 0;
	#endif
}
	
void gui_contactsList(GtkWidget *widget, gchar *friendsname){

	GtkWidget *contacts_window;
	GtkWidget *scrolled_window;
	GtkWidget *button;
	GtkWidget *box;
	GtkWidget *table;
	// char buffer[32];
	int i = 0, k = 0, numberOfFriends = 0;

	friends_tmp = g_malloc(sizeof(*friends_tmp));
	friends_tmp->friends = NULL;
	// friendLabel = g_malloc(sizeof(*friendLabel));
	// friendLabel->friendData = NULL;

	// access to friendslist
	#ifdef FULL_CLIENT
	Friend *temp, *next;
	temp = Friends->first;
	#endif

	contacts_window = gtk_dialog_new ();

	gtk_window_set_default_size((GtkWindow*) contacts_window, 500, 500);

	gtk_window_set_title (GTK_WINDOW (contacts_window), "Contacts");
	gtk_container_set_border_width(GTK_CONTAINER(contacts_window), 10);

	box = gtk_vbox_new(FALSE, 0);

	// /* create scrollbar with table of boxes for friends*/
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(contacts_window)->vbox), scrolled_window, 
			TRUE, TRUE, 0);
    gtk_widget_show (scrolled_window);

    table = gtk_table_new (10, 0, FALSE);

    gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);

    gtk_scrolled_window_add_with_viewport (
                   GTK_SCROLLED_WINDOW (scrolled_window), table);
    gtk_widget_show (table);

    #ifdef FULL_CLIENT
    //delete friend
    if ((g_strcmp0(friendsname, "") != 0) && (numberOfFriends >= 0) && (manage_friend == 2)){
    	popFriend(Friends, friendsname);
    	manage_friend = 0;
    }
    numberOfFriends = Friends->length;
    // populate contacts list with friends
    for(i = 0; i < numberOfFriends; i++){
    	next = temp->next;
		button = gtk_button_new_with_label (temp->uname);
		gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, i, i+1);
		if(g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), contacts_window)){
				friendLabel->friendData = gtk_button_get_label(GTK_BUTTON(button));
				g_signal_connect(button, "clicked", G_CALLBACK(gui_mainScreen), friendLabel->friendData);
		}
		gtk_widget_show (button);
    	temp = next;
	}
	// add friend 
	if((g_strcmp0(friendsname, "") != 0) && (numberOfFriends != MAX_FRIEND) && (manage_friend == 1)){
		temp = CreateFriend(friendsname);
		AppendFriend(Friends, temp);
		button = gtk_button_new_with_label (friendsname);
		gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, i, i+1);
		if(g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), contacts_window)){
				friendLabel->friendData = gtk_button_get_label(GTK_BUTTON(button));
				g_signal_connect(button, "clicked", G_CALLBACK(gui_mainScreen), friendLabel->friendData);
		}
		gtk_widget_show (button);
		manage_friend = 0;
		i += 1;
	}
	#endif
	// populate rest of the boxes with empty
	if(k < MAX_FRIEND){
		for(k = i; k < MAX_FRIEND; k++){
			button = gtk_button_new_with_label ("Empty");
			gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, k, k+1);
			if(g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), contacts_window)){
				friendLabel->friendData = gtk_button_get_label(GTK_BUTTON(button));
				// gtk_widget_destroy(gtk_widget_get_toplevel (widget));
				g_signal_connect(button, "clicked", G_CALLBACK(gui_mainScreen), friendLabel->friendData);
			}
			gtk_widget_show (button);
		}
	}

    /* add or delete friend button */
    button = gtk_button_new_with_label ("Manage friends");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), contacts_window);
    g_signal_connect(button, "clicked", G_CALLBACK(gui_manageFriendsWindow), NULL);
    gtk_box_pack_start(GTK_BOX (GTK_DIALOG (contacts_window)->action_area), button, TRUE, TRUE, 0);
	gtk_widget_show(button);

    /* close button */
    button = gtk_button_new_with_label ("Close");
    g_signal_connect(button, "clicked", G_CALLBACK(gui_mainScreen), NULL);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), contacts_window);
    gtk_widget_set_can_default (button, TRUE);
    gtk_box_pack_start(GTK_BOX (GTK_DIALOG (contacts_window)->action_area), button, TRUE, TRUE, 0);
	gtk_widget_show(button);

	/* show window */
	gtk_widget_show (contacts_window);
}

void gui_manageFriendsWindow(GtkWidget *widget){

	GtkWidget *friendswindow;
	GtkWidget *label;
	GtkWidget *box;
	GtkWidget *button;
	GtkWidget *Friend;
	GtkEntryBuffer *buffer;
	manage_friend = 0;

	/* open window for adding/deleting friends*/
	friendswindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*) friendswindow, 500, 500);
	gtk_window_set_title (GTK_WINDOW (friendswindow), "Manage Friends");
	gtk_container_set_border_width(GTK_CONTAINER(friendswindow), 10);
	box = gtk_vbox_new(FALSE, 0);

	/* label asking user to enter friends name*/
	label = gtk_label_new("Enter a username");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	buffer = gtk_entry_buffer_new(NULL, -1);
	friends_tmp->friends = buffer;
	Friend = gtk_entry_new_with_buffer (buffer);
	g_signal_connect(Friend, "activate", G_CALLBACK(gui_manageFriends), friends_tmp);
	gtk_box_pack_start(GTK_BOX(box),Friend,FALSE,FALSE,0);
	gtk_widget_show(Friend);

	/* button that adds friend */
	button = gtk_button_new_with_label ("Add friend");
	g_signal_connect(button, "clicked", G_CALLBACK(gui_manageFriends), friends_tmp);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), friendswindow);
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
	gtk_widget_show(button);

	/* button that deletes friend */
	button = gtk_button_new_with_label ("Delete friend");
	g_signal_connect(button, "clicked", G_CALLBACK(gui_manageFriends), friends_tmp);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), friendswindow);
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
	gtk_widget_show(button);

	gtk_container_add(GTK_CONTAINER(friendswindow), box);
	gtk_widget_show_all(friendswindow);
}

/* enter username to delete or add friend */
void gui_manageFriends(GtkWidget *widget, gpointer friends){
	friends_tmp = (FRIENDS*) friends;
	GtkEntryBuffer *buffer = (GtkEntryBuffer*) friends_tmp->friends;
	gchar *friendsname = g_malloc(sizeof(friendsname));

	if(g_strcmp0(gtk_button_get_label(GTK_BUTTON(widget)), "Add friend") == 0) manage_friend = 1;
	else if(g_strcmp0(gtk_button_get_label(GTK_BUTTON(widget)), "Delete friend") == 0) manage_friend = 2;

	if(gtk_entry_buffer_get_length(buffer) == 0){
		g_print("Please enter an username.\n");
	}	
	else{
		friendsname = gtk_entry_buffer_get_text(buffer);
		#ifdef TEST_CONTACTS
		g_print("Username: %s\n", friendsname);
		#endif
		gui_contactsList(NULL, friendsname);
	}
}

 gboolean on_expose_event(GtkWidget *widget,  GdkEvent *event, 
    gpointer data)
{      
  do_drawing(data, widget);

  return FALSE;
}

 void do_drawing(gpointer data, GtkWidget *widget)
{
  surface *surface_tmp = data;
  cairo_t* cr = gdk_cairo_create(gtk_widget_get_window(widget));
  cairo_set_source_surface(cr, surface_tmp->image, 10, 10);
  cairo_paint(cr);    
}


void gui_logo (GtkWidget *window, GtkWidget *darea, GtkWidget *box)
{
  surface *surface_tmp = g_malloc(sizeof(*surface_tmp));
  surface_tmp->image = NULL;
  surface_tmp->image = cairo_image_surface_create_from_png("logo.png");


  gtk_box_pack_start(GTK_BOX(box), darea, FALSE, FALSE, 80);

  g_signal_connect(G_OBJECT(darea), "expose-event", 
      G_CALLBACK(on_expose_event), surface_tmp); 
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);


  gtk_widget_show(darea);
  gtk_widget_show(box);
  cairo_surface_destroy(surface_tmp->image);
  g_free(surface_tmp);

}
