st_force_shutdown(struct autofs_point *ap)
{
	int exp;

	debug(ap->logopt, "state %d path %s", ap->state, ap->path);

	assert(ap->state == ST_READY || ap->state == ST_EXPIRE);
	ap->state = ST_SHUTDOWN_FORCE;


	exp = expire_proc(ap, 1);
	switch (exp) {
	case EXP_ERROR:
	case EXP_PARTIAL:

		if (!ap->submount)
			alarm_add(ap, ap->exp_runfreq);
		st_ready(ap);
		return 0;

	case EXP_STARTED:
		return 1;
	}
	return 0;
}
