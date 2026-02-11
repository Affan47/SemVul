lookup_close_lookup(struct autofs_point *ap)
{
	struct map_source *map;

	map = ap->entry->maps;
	if (!map)
		return;

	while (map) {
		lookup_close_lookup_instances(map);
		map = map->next;
	}

	return;
}
