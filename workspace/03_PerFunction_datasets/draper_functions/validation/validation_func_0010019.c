un_op(__isl_take isl_union_map *umap,
	int (*fn)(void **, void *))
{
	umap = isl_union_map_cow(umap);
	if (!umap)
		return NULL;

	if (isl_hash_table_foreach(umap->dim->ctx, &umap->table, fn, NULL) < 0)
		goto error;

	return umap;
error:
	isl_union_map_free(umap);
	return NULL;
}
