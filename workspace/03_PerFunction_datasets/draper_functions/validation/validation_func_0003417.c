addstdenv(struct substvar *sv)
{
	struct substvar *list = sv;
	struct thread_stdenv_vars *tsv;
	char numbuf[16];

	tsv = pthread_getspecific(key_thread_stdenv_vars);
	if (tsv) {
		int ret;
		long num;

		num = (long) tsv->uid;
		ret = sprintf(numbuf, "%ld", num);
		if (ret > 0)
			list = macro_addvar(list, "UID", 3, numbuf);
		num = (long) tsv->gid;
		ret = sprintf(numbuf, "%ld", num);
		if (ret > 0)
			list = macro_addvar(list, "GID", 3, numbuf);
		list = macro_addvar(list, "USER", 4, tsv->user);
		list = macro_addvar(list, "GROUP", 5, tsv->group);
		list = macro_addvar(list, "HOME", 4, tsv->home);
	}
	return list;
}
