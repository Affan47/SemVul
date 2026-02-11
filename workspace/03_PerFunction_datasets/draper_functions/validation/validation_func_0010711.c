cal_backend_store_internal_put_component (ECalBackendStore *store,
                                          ECalComponent *comp)
{
	FullCompObject *obj = NULL;
	const gchar *uid;

	g_return_val_if_fail (comp != NULL, FALSE);

	e_cal_component_get_uid (comp, &uid);

	if (uid == NULL) {
		g_warning ("The component does not have a valid uid \n");
		return FALSE;
	}

	g_rw_lock_writer_lock (&store->priv->lock);
	obj = g_hash_table_lookup (store->priv->comp_uid_hash, uid);
	if (obj == NULL) {
		obj = create_new_full_object ();
		g_hash_table_insert (
			store->priv->comp_uid_hash, g_strdup (uid), obj);
	}

	if (!e_cal_component_is_instance (comp)) {
		if (obj->comp != NULL)
			g_object_unref (obj->comp);

		obj->comp = comp;
	} else {
		gchar *rid = e_cal_component_get_recurid_as_string (comp);

		g_hash_table_insert (obj->recurrences, rid, comp);
	}

	g_object_ref (comp);
	g_rw_lock_writer_unlock (&store->priv->lock);

	return TRUE;
}
