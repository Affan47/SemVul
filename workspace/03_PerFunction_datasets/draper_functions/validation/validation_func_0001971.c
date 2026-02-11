check_map_indirect(struct autofs_point *ap,
			      char *key, int key_len,
			      struct lookup_context *ctxt)
{
	struct map_source *source;
	struct mapent_cache *mc;
	struct mapent *exists;
	unsigned int map_order;
	int ret = 0;

	source = ap->entry->current;
	ap->entry->current = NULL;
	master_source_current_signal(ap->entry);

	mc = source->mc;

	master_source_current_wait(ap->entry);
	ap->entry->current = source;


	ret = lookup_one(ap, key, key_len, ctxt);
	if (ret == CHE_FAIL)
		return NSS_STATUS_NOTFOUND;

	if (ret < 0) {


		exists = cache_lookup(mc, key);
		if (exists && exists->source == source)
			return NSS_STATUS_SUCCESS;

		warn(ap->logopt,
		     MODPREFIX "lookup for %s failed: %s",
		     key, yperr_string(-ret));

		return NSS_STATUS_UNAVAIL;
	}


	map_order = get_map_order(ctxt->domainname, ctxt->mapname);
	if (map_order > ctxt->order) {
		ctxt->order = map_order;
		source->stale = 1;
	}

	cache_writelock(mc);
	exists = cache_lookup_distinct(mc, key);

	if (exists && exists->source == source && ret & CHE_MISSING) {
		if (exists->mapent) {
			free(exists->mapent);
			exists->mapent = NULL;
			source->stale = 1;
			exists->status = 0;
		}
	}
	cache_unlock(mc);

	if (ret == CHE_MISSING) {
		struct mapent *we;
		int wild = CHE_MISSING;

		master_source_current_wait(ap->entry);
		ap->entry->current = source;

		wild = lookup_wild(ap, ctxt);


		cache_writelock(mc);
		we = cache_lookup_distinct(mc, "*");
		if (we) {

			if (we->source == source && (wild & CHE_MISSING)) {
				cache_delete(mc, "*");
				source->stale = 1;
			}
		} else {

			if (wild & (CHE_OK | CHE_UPDATED))
				source->stale = 1;
		}
		cache_unlock(mc);

		if (wild & (CHE_OK | CHE_UPDATED))
			return NSS_STATUS_SUCCESS;
	}

	if (ret == CHE_MISSING)
		return NSS_STATUS_NOTFOUND;

	return NSS_STATUS_SUCCESS;
}
