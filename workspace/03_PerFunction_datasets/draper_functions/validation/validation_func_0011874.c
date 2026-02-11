init_trace(name)
char    *name;
{
	char env_var[256];
	register char    *p;
	trc_spec_t *trc;
	int sav_errno = errno;
	int sav_serrno = serrno;

	Cglobals_get(&trc_key,(void **)&trc,sizeof(trc_spec_t));
	if (!trace_initialized) {
		if ((p = getenv(name)) != NULL)       {
			if (atoi(p) != 0)       {
				trace_level = atoi(p);
				strcpy(env_var, name);
				strcat(env_var, "FILE");
				if ((p = getenv(env_var)) != NULL)
					trace_file = strdup(p);
				print_trace(0, "    **** ", "trace level set to %d", trace_level);
			}
		}
		trace_initialized++;
	}
	indent_level++;
	errno = sav_errno;
	serrno = sav_serrno;
}
