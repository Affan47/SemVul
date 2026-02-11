zn_free_additional_subzones(zone_t *zone)
{
	struct subzone *sz = zone->zn_arena.sz_next;

	while (sz) {
		struct subzone *next = sz->sz_next;
		subzone_free_arena(sz);
		xfree(sz);
		sz = next;
	}

	zone->zn_arena.sz_next = NULL;
	zrange_clear(zone);
}
