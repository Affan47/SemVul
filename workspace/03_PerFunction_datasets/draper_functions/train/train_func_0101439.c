gtk_placer_size_allocate (GtkWidget     *widget,
			 GtkAllocation *allocation)
{
  GtkPlacer *placer;
  GtkPlacerChild *child;
  GtkAllocation child_allocation;
  GtkRequisition child_requisition;
  GList *children;
  guint16 border_width;
  gdouble rel_width_scale, rel_height_scale;

  placer = GTK_PLACER (widget);

  widget->allocation = *allocation;

  if (!GTK_WIDGET_NO_WINDOW (widget))
    {
      if (GTK_WIDGET_REALIZED (widget))
	gdk_window_move_resize (widget->window,
				allocation->x,
				allocation->y,
				allocation->width,
				allocation->height);
    }

  border_width = GTK_CONTAINER (placer)->border_width;
  rel_width_scale = (allocation->width - 2 * border_width) / 32767.0;
  rel_height_scale = (allocation->height - 2 * border_width) / 32767.0;

  children = placer->children;
  while (children)
    {
      child = children->data;
      children = children->next;

      if (GTK_WIDGET_VISIBLE (child->widget))
	{
	  gtk_widget_get_child_requisition (child->widget, &child_requisition);
	  child_allocation.x = child->x + border_width
			       + child->rel_x * rel_width_scale;
	  child_allocation.y = child->y + border_width
			       + child->rel_y * rel_height_scale;

	  if (GTK_WIDGET_NO_WINDOW (widget))
	    {
	      child_allocation.x += allocation->x;
	      child_allocation.y += allocation->y;
	    }

	  if (!child->rel_width)
	    child_allocation.width = child_requisition.width;
	  else
	    child_allocation.width = child->rel_width * rel_width_scale;

	  if (!child->rel_height)
	    child_allocation.height = child_requisition.height;
	  else
	    child_allocation.height = child->rel_height * rel_height_scale;

	  child_allocation.width += child->width;
	  child_allocation.height += child->height;

	  child_allocation.width = MAX (child_allocation.width, 0);
	  child_allocation.height = MAX (child_allocation.height, 0);
	  gtk_widget_size_allocate (child->widget, &child_allocation);
	}
    }
}
