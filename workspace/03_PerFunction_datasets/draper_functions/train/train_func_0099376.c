get_owner_list( int (*cb_func)(const char *, void *),
			   const char *c,
			   const char *mailbox_owner, void *arg)
{
	char *a;
	int rc;
	const char *p, *q;

	a=malloc(sizeof("user=")+strlen(c));
	if (!a)
		return -1;

	strcat(strcpy(a, "user="), c);

	rc=(*cb_func)(a, arg);

	if (rc == 0 && strcmp(a, mailbox_owner) == 0)
		rc=(*cb_func)("owner", arg);
	free(a);

	if (rc)
		return rc;

	c=getenv("OPTIONS");

	for (p=c; p && *p; )
	{
		if (*p == ',')
		{
			++p;
			continue;
		}

		q=p;
		while (*p && *p != ',')
			++p;

		if (strncmp(q, "group=", 6) == 0)
		{
			a=malloc(p-q+1);
			if (!a)
				return -1;

			memcpy(a, q, p-q);
			a[p-q]=0;
			rc=(*cb_func)(a, arg);
			free(a);
			if (rc)
				return rc;
		}
	}
	return 0;
}
