ck_hs_put_internal(struct ck_hs *hs,
    unsigned long h,
    const void *key,
    enum ck_hs_probe_behavior behavior)
{
	const void **slot, **first, *object, *insert;
	unsigned long n_probes;
	struct ck_hs_map *map;

restart:
	map = hs->map;

	slot = ck_hs_map_probe(hs, map, &n_probes, &first, h, key, &object,
	    map->probe_limit, behavior);

	if (slot == NULL && first == NULL) {
		if (ck_hs_grow(hs, map->capacity << 1) == false)
			return false;

		goto restart;
	}


	if (object != NULL)
		return false;

	ck_hs_map_bound_set(map, h, n_probes);
	insert = ck_hs_marshal(hs->mode, key, h);

	if (first != NULL) {

		ck_pr_store_ptr(first, insert);
	} else {

		ck_pr_store_ptr(slot, insert);
	}

	ck_hs_map_postinsert(hs, map);
	return true;
}
