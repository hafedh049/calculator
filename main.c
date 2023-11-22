
#include <gtk/gtk.h>

#include <stdlib.h>
#include <string.h>

#include "linked_list.c"

typedef struct Calculator
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button[16];
} Calculator;

GtkWidget *box;

LinkedList *holder;

char* intToString(int num) {
    int maxDigits = snprintf(NULL, 0, "%d", num);

    char* str = (char*)malloc(maxDigits + 1);

    sprintf(str, "%d", num);

    return str;
}

static void calculate(GtkButton *button, gpointer data)
{

	gchar *text = gtk_button_get_label(button);

	if (!strcmp("+", text) || !strcmp("-", text) || !strcmp("/", text) || !strcmp("x", text))
	{
		if (strcmp("+", text) == 0)
			appendLinkedList(holder,"+");
		else if (strcmp("-", text) == 0)
			appendLinkedList(holder,"-");
		else if (strcmp("/", text) == 0)
			appendLinkedList(holder,"/");
		else if (strcmp("x", text) == 0)
			appendLinkedList(holder,"*");

		gtk_entry_set_placeholder_text(GTK_ENTRY(box), toString(holder));
	}
	else if(!strcmp("=", text))
	{
		char *res = calculateResult(holder);
		gtk_entry_set_placeholder_text(GTK_ENTRY(box), res);
		clearLinkedList(holder);
	}
	else if(!strcmp("C", text))
	{
		gtk_entry_set_placeholder_text(GTK_ENTRY(box), "");
		clearLinkedList(holder);
	}
	else{
		if(getLastLinkedList(*holder) && isNumber(getLastLinkedList(*holder)->data))
			strcat(getLastLinkedList(*holder)->data,text);
		else
			appendLinkedList(holder,text);

		gtk_entry_set_placeholder_text(GTK_ENTRY(box), "");
		gtk_entry_set_placeholder_text(GTK_ENTRY(box), toString(holder));
	}
}

static void activate(GtkApplication *app, gpointer user_data)
{
	Calculator widget;

	widget.window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(widget.window), "Calculator");
	gtk_window_set_default_size(GTK_WINDOW(widget.window), 200, 200);

	widget.grid = gtk_grid_new();
	gtk_window_set_child(GTK_WINDOW(widget.window), widget.grid);

	box = gtk_entry_new();
	gtk_editable_set_editable(GTK_EDITABLE(box), FALSE);

	for(int i = 0; i <= 9 ;i++)
		widget.button[i] = gtk_button_new_with_label(intToString(i));

	widget.button[10] = gtk_button_new_with_label("+");
	widget.button[11] = gtk_button_new_with_label("-");
	widget.button[12] = gtk_button_new_with_label("x");
	widget.button[13] = gtk_button_new_with_label("/");
	widget.button[14] = gtk_button_new_with_label("C");
	widget.button[15] = gtk_button_new_with_label("=");

	gtk_grid_attach(GTK_GRID(widget.grid), box, 0, 0, 4, 1);

	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[14], 0, 1, 3, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[13], 3, 1, 1, 1);

	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[7], 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[8], 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[9], 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[12], 3, 2, 1, 1);

	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[4], 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[5], 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[6], 2, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[11], 3, 3, 1, 1);

	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[1], 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[2], 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[3], 2, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[10], 3, 4, 1, 1);

	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[0], 0, 5, 3, 1);
	gtk_grid_attach(GTK_GRID(widget.grid), widget.button[15], 3, 5, 1, 1);

	
	for(int i = 0; i <= 15 ;i++)
		g_signal_connect(widget.button[i], "clicked", G_CALLBACK(calculate), NULL);

	gtk_window_present(GTK_WINDOW(widget.window));
}

int main(int argc, char **argv)
{
	holder = createLinkedList();

	GtkApplication *app;

	gtk_init();

	int status;
	app = gtk_application_new("org.gtk.calculator", G_APPLICATION_DEFAULT_FLAGS);

	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}