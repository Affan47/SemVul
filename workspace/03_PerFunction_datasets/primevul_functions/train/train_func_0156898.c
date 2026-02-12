NUM_cache_getnew(char *str)
{
	NUMCacheEntry *ent;


	if (NUMCounter >= (INT_MAX - NUM_CACHE_FIELDS - 1))
	{
		NUMCounter = 0;

		for (ent = NUMCache; ent <= (NUMCache + NUM_CACHE_FIELDS); ent++)
			ent->age = (++NUMCounter);
	}


	if (n_NUMCache > NUM_CACHE_FIELDS)
	{
		NUMCacheEntry *old = NUMCache + 0;

#ifdef DEBUG_TO_FROM_CHAR
		elog(DEBUG_elog_output, "Cache is full (%d)", n_NUMCache);
#endif
		for (ent = NUMCache; ent <= (NUMCache + NUM_CACHE_FIELDS); ent++)
		{


			if (ent->str[0] == '\0')
			{
				old = ent;
				break;
			}
			if (ent->age < old->age)
				old = ent;
		}
#ifdef DEBUG_TO_FROM_CHAR
		elog(DEBUG_elog_output, "OLD: \"%s\" AGE: %d", old->str, old->age);
#endif
		StrNCpy(old->str, str, NUM_CACHE_SIZE + 1);

		old->age = (++NUMCounter);
		ent = old;
	}
	else
	{
#ifdef DEBUG_TO_FROM_CHAR
		elog(DEBUG_elog_output, "NEW (%d)", n_NUMCache);
#endif
		ent = NUMCache + n_NUMCache;
		StrNCpy(ent->str, str, NUM_CACHE_SIZE + 1);

		ent->age = (++NUMCounter);
		++n_NUMCache;
	}

	zeroize_NUM(&ent->Num);

	last_NUMCacheEntry = ent;
	return ent;
}
