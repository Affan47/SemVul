on_entry_config_ipv6_trt_prefix_activate(GtkEditable *unused_editable,
		gpointer unused_udata)
{
	const gchar *endptr;
	host_addr_t addr;
   	gchar *text;

	(void) unused_editable;
	(void) unused_udata;
	text = STRTRACK(gtk_editable_get_chars(
        GTK_EDITABLE(gui_dlg_prefs_lookup("entry_config_ipv6_trt_prefix")),
        0, -1));
	g_strstrip(text);
	if (
		string_to_host_addr(text, &endptr, &addr)
			&& '\0' == endptr[0]
			&& host_addr_is_ipv6(addr)
	) {
		gnet_prop_set_ip_val(PROP_IPV6_TRT_PREFIX, addr);
	} else if (0 == strcmp(text, "") || 0 == strcmp(text, "<none>")) {
		gnet_prop_set_ip_val(PROP_IPV6_TRT_PREFIX, zero_host_addr);
	}
	G_FREE_NULL(text);
}
