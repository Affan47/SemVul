static void find_jobs(int vtime, cron_db * db, int doWild, int doNonWild, long vGMToff) {
	char *orig_tz, *job_tz;
	time_t virtualSecond = vtime * SECONDS_PER_MINUTE;
	time_t virtualGMTSecond = virtualSecond - vGMToff;
	struct tm *tm;
	int minute, hour, dom, month, dow;
	user *u;
	entry *e;
	const char *uname;


#define maketime(tz1, tz2) do { \
	char *t = tz1; \
	if (t != NULL && *t != '\0') { \
		setenv("TZ", t, 1); \
		tm = localtime(&virtualGMTSecond); \
	} else { if ((tz2) != NULL) \
			setenv("TZ", (tz2), 1); \
		else \
			unsetenv("TZ"); \
		tm = gmtime(&virtualSecond); \
	} \
	minute = tm->tm_min -FIRST_MINUTE; \
	hour = tm->tm_hour -FIRST_HOUR; \
	dom = tm->tm_mday -FIRST_DOM; \
	month = tm->tm_mon +1  -FIRST_MONTH; \
	dow = tm->tm_wday -FIRST_DOW; \
	} while (0)

	orig_tz = getenv("TZ");
	maketime(NULL, orig_tz);

	Debug(DSCH, ("[%ld] tick(%d,%d,%d,%d,%d) %s %s\n",
			(long) getpid(), minute, hour, dom, month, dow,
			doWild ? " " : "No wildcard", doNonWild ? " " : "Wildcard only"))


		for (u = db->head; u != NULL; u = u->next) {
		for (e = u->crontab; e != NULL; e = e->next) {
			Debug(DSCH | DEXT, ("user [%s:%ld:%ld:...] cmd=\"%s\"\n",
					e->pwd->pw_name, (long) e->pwd->pw_uid,
					(long) e->pwd->pw_gid, e->cmd))
				uname = e->pwd->pw_name;

			if (getpwnam(uname) != NULL) {
				job_tz = env_get("CRON_TZ", e->envp);
				maketime(job_tz, orig_tz);

				if (bit_test(e->minute, minute) &&
					bit_test(e->hour, hour) &&
					bit_test(e->month, month) &&
					(((e->flags & DOM_STAR) || (e->flags & DOW_STAR))
						? (bit_test(e->dow, dow) && bit_test(e->dom, dom))
						: (bit_test(e->dow, dow) || bit_test(e->dom, dom))
					)
					) {
					if (job_tz != NULL && vGMToff != GMToff)


						continue;

					if ((doNonWild &&
							!(e->flags & (MIN_STAR | HR_STAR))) ||
						(doWild && (e->flags & (MIN_STAR | HR_STAR))))
						job_add(e, u);
				}
			}
		}
	}
	if (orig_tz != NULL)
		setenv("TZ", orig_tz, 1);
	else
		unsetenv("TZ");
}
