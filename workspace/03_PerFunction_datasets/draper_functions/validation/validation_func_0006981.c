data_cal_handle_remove_objects_cb (EDBusCalendar *interface,
                                   GDBusMethodInvocation *invocation,
                                   GVariant *in_uid_rid_array,
                                   const gchar *in_mod_type,
                                   EDataCal *data_cal)
{
	ECalBackend *backend;
	AsyncContext *async_context;
	GFlagsClass *flags_class;
	ECalObjModType mod = 0;
	GQueue component_ids = G_QUEUE_INIT;
	gchar **flags_strv;
	gsize n_children, ii;

	backend = e_data_cal_ref_backend (data_cal);
	g_return_val_if_fail (backend != NULL, FALSE);

	flags_class = g_type_class_ref (E_TYPE_CAL_OBJ_MOD_TYPE);
	flags_strv = g_strsplit (in_mod_type, ":", -1);
	for (ii = 0; flags_strv[ii] != NULL; ii++) {
		GFlagsValue *flags_value;

		flags_value = g_flags_get_value_by_nick (
			flags_class, flags_strv[ii]);
		if (flags_value != NULL) {
			mod |= flags_value->value;
		} else {
			g_warning (
				"%s: Unknown flag: %s",
				G_STRFUNC, flags_strv[ii]);
		}
	}
	g_strfreev (flags_strv);
	g_type_class_unref (flags_class);

	n_children = g_variant_n_children (in_uid_rid_array);
	for (ii = 0; ii < n_children; ii++) {
		ECalComponentId *id;


		id = g_malloc0 (sizeof (ECalComponentId));

		g_variant_get_child (
			in_uid_rid_array, ii, "(ss)", &id->uid, &id->rid);

		if (id->uid != NULL && *id->uid == '\0') {
			e_cal_component_free_id (id);
			continue;
		}


		if (id->rid != NULL && *id->rid == '\0') {
			g_free (id->rid);
			id->rid = NULL;
		}

		g_queue_push_tail (&component_ids, id);
	}

	async_context = async_context_new (data_cal, invocation);

	e_cal_backend_remove_objects (
		backend,
		component_ids.head, mod,
		async_context->cancellable,
		data_cal_complete_remove_objects_cb,
		async_context);

	while (!g_queue_is_empty (&component_ids))
		e_cal_component_free_id (g_queue_pop_head (&component_ids));

	g_object_unref (backend);

	return TRUE;
}
