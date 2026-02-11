__memp_bh_settxn(dbmp, mfp, bhp, vtd)
	DB_MPOOL *dbmp;
	MPOOLFILE *mfp;
	BH *bhp;
	void *vtd;
{
	ENV *env;
	TXN_DETAIL *td;

	env = dbmp->env;
	td = (TXN_DETAIL *)vtd;

	if (td == NULL) {
		__db_errx(env, DB_STR_A("3002",
		    "%s: non-transactional update to a multiversion file",
		    "%s"), __memp_fns(dbmp, mfp));
		return (EINVAL);
	}

	if (bhp->td_off != INVALID_ROFF) {
		DB_ASSERT(env, BH_OWNER(env, bhp) == td);
		return (0);
	}

	bhp->td_off = R_OFFSET(&env->tx_handle->reginfo, td);
	return (__txn_add_buffer(env, td));
}
