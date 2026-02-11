nautilus_canvas_item_set_image (NautilusCanvasItem *item,
				GdkPixbuf *image)
{
	NautilusCanvasItemDetails *details;

	g_return_if_fail (NAUTILUS_IS_CANVAS_ITEM (item));
	g_return_if_fail (image == NULL || pixbuf_is_acceptable (image));

	details = item->details;
	if (details->pixbuf == image) {
		return;
	}

	if (image != NULL) {
		g_object_ref (image);
	}
	if (details->pixbuf != NULL) {
		g_object_unref (details->pixbuf);
	}
	if (details->rendered_surface != NULL) {
		cairo_surface_destroy (details->rendered_surface);
		details->rendered_surface = NULL;
	}

	details->pixbuf = image;

	nautilus_canvas_item_invalidate_bounds_cache (item);
	eel_canvas_item_request_update (EEL_CANVAS_ITEM (item));
}
