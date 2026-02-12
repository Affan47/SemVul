parse_user_host_path(const char *s, char **userp, char **hostp, char **pathp)
{
	char *user = NULL, *host = NULL, *path = NULL;
	char *sdup, *tmp;
	int ret = -1;

	if (userp != NULL)
		*userp = NULL;
	if (hostp != NULL)
		*hostp = NULL;
	if (pathp != NULL)
		*pathp = NULL;

	sdup = xstrdup(s);


	if ((tmp = colon(sdup)) == NULL)
		goto out;


	*tmp++ = '\0';
	if (*tmp == '\0')
		tmp = ".";
	path = xstrdup(tmp);


	tmp = strrchr(sdup, '@');
	if (tmp != NULL) {
		*tmp++ = '\0';
		host = xstrdup(cleanhostname(tmp));
		if (*sdup != '\0')
			user = xstrdup(sdup);
	} else {
		host = xstrdup(cleanhostname(sdup));
		user = NULL;
	}


	if (userp != NULL) {
		*userp = user;
		user = NULL;
	}
	if (hostp != NULL) {
		*hostp = host;
		host = NULL;
	}
	if (pathp != NULL) {
		*pathp = path;
		path = NULL;
	}
	ret = 0;
out:
	free(sdup);
	free(user);
	free(host);
	free(path);
	return ret;
}
