wrap_C_Finalize (CK_VOID_PTR reserved)
{
	CK_FUNCTION_LIST_PTR funcs;
	GList *l;

	G_LOCK (wrap_layer);

		for (l = wrap_modules; l != NULL; l = g_list_next (l)) {
			funcs = l->data;
			(funcs->C_Finalize) (NULL);
		}
		g_free (wrap_mappings);
		wrap_mappings = NULL;

		g_hash_table_destroy (wrap_sessions);
		wrap_sessions = NULL;

	G_UNLOCK (wrap_layer);

	return CKR_OK;
}
