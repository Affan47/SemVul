child_size_request_handler (GtkWidget         *widget,
			    GtkRequisition    *req,
			    GladeDesignLayout *layout)
{
	GladeDesignLayoutPrivate *priv;
	GtkAllocation allocation;
	GtkRequisition requisition;
	gint new_width, new_height;
	gint old_width, old_height;

	priv = GLADE_DESIGN_LAYOUT_GET_PRIVATE (layout);

	priv->current_size_request->width = req->width;
	priv->current_size_request->height = req->height;

	gtk_widget_get_allocation (widget, &allocation);
	new_width = allocation.width;
	new_height = allocation.height;

	if (req->width > new_width)
		new_width = req->width;

	if (req->height > new_height)
		new_height = req->height;

	if ((new_width != allocation.width) ||
	    (new_height != allocation.height))
	{
		gtk_widget_size_request (widget, &requisition);
		old_width = requisition.width;
		old_height = requisition.height;

		gtk_widget_set_size_request (widget,
					     (old_width > new_width) ? old_width : new_width,
					     (old_height > new_height) ? old_height : new_height);
	}

	gtk_widget_queue_draw (GTK_WIDGET (layout));

}
