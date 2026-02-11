test_array_remove ()
{
	GArray *array = g_array_new (FALSE, FALSE, sizeof (int));
	int v[] = {30, 29, 28, 27, 26, 25};

	g_array_append_vals (array, v, 6);

	if (6 != array->len)
		return FAILED ("append_vals fail");

	g_array_remove_index (array, 3);

	if (5 != array->len)
		return FAILED ("remove_index failed to update length");

	if (26 != g_array_index (array, int, 3))
		return FAILED ("remove_index failed to update the array");

	g_array_free (array, TRUE);

	return NULL;
}
