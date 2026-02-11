__dbreg_fid_to_fname(dblp, fid, have_lock, fnamep)
	DB_LOG *dblp;
	u_int8_t *fid;
	int have_lock;
	FNAME **fnamep;
{
	ENV *env;
	FNAME *fnp;
	LOG *lp;
	int ret;

	env = dblp->env;
	lp = dblp->reginfo.primary;

	ret = -1;

	if (!have_lock)
		MUTEX_LOCK(env, lp->mtx_filelist);
	SH_TAILQ_FOREACH(fnp, &lp->fq, q, __fname)
		if (memcmp(fnp->ufid, fid, DB_FILE_ID_LEN) == 0) {
			*fnamep = fnp;
			ret = 0;
			break;
		}
	if (!have_lock)
		MUTEX_UNLOCK(env, lp->mtx_filelist);

	return (ret);
}
