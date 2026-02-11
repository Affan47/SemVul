reload_icon_positions (NautilusCanvasContainer *container)
{
	GList *p, *no_position_icons;
	NautilusCanvasIcon *icon;
	gboolean have_stored_position;
	NautilusCanvasPosition position;
	EelDRect bounds;
	double bottom;
	EelCanvasItem *item;

	g_assert (!container->details->auto_layout);

	resort (container);

	no_position_icons = NULL;


	bottom = 0;
	for (p = container->details->icons; p != NULL; p = p->next) {
		icon = p->data;

		have_stored_position = FALSE;
		g_signal_emit (container,
			       signals[GET_STORED_ICON_POSITION], 0,
			       icon->data,
			       &position,
			       &have_stored_position);
		if (have_stored_position) {
			icon_set_position (icon, position.x, position.y);
			item = EEL_CANVAS_ITEM (icon->item);
			nautilus_canvas_item_get_bounds_for_layout (icon->item,
									   &bounds.x0,
									   &bounds.y0,
									   &bounds.x1,
									   &bounds.y1);
			eel_canvas_item_i2w (item->parent,
					     &bounds.x0,
					     &bounds.y0);
			eel_canvas_item_i2w (item->parent,
					     &bounds.x1,
					     &bounds.y1);
			if (bounds.y1 > bottom) {
				bottom = bounds.y1;
			}
		} else {
			no_position_icons = g_list_prepend (no_position_icons, icon);
		}
	}
	no_position_icons = g_list_reverse (no_position_icons);


	lay_down_icons (container, no_position_icons, bottom + ICON_PAD_BOTTOM);
	g_list_free (no_position_icons);
}
