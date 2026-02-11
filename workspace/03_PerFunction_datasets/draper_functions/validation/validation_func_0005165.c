nautilus_canvas_container_accessible_select_all_selection (AtkSelection *accessible)
{
	NautilusCanvasContainer *container;
	GtkWidget *widget;

	widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (accessible));
	if (!widget) {
		return FALSE;
	}

        container = NAUTILUS_CANVAS_CONTAINER (widget);

	nautilus_canvas_container_select_all (container);

	return TRUE;
}
