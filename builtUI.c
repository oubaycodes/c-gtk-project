#include "gtk/gtk.h"
#include "glib/gstdio.h"

static void activate(GtkApplication *app, gpointer app_data)
{
    // style variables
    int xBoxMargins = 40;
    int yBoxMargins = 30;
    // building
    GtkBuilder *builder;
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "./builder.ui", NULL);

    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW(window), app);
    // gtk_window_set_resizable(GTK_WINDOW(window), false);

    GObject *box = gtk_builder_get_object(builder, "box");

    gtk_widget_set_margin_top(GTK_WIDGET(box), yBoxMargins);
    gtk_widget_set_margin_bottom(GTK_WIDGET(box), yBoxMargins);
    gtk_widget_set_margin_start(GTK_WIDGET(box), xBoxMargins);
    gtk_widget_set_margin_end(GTK_WIDGET(box), xBoxMargins);

    g_object_unref(builder);
}
int main(int argc, char *argv[])
{
    GtkApplication *app;
    app = gtk_application_new("org.oub.builtApp", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}