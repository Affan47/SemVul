proto_init(GSList *register_all_plugin_protocols_list,
	   GSList *register_all_plugin_handoffs_list,
	   register_cb cb,
	   gpointer client_data)
{
	proto_cleanup_base();

	proto_names        = g_hash_table_new(g_str_hash, g_str_equal);
	proto_short_names  = g_hash_table_new(g_str_hash, g_str_equal);
	proto_filter_names = g_hash_table_new(g_str_hash, g_str_equal);

	gpa_hfinfo.len           = 0;
	gpa_hfinfo.allocated_len = 0;
	gpa_hfinfo.hfi           = NULL;
	gpa_name_map             = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, save_same_name_hfinfo);
	gpa_protocol_aliases     = g_hash_table_new(g_str_hash, g_str_equal);
	deregistered_fields      = g_ptr_array_new();
	deregistered_data        = g_ptr_array_new();


	ftypes_initialize();


	address_types_initialize();


	hf_text_only = proto_register_field_init(&hfi_text_only, -1);


	register_show_exception();
	register_type_length_mismatch();
	register_number_string_decoding_error();
	register_string_errors();


	register_all_protocols(cb, client_data);


	for (GSList *l = register_all_plugin_protocols_list; l != NULL; l = l->next) {
		((void (*)(register_cb, gpointer))l->data)(cb, client_data);
	}

#ifdef HAVE_PLUGINS

	if (cb)
		(*cb)(RA_PLUGIN_REGISTER, NULL, client_data);
	g_slist_foreach(dissector_plugins, call_plugin_register_protoinfo, NULL);
#endif


	register_all_protocol_handoffs(cb, client_data);


	for (GSList *l = register_all_plugin_handoffs_list; l != NULL; l = l->next) {
		((void (*)(register_cb, gpointer))l->data)(cb, client_data);
	}

#ifdef HAVE_PLUGINS

	if (cb)
		(*cb)(RA_PLUGIN_HANDOFF, NULL, client_data);
	g_slist_foreach(dissector_plugins, call_plugin_register_handoff, NULL);
#endif


	protocols = g_list_sort(protocols, proto_compare_name);


	tree_is_expanded = g_new0(guint32, (num_tree_types/32)+1);
}
