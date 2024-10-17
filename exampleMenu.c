#include "gtk/gtk.h"

void handleValue(GtkWidget *widget, gpointer data)
{
    printf("hiii\n");
}
void activate(GtkApplication *app, gpointer app_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *entry;
    GtkWidget *label;
    // window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Enter Your name");
    gtk_window_set_resizable(GTK_WINDOW(window), false);
    // gtk box
    // label
    label = gtk_label_new("Enter your name");

    gtk_window_set_child(GTK_WINDOW(window), label);
    // grid
    grid = gtk_grid_new();
    // gtk_window_set_child(GTK_WINDOW(window), grid);
    // entry
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 10, 1);
    // button
    button = gtk_button_new_with_label("Enter");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(handleValue), entry);
    gtk_grid_attach_next_to(GTK_GRID(grid), button, entry, GTK_POS_RIGHT, 1, 2);
    gtk_window_present(GTK_WINDOW(window));
}
int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;
    app = gtk_application_new("org.oub.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
