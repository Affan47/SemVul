__memp_remove_bucket(dbmp)
	DB_MPOOL *dbmp;
{
	ENV *env;
	MPOOL *mp;
	u_int32_t high_mask, new_bucket, old_bucket;

	env = dbmp->env;
	mp = dbmp->reginfo[0].primary;

	old_bucket = mp->nbuckets - 1;


	DB_ASSERT(env, NREGION(mp, old_bucket) == mp->nreg - 1);
	MP_MASK(mp->nbuckets - 1, high_mask);
	new_bucket = old_bucket & (high_mask >> 1);

	return (__memp_merge_buckets(dbmp, mp->nbuckets - 1,
	    old_bucket, new_bucket));
}
