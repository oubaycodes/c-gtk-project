#include "gtk/gtk.h"

static int returnValue[2];
static int currentValueIndex = 0;
static int passedVarIndex = 0;
// global
void handleValue(GtkWidget *widget, GtkWidget *data)
{
    GtkEntryBuffer *valueBuffer = gtk_entry_get_buffer(GTK_ENTRY(widget));
    int bufferLength = gtk_entry_buffer_get_length(valueBuffer);
    char *entryTextPointer = (char *)gtk_entry_buffer_get_text(valueBuffer);
    char entryText[100];
    strncpy(entryText, entryTextPointer, 100);
    if (entryText[0] == '\0')
        return;

    // gtk_entry_buffer_delete_text(valueBuffer, 0, bufferLength);
    gtk_widget_set_sensitive(widget, FALSE);
    gtk_widget_set_sensitive(data, FALSE);

    returnValue[currentValueIndex] = atoi(entryText);
    currentValueIndex++;
}
void firstDegreeLogic(GtkWidget *widget, gpointer data)
{
    GtkWidget *label;
    if (currentValueIndex != 2)
        return;
    double a = returnValue[0];
    double b = returnValue[1];
    double x;
    printf("%f\n%f\n", a, b);
    // ax+b=0
    if (a == 0 && b == 0)
    {
    }
    else
    {
        x = -b / a;
    }
    char labelBuffer[60];
    g_snprintf(labelBuffer, sizeof(labelBuffer), "The solution to %.1fx+%.1f is x = %.2f", a, b, x);
    label = gtk_label_new(labelBuffer);
    gtk_label_set_xalign(GTK_LABEL(label), 0);
    gtk_box_append(GTK_BOX(data), label);
}
void createVarInput(GtkWidget *widget, gpointer data, int var)
{
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *box = data;

    // spacing
    int buttonGridGap = 20;
    int entryGridGap = 10;

    // label
    char varName;

    switch (passedVarIndex)
    {
    case 0:
        varName = 'a';
        passedVarIndex++;
        break;
    case 1:
        varName = 'b';
        passedVarIndex++;
        break;
    case 2:
        varName = 'c';
        passedVarIndex++;
        break;
    default:
        break;
    }
    char labelBuffer[30];
    g_snprintf(labelBuffer, sizeof(labelBuffer), "Enter an integer %c:", varName);

    label = gtk_label_new(labelBuffer);
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
}
int firstDegreeWidgets(GtkWidget *widget, gpointer data)
{
    GtkWidget *box = data;
    GtkWidget *button;

    g_signal_handlers_disconnect_by_data(widget, data);
    gtk_widget_set_sensitive(widget, FALSE);

    int a, b, x;
    createVarInput(widget, data, a);
    createVarInput(widget, data, b);

    // ///////////////////enter button//////////////////
    button = gtk_button_new_with_label("Enter");
    g_signal_connect(button, "clicked", G_CALLBACK(firstDegreeLogic), box);

    gtk_box_append(GTK_BOX(box), button);
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
