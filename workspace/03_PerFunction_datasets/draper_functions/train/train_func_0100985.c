lock_stats(DB_ENV *dbenvp)
{
	DB_LOCK_STAT *sp;
	int ret;

	if (stats_internal != NULL) {
		CDB___lock_dump_region(dbenvp, stats_internal, stdout);
		return (0);
	}

	if ((ret = CDB_lock_stat(dbenvp, &sp, NULL)) != 0) {
		dbenvp->err(dbenvp, ret, NULL);
		return (1);
	}

	dl("Last allocated locker ID.\n", (u_long)sp->st_lastid);
	dl("Number of lock modes.\n", (u_long)sp->st_nmodes);
	dl("Maximum number of locks possible.\n", (u_long)sp->st_maxlocks);
	dl("Current lockers.\n", (u_long)sp->st_nlockers);
	dl("Maximum current lockers.\n", (u_long)sp->st_nlockers);
	dl("Number of lock requests.\n", (u_long)sp->st_nrequests);
	dl("Number of lock releases.\n", (u_long)sp->st_nreleases);
	dl("Number of lock conflicts.\n", (u_long)sp->st_nconflicts);
	dl("Number of deadlocks.\n", (u_long)sp->st_ndeadlocks);
	dl_bytes("Lock region size.\n",
	    (u_long)0, (u_long)0, (u_long)sp->st_regsize);
	dl("The number of region locks granted without waiting.\n",
	    (u_long)sp->st_region_nowait);
	dl("The number of region locks granted after waiting.\n",
	    (u_long)sp->st_region_wait);

	return (0);
}
