on_preview_image_scrolled (GtkWidget *widget,
			   GdkEventScroll *event,
			   gpointer user_data)
{
	PhotosPrintSetupPrivate *priv = PHOTOS_PRINT_SETUP (user_data)->priv;
	PhotosPrintPreview *preview = PHOTOS_PRINT_PREVIEW (widget);
	gfloat scale;

	scale = photos_print_preview_get_scale (preview);

	if (!photos_print_preview_point_in_image_area (preview,
						    event->x, event->y))
	{
		return FALSE;
	}

	switch (event->direction) {
	case GDK_SCROLL_UP:

		scale *= 1.1;
		break;
	case GDK_SCROLL_DOWN:

		scale *= 0.9;
		break;
	default:
		return FALSE;
		break;
	}

	gtk_range_set_value (GTK_RANGE (priv->scaling), 100*scale);

	return TRUE;
}
