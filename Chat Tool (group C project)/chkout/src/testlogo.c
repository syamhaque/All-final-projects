#include <cairo.h>
#include <gtk/gtk.h>

// compile with this in the command line:
// gcc -ansi -Wall -std=c99 `pkg-config --libs --cflags cairo` `pkg-config --libs --cflags gtk+-2.0` testlogo.c -o testlogo

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
}


int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;
  GtkWidget *box;
  

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

  gtk_widget_show_all(window);

  gtk_main();

  cairo_surface_destroy(surface_tmp->image);
  g_free(surface_tmp);
  return 0;
}