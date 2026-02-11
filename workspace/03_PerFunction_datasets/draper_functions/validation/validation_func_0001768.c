auth(int fd, char *p)
{
	char *service;
	char *authtype;
	char	*pp;
	struct authstaticinfolist *l;

	service=p;
	if ((p=strchr(p, '\n')) == 0)	return;
	*p++=0;
	authtype=p;
	if ((p=strchr(p, '\n')) == 0)	return;
	*p++=0;

	pp=malloc(strlen(p)+1);
	if (!pp)
	{
		perror("CRIT: malloc() failed");
		return;
	}

	DPRINTF("received auth request, service=%s, authtype=%s", service, authtype);
	for (l=modulelist; l; l=l->next)
	{
		struct authstaticinfo *auth=l->info;
		const char	*modname = auth->auth_name;
		int rc;

		DPRINTF("%s: trying this module", modname);

		rc=(*auth->auth_func)(service, authtype,
				      strcpy(pp, p),
				      &printauth, &fd);

		if (rc == 0)
		{
			free(pp);
			return;
		}

		if (rc > 0)
		{
			DPRINTF("%s: TEMPFAIL - no more modules will be tried", modname);
			free(pp);
			return;
		}
		DPRINTF("%s: REJECT - try next module", modname);
	}
	DPRINTF("FAIL, all modules rejected");
	writeauth(fd, "FAIL\n", 5);
	free(pp);
}
