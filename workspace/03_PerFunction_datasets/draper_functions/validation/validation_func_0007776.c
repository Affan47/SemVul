source_selector_popup_menu (GtkWidget *widget)
{
	ESourceSelector *selector;
	ESource *source;
	gboolean res = FALSE;

	selector = E_SOURCE_SELECTOR (widget);
	source = e_source_selector_ref_primary_selection (selector);
	g_signal_emit (selector, signals[POPUP_EVENT], 0, source, NULL, &res);

	if (source != NULL)
		g_object_unref (source);

	return res;
}
