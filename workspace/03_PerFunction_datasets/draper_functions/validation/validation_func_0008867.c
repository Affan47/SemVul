__qam_open(dbp, ip, txn, name, base_pgno, mode, flags)
	DB *dbp;
	DB_THREAD_INFO *ip;
	DB_TXN *txn;
	const char *name;
	db_pgno_t base_pgno;
	int mode;
	u_int32_t flags;
{
	DBC *dbc;
	DB_MPOOLFILE *mpf;
	ENV *env;
	QMETA *qmeta;
	QUEUE *t;
	int ret, t_ret;

	env = dbp->env;
	mpf = dbp->mpf;
	t = dbp->q_internal;
	ret = 0;
	qmeta = NULL;

	if (name == NULL && t->page_ext != 0) {
		__db_errx(env, DB_STR("1134",
	"Extent size may not be specified for in-memory queue database"));
		return (EINVAL);
	}

	if (MULTIVERSION(dbp)) {
		__db_errx(env, DB_STR("1135",
		    "Multiversion queue databases are not supported"));
		return (EINVAL);
	}


	dbp->db_am_remove = __qam_remove;
	dbp->db_am_rename = __qam_rename;


	if ((ret = __db_cursor(dbp, ip, txn, &dbc,
	    LF_ISSET(DB_CREATE) && CDB_LOCKING(env) ?
	    DB_WRITECURSOR : 0)) != 0)
		return (ret);


	if ((ret = __memp_fget(mpf, &base_pgno, ip, txn, 0, &qmeta)) != 0)
		goto err;


	if (qmeta->dbmeta.magic != DB_QAMMAGIC) {
		__db_errx(env, DB_STR_A("1136",
		    "__qam_open: %s: unexpected file type or format", "%s"),
		    name);
		ret = EINVAL;
		goto err;
	}


	t->page_ext = qmeta->page_ext;

	if (t->page_ext != 0 && (ret = __qam_set_ext_data(dbp, name)) != 0)
		goto err;

	if (mode == 0)
		mode = DB_MODE_660;
	t->mode = mode;
	t->re_pad = (int)qmeta->re_pad;
	t->re_len = qmeta->re_len;
	t->rec_page = qmeta->rec_page;

	t->q_meta = base_pgno;
	t->q_root = base_pgno + 1;

err:	if (qmeta != NULL && (t_ret =
	    __memp_fput(mpf, ip, qmeta, dbc->priority)) != 0 && ret == 0)
		ret = t_ret;

	if ((t_ret = __dbc_close(dbc)) != 0 && ret == 0)
		ret = t_ret;

	return (ret);
}
