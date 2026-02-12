extern char *x11_get_xauth(void)
{
	int status, matchlen;
	char **xauth_argv;
	regex_t reg;
	regmatch_t regmatch[2];
	char *result, *cookie;


	static char *cookie_pattern = "^[[:alnum:]./-]+:[[:digit:]]+"
				      "[[:space:]]+MIT-MAGIC-COOKIE-1"
				      "[[:space:]]+([[:xdigit:]]+)$";

	xauth_argv = xmalloc(sizeof(char *) * 10);
	xauth_argv[0] = xstrdup("xauth");
	xauth_argv[1] = xstrdup("list");
	xauth_argv[2] = xstrdup(getenv("DISPLAY"));

	result = run_command("xauth", XAUTH_PATH, xauth_argv, 10000, 0,
			     &status);

	debug2("%s: result from xauth: %s", __func__, result);

	free_command_argv(xauth_argv);

	if (status) {
		error("Problem running xauth command. "
		      "Cannot use X11 forwarding.");
		exit(-1);

	}

	regcomp(&reg, cookie_pattern, REG_EXTENDED|REG_NEWLINE);
	if (regexec(&reg, result, 2, regmatch, 0) == REG_NOMATCH) {
		error("%s: Could not retrieve magic cookie. "
		      "Cannot use X11 forwarding.", __func__);
		exit(-1);
	}

	matchlen = regmatch[1].rm_eo - regmatch[1].rm_so + 1;
	cookie = xmalloc(matchlen);
	strlcpy(cookie, result + regmatch[1].rm_so, matchlen);
	xfree(result);

	return cookie;
}
