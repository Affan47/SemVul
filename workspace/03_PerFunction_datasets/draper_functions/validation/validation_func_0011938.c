fetch_pagbuf(DBM *db, long pagnum)
{
	db->pagfetch++;

#ifdef LRU

	if G_UNLIKELY(NULL == db->cache) {
		lru_init(db);
	}
#endif


	if (pagnum != db->pagbno) {
		ssize_t got;

#ifdef LRU
		{
			bool loaded;

			if G_UNLIKELY(!readbuf(db, pagnum, &loaded)) {
				db->pagbno = -1;
				return FALSE;
			}

			if (loaded) {
				db->pagbno = pagnum;
				return TRUE;
			}
		}
#endif


		db->pagread++;
		got = compat_pread(db->pagf, db->pagbuf, DBM_PBLKSIZ, OFF_PAG(pagnum));
		if G_UNLIKELY(got < 0) {
			g_critical("sdbm: \"%s\": cannot read page #%ld: %m",
				sdbm_name(db), pagnum);
			ioerr(db, FALSE);
			db->pagbno = -1;
			return FALSE;
		}
		if G_UNLIKELY(got < DBM_PBLKSIZ) {
			if (got > 0)
				g_critical("sdbm: \"%s\": partial read (%u bytes) of page #%ld",
					sdbm_name(db), (unsigned) got, pagnum);
			memset(db->pagbuf + got, 0, DBM_PBLKSIZ - got);
		}
		if G_UNLIKELY(!sdbm_internal_chkpage(db->pagbuf)) {
			g_critical("sdbm: \"%s\": corrupted page #%ld, clearing",
				sdbm_name(db), pagnum);
			memset(db->pagbuf, 0, DBM_PBLKSIZ);
			db->bad_pages++;
		}
		db->pagbno = pagnum;

		debug(("pag read: %ld\n", pagnum));
	} else {
		db->pagbno_hit++;
	}

	return TRUE;
}
