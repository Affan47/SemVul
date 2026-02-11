tls_prune_sessions(void)
{
    const char *fname = NULL;
    char *tofree = NULL;
    int ret;
    struct prunerock prock;

    fname = config_getstring(IMAPOPT_TLSCACHE_DB_PATH);


    if (!fname) {
	tofree = strconcat(config_dir, FNAME_TLSSESSIONS, (char *)NULL);
	fname = tofree;
    }

    ret = (DB->open)(fname, 0, &sessdb);
    if (ret != CYRUSDB_OK) {
	syslog(LOG_ERR, "DBERROR: opening %s: %s",
	       fname, cyrusdb_strerror(ret));
	return 1;
    }
    else {

	sess_dbopen = 1;
	prock.count = prock.deletions = 0;
	DB->foreach(sessdb, "", 0, &prune_p, &prune_cb, &prock, NULL);
	(DB->close)(sessdb);
	sessdb = NULL;
	sess_dbopen = 0;

	syslog(LOG_NOTICE, "tls_prune: purged %d out of %d entries",
	       prock.deletions, prock.count);
    }

    free(tofree);

    return 0;
}
