secret_service_store (SecretService *service,
                      const SecretSchema *schema,
                      GHashTable *attributes,
                      const gchar *collection,
                      const gchar *label,
                      SecretValue *value,
                      GCancellable *cancellable,
                      GAsyncReadyCallback callback,
                      gpointer user_data)
{
	GSimpleAsyncResult *async;
	StoreClosure *store;
	const gchar *schema_name;
	GVariant *propval;

	g_return_if_fail (service == NULL || SECRET_IS_SERVICE (service));
	g_return_if_fail (attributes != NULL);
	g_return_if_fail (label != NULL);
	g_return_if_fail (value != NULL);
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));


	if (schema != NULL && !_secret_attributes_validate (schema, attributes, G_STRFUNC, FALSE))
		return;

	async = g_simple_async_result_new  (G_OBJECT (service), callback, user_data,
	                                    secret_service_store);
	store = g_slice_new0 (StoreClosure);
	store->collection_path = _secret_util_collection_to_path (collection);
	store->cancellable = cancellable ? g_object_ref (cancellable) : NULL;
	store->value = secret_value_ref (value);
	store->properties = g_hash_table_new_full (g_str_hash, g_str_equal, NULL,
	                                           (GDestroyNotify)g_variant_unref);

	propval = g_variant_new_string (label);
	g_hash_table_insert (store->properties,
	                     SECRET_ITEM_INTERFACE ".Label",
	                     g_variant_ref_sink (propval));


	schema_name = (schema == NULL) ? NULL : schema->name;
	propval = _secret_attributes_to_variant (attributes, schema_name);
	g_hash_table_insert (store->properties,
	                     SECRET_ITEM_INTERFACE ".Attributes",
	                     g_variant_ref_sink (propval));

	g_simple_async_result_set_op_res_gpointer (async, store, store_closure_free);

	if (service == NULL) {
		secret_service_get (SECRET_SERVICE_OPEN_SESSION, cancellable,
		                    on_store_service, g_object_ref (async));

	} else {
		secret_service_create_item_dbus_path (service, store->collection_path,
		                                      store->properties, store->value,
		                                      SECRET_ITEM_CREATE_REPLACE, store->cancellable,
		                                      on_store_create, g_object_ref (async));
	}

	g_object_unref (async);
}
