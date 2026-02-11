nemo_floating_bar_cleanup_actions (NemoFloatingBar *self)
{
	GtkWidget *widget;
	GList *children, *l;
	gpointer data;

	children = gtk_container_get_children (GTK_CONTAINER (self));
	l = children;

	while (l != NULL) {
		widget = l->data;
		data = g_object_get_data (G_OBJECT (widget), "action-id");
		l = l->next;

		if (data != NULL) {

			gtk_widget_destroy (widget);
		}
	}

	g_list_free (children);

	self->priv->is_interactive = FALSE;
}
