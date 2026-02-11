ck_hs_map_postinsert(struct ck_hs *hs, struct ck_hs_map *map)
{

	map->n_entries++;
	if ((map->n_entries << 1) > map->capacity)
		ck_hs_grow(hs, map->capacity << 1);

	return;
}
