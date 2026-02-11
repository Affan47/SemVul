go_data_cache_permute (GODataCache const *cache,
		       GArray const *field_order,
		       GArray *permutation)
{
	GODataCacheCompare info;

	g_return_if_fail (IS_GO_DATA_CACHE (cache));
	g_return_if_fail (field_order);
	g_return_if_fail (permutation);

	info.cache = cache;
	info.field_order = field_order;
	g_array_sort_with_data (permutation,
		(GCompareDataFunc) cb_go_data_cache_cmp, &info);
}
