handle_nonlocal_move (NautilusCanvasContainer *container,
		      GdkDragAction action,
		      int x, int y,
		      const char *target_uri,
		      gboolean icon_hit)
{
	GList *source_uris, *p;
	GArray *source_item_locations;
	gboolean free_target_uri, is_rtl;
	int index, item_x;
	GtkAllocation allocation;

	if (container->details->dnd_info->drag_info.selection_list == NULL) {
		return;
	}

	source_uris = NULL;
	for (p = container->details->dnd_info->drag_info.selection_list; p != NULL; p = p->next) {

		source_uris = g_list_prepend (source_uris, ((NautilusDragSelectionItem *)p->data)->uri);
	}
	source_uris = g_list_reverse (source_uris);

	is_rtl = nautilus_canvas_container_is_layout_rtl (container);

	source_item_locations = g_array_new (FALSE, TRUE, sizeof (GdkPoint));
	if (!icon_hit) {


		source_item_locations = g_array_set_size (source_item_locations,
			g_list_length (container->details->dnd_info->drag_info.selection_list));

		for (index = 0, p = container->details->dnd_info->drag_info.selection_list;
			p != NULL; index++, p = p->next) {
		    	item_x = ((NautilusDragSelectionItem *)p->data)->icon_x;
			if (is_rtl)
				item_x = -item_x - ((NautilusDragSelectionItem *)p->data)->icon_width;
		     	g_array_index (source_item_locations, GdkPoint, index).x = item_x;
		     	g_array_index (source_item_locations, GdkPoint, index).y =
				((NautilusDragSelectionItem *)p->data)->icon_y;
		}
	}

	free_target_uri = FALSE;

	if (eel_uri_is_desktop (target_uri)) {
		target_uri = nautilus_get_desktop_directory_uri ();
		free_target_uri = TRUE;
	}

	if (is_rtl) {
		gtk_widget_get_allocation (GTK_WIDGET (container), &allocation);
		x = CANVAS_WIDTH (container, allocation) - x;
	}


	g_signal_emit_by_name (container, "move-copy-items",
			       source_uris,
			       source_item_locations,
			       target_uri,
			       action,
			       x, y);

	if (free_target_uri) {
		g_free ((char *)target_uri);
	}

	g_list_free (source_uris);
	g_array_free (source_item_locations, TRUE);
}
