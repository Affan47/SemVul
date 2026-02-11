PrintCatCacheListLeakWarning(CatCList *list)
{
	elog(WARNING, "cache reference leak: cache %s (%d), list %p has count %d",
		 list->my_cache->cc_relname, list->my_cache->id,
		 list, list->refcount);
}
