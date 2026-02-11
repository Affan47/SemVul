_goc_item_update_bounds (GocItem *item)
{
	GocItemClass *klass = GOC_ITEM_GET_CLASS (item);
	g_return_if_fail (klass != NULL);

	if (klass->update_bounds)
		klass->update_bounds (item);
	item->cached_bounds = TRUE;
}
