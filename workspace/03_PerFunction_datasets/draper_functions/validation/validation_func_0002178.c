izoom_in(IAnjutaEditorZoom* zoom, GError** e)
{
	TextEditor* te = TEXT_EDITOR(zoom);
	gint zoom_factor = g_settings_get_int (te->docman_settings,
												   TEXT_ZOOM_FACTOR) + 1;

	if (zoom_factor > MAX_ZOOM_FACTOR)
		zoom_factor = MAX_ZOOM_FACTOR;
	else if (zoom_factor < MIN_ZOOM_FACTOR)
		zoom_factor = MIN_ZOOM_FACTOR;

	g_settings_set_int (te->docman_settings, TEXT_ZOOM_FACTOR, zoom_factor);
}
