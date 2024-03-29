#include <gtk/gtk.h>

#include "utils.c"

typedef struct Calculator
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *buttons[14];
} Calculator;

GtkWidget *box;

char *input = "";

void calculate(GtkButton *button, gpointer data)
{
	const gchar *text = gtk_button_get_label(button);

	if (!strcmp("=", text))
	{
		char *res = compute(gtk_entry_get_placeholder_text(GTK_ENTRY(box)));
		gtk_entry_set_placeholder_text(GTK_ENTRY(box), res);
	}
	else if (!strcmp("C", text))
	{
		input = "";
		gtk_entry_set_placeholder_text(GTK_ENTRY(box), input);
	}
	else
	{
		input = concatenate(input, text);
		gtk_entry_set_placeholder_text(GTK_ENTRY(box), input);
	}
}

void activate(GtkApplication *app, gpointer user_data)
{
	Calculator widget;

	widget.window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(widget.window), "Calculator");
	gtk_window_set_default_size(GTK_WINDOW(widget.window), 200, 200);

	widget.grid = gtk_grid_new();
	gtk_window_set_child(GTK_WINDOW(widget.window), widget.grid);

	box = gtk_entry_new();
	gtk_editable_set_editable(GTK_EDITABLE(box), FALSE);

	gtk_grid_attach(GTK_GRID(widget.grid), box, 0, 0, 4, 1);

	for (int index = 0; index < 14; index++)
	{
		widget.buttons[index] = gtk_button_new_with_label(labels[index]);
		g_signal_connect(widget.buttons[index], "clicked", G_CALLBACK(calculate), NULL);
		gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[index], positions[index][0], positions[index][1], positions[index][2], positions[index][3]);
	}

	gtk_window_present(GTK_WINDOW(widget.window));
}

int main(int argc, char **argv)
{
	GtkApplication *app;

	gtk_init();

	int status;

	app = gtk_application_new("org.gtk.calculator", G_APPLICATION_DEFAULT_FLAGS);

	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv);

	g_object_unref(app);

	return status;
}