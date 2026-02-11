test_enumerate_objects (Test *test, gconstpointer unused)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GError *error = NULL;
	GckEnumerator *en;
	GList *objects;

	gck_builder_add_string (&builder, CKA_LABEL, "Private Capitalize Key");
	en = gck_modules_enumerate_objects (test->modules, gck_builder_end (&builder), 0);
	g_assert (GCK_IS_ENUMERATOR (en));

	objects = gck_enumerator_next_n (en, -1, NULL, &error);
	g_assert_no_error (error);
	g_assert_cmpint (g_list_length (objects), ==, 1);
	g_assert (GCK_IS_OBJECT (objects->data));

	gck_list_unref_free (objects);
	g_object_unref (en);
}
