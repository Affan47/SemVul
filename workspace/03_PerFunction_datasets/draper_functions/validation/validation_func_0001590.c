dump_errormap(StoreEntry * entry, const char *name, errormap * map)
{
    while (map) {
	struct error_map_entry *me;
	storeAppendPrintf(entry, "%s %s",
	    name, map->url);
	for (me = map->map; me; me = me->next)
	    storeAppendPrintf(entry, " %s", me->value);
	storeAppendPrintf(entry, "\n");
	map = map->next;
    }
}
