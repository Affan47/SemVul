ay_chat_get_tab_label(GtkNotebook *notebook, GtkWidget *child)
{
	GtkWidget *tab_label;
	GList *children;

	tab_label = gtk_notebook_get_tab_label(notebook, child);
	children = gtk_container_get_children(GTK_CONTAINER(tab_label));

	while(children) {
		if (GTK_IS_LABEL(children->data))
			return children->data;

		children = g_list_next(children);
	}

	return NULL;
}
