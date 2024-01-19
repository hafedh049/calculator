#include <gtk/gtk.h>
#include "stack.c"

typedef struct Button
{
	GtkWidget *button;
	char *text;
} Button;

typedef struct Calculator
{
	GtkWidget *window;
	GtkWidget *grid;
	Button buttons[16];
} Calculator;

GtkWidget *box;

void calculate(GtkButton *button, gpointer data)
{

	gchar *text = gtk_button_get_label(button);

	if (!strcmp("=", text))
	{
		// Evaluate the expression using the stack
		gtk_entry_set_placeholder_text(GTK_ENTRY(box), res);
	}
	else if (!strcmp("C", text))
	{
		gtk_entry_set_placeholder_text(GTK_ENTRY(box), "");
	}
	else
	{
		gtk_entry_set_placeholder_text(GTK_ENTRY(box), text);
	}
}

char *intToString(int num)
{
	int maxDigits = snprintf(NULL, 0, "%d", num);

	char *str = (char *)malloc(maxDigits + 1);

	sprintf(str, "%d", num);

	return str;
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

	for (int i = 0; i <= 9; i++)
		widget.buttons[i].button = gtk_button_new_with_label(intToString(i));

	widget.buttons[10].button = gtk_button_new_with_label("+");
	widget.buttons[11].button = gtk_button_new_with_label("-");
	widget.buttons[12].button = gtk_button_new_with_label("x");
	widget.buttons[13].button = gtk_button_new_with_label("/");
	widget.buttons[14].button = gtk_button_new_with_label("C");
	widget.buttons[15].button = gtk_button_new_with_label("=");

	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[14].button, 0, 1, 3, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[13].button, 3, 1, 1, 1);

	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[7].button, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[8].button, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[9].button, 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[12].button, 3, 2, 1, 1);

	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[4].button, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[5].button, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[6].button, 2, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[11].button, 3, 3, 1, 1);

	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[1].button, 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[2].button, 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[3].button, 2, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[10].button, 3, 4, 1, 1);

	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[0].button, 0, 5, 3, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.buttons[15].button, 3, 5, 1, 1);

	for (int i = 0; i <= 15; i++)
		g_signal_connect(widget.buttons[i].button, "clicked", G_CALLBACK(calculate), NULL);

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