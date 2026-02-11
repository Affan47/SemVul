nautilus_canvas_container_init (NautilusCanvasContainer *container)
{
	NautilusCanvasContainerDetails *details;
	static gboolean setup_prefs = FALSE;

	details = g_new0 (NautilusCanvasContainerDetails, 1);

	details->icon_set = g_hash_table_new (g_direct_hash, g_direct_equal);
	details->layout_timestamp = UNDEFINED_TIME;
	details->zoom_level = NAUTILUS_ZOOM_LEVEL_STANDARD;

	container->details = details;

	g_signal_connect (container, "focus-in-event",
			  G_CALLBACK (handle_focus_in_event), NULL);
	g_signal_connect (container, "focus-out-event",
			  G_CALLBACK (handle_focus_out_event), NULL);

	if (!setup_prefs) {
		g_signal_connect_swapped (nautilus_icon_view_preferences,
					  "changed::" NAUTILUS_PREFERENCES_ICON_VIEW_TEXT_ELLIPSIS_LIMIT,
					  G_CALLBACK (text_ellipsis_limit_changed_callback),
					  NULL);
		text_ellipsis_limit_changed_callback (NULL);

		g_signal_connect_swapped (nautilus_icon_view_preferences,
					  "changed::" NAUTILUS_PREFERENCES_DESKTOP_TEXT_ELLIPSIS_LIMIT,
					  G_CALLBACK (desktop_text_ellipsis_limit_changed_callback),
					  NULL);
		desktop_text_ellipsis_limit_changed_callback (NULL);

		setup_prefs = TRUE;
	}
}
