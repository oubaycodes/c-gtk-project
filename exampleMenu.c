#include "gtk/gtk.h"

void handleValue(GtkWidget *widget, gpointer data)
{
    GtkEntryBuffer *valueBuffer = gtk_entry_get_buffer(GTK_ENTRY(widget));
    int bufferLength = gtk_entry_buffer_get_length(valueBuffer);
    char *entryText = gtk_entry_buffer_get_text(valueBuffer);
    printf("%s\n", entryText);

    gtk_entry_buffer_delete_text(valueBuffer, 0, bufferLength);
}
void activate(GtkApplication *app, gpointer app_data)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *entry;
    GtkWidget *label;

    // styling
    int xBoxMargins = 40;
    int yBoxMargins = 30;
    int entryGridGap = 10;
    // window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Enter Your name");
    // gtk_window_set_default_size(GTK_WINDOW(window), 500, 150);
    gtk_window_set_resizable(GTK_WINDOW(window), false);

    // gtk box
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_widget_set_margin_top(box, yBoxMargins);
    gtk_widget_set_margin_bottom(box, yBoxMargins);
    gtk_widget_set_margin_start(box, xBoxMargins);
    gtk_widget_set_margin_end(box, xBoxMargins);

    // label
    label = gtk_label_new("Enter your name:");
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_box_append(GTK_BOX(box), label);

    // grid
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), entryGridGap);
    gtk_box_append(GTK_BOX(box), grid);

    // entry
    entry = gtk_entry_new();
    GtkEntryBuffer *buffer = gtk_entry_buffer_new("", 0);
    entry = gtk_entry_new_with_buffer(buffer);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);
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
