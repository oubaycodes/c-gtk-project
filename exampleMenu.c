#include "gtk/gtk.h"

static int returnValue[2];
static int currentValueIndex = 0;
void handleValue(GtkWidget *widget, GtkWidget *data)
{
    GtkEntryBuffer *valueBuffer = gtk_entry_get_buffer(GTK_ENTRY(widget));
    int bufferLength = gtk_entry_buffer_get_length(valueBuffer);
    char *entryTextPointer = (char *)gtk_entry_buffer_get_text(valueBuffer);
    char entryText[100];
    strncpy(entryText, entryTextPointer, 100);
    if (entryText[0] == '\0')
        return;

    gtk_entry_buffer_delete_text(valueBuffer, 0, bufferLength);
    gtk_widget_set_sensitive(widget, FALSE);
    gtk_widget_set_sensitive(data, FALSE);

    returnValue[currentValueIndex] = atoi(entryText);
    currentValueIndex++;
    if (currentValueIndex == 2)
    {
        //
    }
}
void firstDegreeLogic(GtkWidget *widget, gpointer data)
{
    int a = returnValue[0];
    int b = returnValue[1];
    printf("%i\n%i\n", a, b);
}
int firstDegreeWidgets(GtkWidget *widget, gpointer data)
{
    g_signal_handlers_disconnect_by_data(widget, data);
    gtk_widget_set_sensitive(widget, FALSE);
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *box = data;
    int a, b, c;
    // spacing
    int buttonGridGap = 20;
    int entryGridGap = 10;
    //////////////////////////////////a///////////////////////////////
    // label
    label = gtk_label_new("enter a value for a:");
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_box_append(GTK_BOX(box), label);
    // grid
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), entryGridGap);
    gtk_box_append(GTK_BOX(box), grid);
    // entry
    GtkEntryBuffer *buffer = gtk_entry_buffer_new("", 0);
    entry = gtk_entry_new_with_buffer(buffer);
    gtk_entry_set_max_length(GTK_ENTRY(entry), 60);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 1, 1);
    // button
    button = gtk_button_new_with_label("Enter");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(handleValue), entry);

    gtk_grid_attach_next_to(GTK_GRID(grid), button, entry, GTK_POS_RIGHT, 1, 2);
    //////////////////////////////////b//////////////////////////////
    // label
    label = gtk_label_new("enter a value for b:");
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_box_append(GTK_BOX(box), label);
    // grid
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), entryGridGap);
    gtk_box_append(GTK_BOX(box), grid);
    // entry
    buffer = gtk_entry_buffer_new("", 0);
    entry = gtk_entry_new_with_buffer(buffer);
    gtk_entry_set_max_length(GTK_ENTRY(entry), 60);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 1, 1);
    // button
    button = gtk_button_new_with_label("Enter");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(handleValue), entry);
    gtk_grid_attach_next_to(GTK_GRID(grid), button, entry, GTK_POS_RIGHT, 1, 2);
    /////////////////////////////////////////////////////////////////
    // label
    // label = gtk_label_new("enter a value for c:");
    // gtk_label_set_xalign(GTK_LABEL(label), 0);
    // gtk_box_append(GTK_BOX(box), label);
    // // grid
    // grid = gtk_grid_new();
    // gtk_grid_set_column_spacing(GTK_GRID(grid), entryGridGap);
    // gtk_box_append(GTK_BOX(box), grid);
    // // entry
    // buffer = gtk_entry_buffer_new("", 0);
    // entry = gtk_entry_new_with_buffer(buffer);
    // gtk_entry_set_max_length(GTK_ENTRY(entry), 60);
    // gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 1, 1);
    // // button
    // button = gtk_button_new_with_label("Enter");
    // g_signal_connect_swapped(button, "clicked", G_CALLBACK(handleValue), entry);
    // gtk_grid_attach_next_to(GTK_GRID(grid), button, entry, GTK_POS_RIGHT, 1, 2);
    // ///////////////////enter button//////////////////
    button = gtk_button_new_with_label("Enter");
    g_signal_connect(button, "clicked", G_CALLBACK(firstDegreeLogic), NULL);
    gtk_widget_set_sensitive(button, FALSE);
    gtk_box_append(GTK_BOX(box), button);

    // if (a != 0)
    // {
    //     double x = (double)b / a;
    // }
    // else if (b = 0)
    // {
    //     // printf("X = R");
    // }
    // else
    // {

    //     // printf("X n'pas d'solution\n");
    // }
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

    int typeButtonGridGap = 25;
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
    label = gtk_label_new("enter equation type:");
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_box_append(GTK_BOX(box), label);

    // button grid
    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), true);
    gtk_grid_set_column_spacing(GTK_GRID(grid), typeButtonGridGap);
    gtk_box_append(GTK_BOX(box), grid);

    button = gtk_button_new_with_label("ax+b=0");
    g_signal_connect(button, "clicked", G_CALLBACK(firstDegreeWidgets), box);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);
    button = gtk_button_new_with_label("ax^2+bx+c=0");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    // display
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
