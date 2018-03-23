#include <cairo.h>
#include <gtk/gtk.h>

void gui_mainScreen(void);
void gui_sendMessage(GtkWidget *widget, gpointer data);
void gui_displayMessage(GtkWidget *box, gchar *user, gchar *text);
typedef struct SURFACE{
  cairo_surface_t *image;  
} surface;


void do_drawing(gpointer data, GtkWidget *widget);

static gboolean on_expose_event(GtkWidget *widget,  GdkEvent *event, 
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
  cairo_show_text(cr,"why does this not work"); 
}
typedef struct Data{
	gpointer *data1;
	gpointer *data2;
	gpointer *data3;
}DATA;


void gui_mainScreen(void){
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
	g_signal_connect(window, "delete_event", G_CALLBACK(gtk_main_quit), NULL);
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
	
	/*Creates text entry for the username to send the message to*/
	label = gtk_label_new("Username");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	name_entry = gtk_entry_new();
	data_tmp->data1 = name_entry;
	g_signal_connect(name_entry, "activate", G_CALLBACK(gui_sendMessage), data_tmp);
	gtk_box_pack_start(GTK_BOX(box),name_entry,FALSE,FALSE,0);
	gtk_widget_show(name_entry);
	
	/*Creates text entry for writing messages*/	
	label = gtk_label_new("Message");
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	gtk_widget_show(label);
	buffer = gtk_entry_buffer_new(NULL, -1);
	data_tmp->data2 = buffer;
	entry = gtk_entry_new_with_buffer (buffer);
	g_signal_connect(entry, "activate", G_CALLBACK(gui_sendMessage), data_tmp);
	gtk_box_pack_start(GTK_BOX(box),entry,FALSE,FALSE,0);
	gtk_widget_show(entry);
	
	/*Creates button to send messages*/
	button = gtk_button_new_with_label("Send");
	g_signal_connect(button, "clicked", G_CALLBACK(gui_sendMessage), data_tmp);
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
	}
	else if(gtk_entry_buffer_get_length(buffer) == 0){
		g_print("Please enter a message.\n");
	}
	else{
		username = gtk_entry_get_text(GTK_ENTRY(data_tmp->data1));
		text = gtk_entry_buffer_get_text(buffer);
		gui_displayMessage(GTK_WIDGET(data_tmp->data3),username, text);

		g_print("Username: %s Message: %s\n", username, text);

	}
}

/*Displays the sent messages*/
void gui_displayMessage(GtkWidget *box, gchar *user, gchar *text){
	GtkWidget *text_view;
	GtkTextBuffer *buffer;
	
	gchar *to = g_strdup ("To: ");
	gchar *nl = g_strdup ("\n");
	
	buffer = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text (buffer, g_strconcat (to,user,nl,text,nl,NULL), -1);
	text_view = gtk_text_view_new_with_buffer (buffer);
	
	//printf ("%d	%d	%d\n",text_view->allocation.width,text_view->allocation.height,text_view->allocation.height+100);
	//gtk_widget_set_size_request (text_view, text_view->allocation.width+100, text_view->allocation.height+100);

	gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
	gtk_box_pack_start(GTK_BOX(box),text_view, FALSE, FALSE, 0);
	gtk_widget_show(text_view);
	
}


int main(int argc, char *argv[])
{
  GtkWidget *window;

  GtkWidget *darea;

  

  surface *surface_tmp = g_malloc(sizeof(*surface_tmp));
  surface_tmp->image = NULL;
  surface_tmp->image = cairo_image_surface_create_from_png("logo.png");

  gtk_init(&argc, &argv);

 

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);

  g_signal_connect(G_OBJECT(darea), "expose-event", 
      G_CALLBACK(on_expose_event), surface_tmp); 
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000); 
  gtk_window_set_title(GTK_WINDOW(window), "Image");

  gtk_container_add(GTK_CONTAINER(window), darea);

  gtk_widget_show_all(window);
gui_mainScreen();
  gtk_main();

  cairo_surface_destroy(surface_tmp->image);
  g_free(surface_tmp);
  return 0;
}
