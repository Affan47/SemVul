teardown (Test *test, gconstpointer unused)
{
	g_object_unref (test->session);
	g_object_unref (test->slot);
	g_object_unref (test->module);

	g_assert (test->session == NULL);
	g_assert (test->slot == NULL);
	g_assert (test->module == NULL);
}
