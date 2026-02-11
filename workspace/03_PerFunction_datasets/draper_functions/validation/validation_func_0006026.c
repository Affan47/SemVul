gtk_form_size_allocate(GtkWidget *widget, GtkAllocation *allocation)
{
    GList *tmp_list;
    GtkForm *form;
    gboolean need_reposition;

    g_return_if_fail(GTK_IS_FORM(widget));

    if (widget->allocation.x == allocation->x
	    && widget->allocation.y == allocation->y
	    && widget->allocation.width == allocation->width
	    && widget->allocation.height == allocation->height)
	return;

    need_reposition = widget->allocation.width != allocation->width
		   || widget->allocation.height != allocation->height;
    form = GTK_FORM(widget);

    if (need_reposition)
    {
	tmp_list = form->children;

	while (tmp_list)
	{
	    GtkFormChild *child = tmp_list->data;
	    gtk_form_position_child(form, child, TRUE);

	    tmp_list = tmp_list->next;
	}
    }

    if (GTK_WIDGET_REALIZED(widget))
    {
	gdk_window_move_resize(widget->window,
			       allocation->x, allocation->y,
			       allocation->width, allocation->height);
	gdk_window_move_resize(GTK_FORM(widget)->bin_window,
			       0, 0,
			       allocation->width, allocation->height);
    }
    widget->allocation = *allocation;
    if (need_reposition)
	gtk_form_send_configure(form);
}
