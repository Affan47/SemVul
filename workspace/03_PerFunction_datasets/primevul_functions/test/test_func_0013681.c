tilde_expand(const char *filename, uid_t uid, char **retp)
{
	const char *path, *sep;
	char user[128], *ret;
	struct passwd *pw;
	u_int len, slash;

	if (*filename != '~') {
		*retp = xstrdup(filename);
		return 0;
	}
	filename++;

	path = strchr(filename, '/');
	if (path != NULL && path > filename) {
		slash = path - filename;
		if (slash > sizeof(user) - 1) {
			error_f("~username too long");
			return -1;
		}
		memcpy(user, filename, slash);
		user[slash] = '\0';
		if ((pw = getpwnam(user)) == NULL) {
			error_f("No such user %s", user);
			return -1;
		}
	} else if ((pw = getpwuid(uid)) == NULL) {
		error_f("No such uid %ld", (long)uid);
		return -1;
	}


	len = strlen(pw->pw_dir);
	if (len == 0 || pw->pw_dir[len - 1] != '/')
		sep = "/";
	else
		sep = "";


	if (path != NULL)
		filename = path + 1;

	if (xasprintf(&ret, "%s%s%s", pw->pw_dir, sep, filename) >= PATH_MAX) {
		error_f("Path too long");
		return -1;
	}

	*retp = ret;
	return 0;
}
