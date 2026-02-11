search_gui_new_search(const gchar *query, guint32 flags, search_t **search)
{
    guint32 timeout;
	gboolean ret;

    gnet_prop_get_guint32_val(PROP_SEARCH_REISSUE_TIMEOUT, &timeout);

	if (!((SEARCH_F_PASSIVE | SEARCH_F_WHATS_NEW) & flags))
		query = lazy_ui_string_to_utf8(query);

    ret = search_gui_new_search_full(query,
			search_gui_configured_media_type(),
			tm_time(),
			GUI_PROPERTY(search_lifetime), timeout,
			GUI_PROPERTY(search_sort_default_column),
			GUI_PROPERTY(search_sort_default_order),
			flags | SEARCH_F_ENABLED, search);

	return ret;
}
