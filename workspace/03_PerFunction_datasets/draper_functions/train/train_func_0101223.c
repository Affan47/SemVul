gth_image_selector_button_press (GthImageViewerTool *base,
				 GdkEventButton     *event)
{
	GthImageSelector *self = GTH_IMAGE_SELECTOR (base);
	gboolean          retval = FALSE;
	int               x, y;

	if (event->button != 1)
		return FALSE;

	if (! point_in_rectangle (event->x, event->y, self->priv->viewer->image_area))
		return FALSE;

	x = event->x + self->priv->viewer->x_offset;
	y = event->y + self->priv->viewer->y_offset;

	if (self->priv->current_area == NULL) {
		cairo_rectangle_int_t new_selection;

		new_selection.x = selector_to_real (self, x - self->priv->viewer->image_area.x);
		new_selection.y = selector_to_real (self, y - self->priv->viewer->image_area.y);
		new_selection.width = selector_to_real (self, 1);
		new_selection.height = selector_to_real (self, 1);

		if (self->priv->type == GTH_SELECTOR_TYPE_REGION) {
			check_and_set_new_selection (self, new_selection);
			set_active_area (self, get_event_area_from_id (self, C_BOTTOM_RIGHT_AREA));
		}
		else if (self->priv->type == GTH_SELECTOR_TYPE_POINT) {
			g_signal_emit (G_OBJECT (self),
				       signals[SELECTED],
				       0,
				       new_selection.x,
				       new_selection.y);
			return TRUE;
		}
	}

	if (self->priv->current_area != NULL) {
		self->priv->viewer->pressed = TRUE;
		self->priv->viewer->dragging = TRUE;
		self->priv->drag_start_selection_area = self->priv->selection_area;
		gtk_widget_queue_draw (GTK_WIDGET (self->priv->viewer));
		retval = TRUE;
	}

	return retval;
}
