complete_destroy (Complete *complete)
{
	g_assert (complete->func);
	if (complete->object)
		g_object_unref (complete->object);
	g_slice_free (Complete, complete);
}
