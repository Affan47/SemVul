ck_rhs_map_create(struct ck_rhs *hs, unsigned long entries)
{
	struct ck_rhs_map *map;
	unsigned long size, n_entries, limit;

	n_entries = ck_internal_power_2(entries);
	if (n_entries < CK_RHS_PROBE_L1)
		n_entries = CK_RHS_PROBE_L1;

	if (hs->mode & CK_RHS_MODE_READ_MOSTLY)
		size = sizeof(struct ck_rhs_map) +
		    (sizeof(void *) * n_entries +
		     sizeof(struct ck_rhs_no_entry_desc) * n_entries +
		     2 * CK_MD_CACHELINE - 1);
	else
		size = sizeof(struct ck_rhs_map) +
		    (sizeof(struct ck_rhs_entry_desc) * n_entries +
		     CK_MD_CACHELINE - 1);
	map = hs->m->malloc(size);
	if (map == NULL)
		return NULL;
	map->read_mostly = !!(hs->mode & CK_RHS_MODE_READ_MOSTLY);

	map->size = size;

	limit = ck_internal_max(n_entries >> (CK_RHS_PROBE_L1_SHIFT + 2), CK_RHS_PROBE_L1_DEFAULT);
	if (limit > UINT_MAX)
		limit = UINT_MAX;

	map->probe_limit = (unsigned int)limit;
	map->probe_maximum = 0;
	map->capacity = n_entries;
	map->step = ck_internal_bsf(n_entries);
	map->mask = n_entries - 1;
	map->n_entries = 0;

	map->max_entries = (map->capacity * (unsigned long)hs->load_factor) / 100;

	if (map->read_mostly) {
		map->entries.no_entries.entries = (void *)(((uintptr_t)&map[1] +
		    CK_MD_CACHELINE - 1) & ~(CK_MD_CACHELINE - 1));
		map->entries.no_entries.descs = (void *)(((uintptr_t)map->entries.no_entries.entries + (sizeof(void *) * n_entries) + CK_MD_CACHELINE - 1) &~ (CK_MD_CACHELINE - 1));
		memset(map->entries.no_entries.entries, 0,
		    sizeof(void *) * n_entries);
		memset(map->entries.no_entries.descs, 0,
		    sizeof(struct ck_rhs_no_entry_desc));
		map->offset_mask = (CK_MD_CACHELINE / sizeof(void *)) - 1;
		map->probe_func = ck_rhs_map_probe_rm;

	} else {
		map->entries.descs = (void *)(((uintptr_t)&map[1] +
		    CK_MD_CACHELINE - 1) & ~(CK_MD_CACHELINE - 1));
		memset(map->entries.descs, 0, sizeof(struct ck_rhs_entry_desc) * n_entries);
		map->offset_mask = (CK_MD_CACHELINE / sizeof(struct ck_rhs_entry_desc)) - 1;
		map->probe_func = ck_rhs_map_probe;
	}
	memset(map->generation, 0, sizeof map->generation);


	ck_pr_fence_store();
	return map;
}
