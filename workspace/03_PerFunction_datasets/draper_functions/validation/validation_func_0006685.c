disconnect_children (GsfOutfileZip *zip)
{
	unsigned i;

	if (!zip->root_order)
		return;

	for (i = 0 ; i < zip->root_order->len ; i++) {
		GsfOutfileZip *child =
			g_ptr_array_index (zip->root_order, i);
		if (child)
			g_object_unref (child);
	}
	g_ptr_array_free (zip->root_order, TRUE);
	zip->root_order = NULL;
}
