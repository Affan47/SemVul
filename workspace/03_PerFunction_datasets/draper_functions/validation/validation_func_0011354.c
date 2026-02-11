isl_union_access_info_normalize(
	__isl_take isl_union_access_info *access)
{
	if (!access)
		return NULL;
	access->may_source = isl_union_map_subtract(access->may_source,
				    isl_union_map_copy(access->must_source));
	if (!access->may_source)
		return isl_union_access_info_free(access);

	return access;
}
