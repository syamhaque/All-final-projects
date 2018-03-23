#include <gtk/gtk.h>
#include "GUI.h"

int main(int argc, char *argv[]){
	USER *user_data = g_malloc(sizeof(*user_data));
	
	user_data->username = NULL;
	user_data->password = NULL;
	user_data->username_entry = NULL;
	user_data->password_entry = NULL;
	
	cairo_surface_t *surface;
	cairo_t *cr;	

	/*initialize gtk*/
	gtk_init(&argc, &argv);
	
	/*Shows the login screen and from there calls other functions as needed.*/
	gui_loginScreen(user_data);
	
	gtk_main();
	
	g_free(user_data);
	cairo_destroy(cr);
	user_data = NULL;
	return 0;
}
	
