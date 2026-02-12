int commonio_lock (struct commonio_db *db)
{
#ifdef HAVE_LCKPWDF


	if (0 == lock_count) {
		if (lckpwdf () == -1) {
			if (geteuid () != 0) {
				(void) fprintf (stderr,
				                "%s: Permission denied.\n",
				                Prog);
			}
			return 0;
		}
	}

	if (commonio_lock_nowait (db, true) != 0) {
		return 1;
	}

	ulckpwdf ();
	return 0;
#else
	int i;


#ifndef LOCK_TRIES
#define LOCK_TRIES 15
#endif

#ifndef LOCK_SLEEP
#define LOCK_SLEEP 1
#endif
	for (i = 0; i < LOCK_TRIES; i++) {
		if (i > 0) {
			sleep (LOCK_SLEEP);
		}
		if (commonio_lock_nowait (db, i==LOCK_TRIES-1) != 0) {
			return 1;
		}

		if (geteuid () != 0) {
			(void) fprintf (stderr, "%s: Permission denied.\n",
			                Prog);
			return 0;
		}
	}
	return 0;
#endif
}
