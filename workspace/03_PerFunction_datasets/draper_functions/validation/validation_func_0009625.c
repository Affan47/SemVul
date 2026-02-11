gck_mock_module_add_object (GckAttributes *attrs)
{
	GckBuilder builder;
	gboolean token;
	guint handle;

	g_return_val_if_fail (the_objects, 0);


	handle = ++unique_identifier;
	if (gck_attributes_find_boolean (attrs, CKA_TOKEN, &token)) {
		g_return_val_if_fail (token == TRUE, 0);
		gck_attributes_ref_sink (attrs);
	} else {
		gck_builder_init (&builder);
		gck_builder_add_except (&builder, attrs, CKA_TOKEN, GCK_INVALID);
		gck_builder_add_boolean (&builder, CKA_TOKEN, TRUE);
		gck_attributes_unref (attrs);
		attrs = gck_attributes_ref_sink (gck_builder_end (&builder));
	}
	g_hash_table_insert (the_objects, GUINT_TO_POINTER (handle), attrs);

	return handle;
}
