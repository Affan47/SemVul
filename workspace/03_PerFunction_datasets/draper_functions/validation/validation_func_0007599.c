log_reopen_all(bool daemonized)
{
	size_t i;
	bool success = TRUE;

	for (i = 0; i < G_N_ELEMENTS(logfile); i++) {
		struct logfile *lf = &logfile[i];

		if (NULL == lf->path) {
			if (daemonized)
				log_set_disabled(i, TRUE);
			continue;
		}

		if (!log_reopen(i))
			success = FALSE;
	}

	return success;
}
