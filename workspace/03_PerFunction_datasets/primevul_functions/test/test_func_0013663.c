argv_split(const char *s, int *argcp, char ***argvp, int terminate_on_comment)
{
	int r = SSH_ERR_INTERNAL_ERROR;
	int argc = 0, quote, i, j;
	char *arg, **argv = xcalloc(1, sizeof(*argv));

	*argvp = NULL;
	*argcp = 0;

	for (i = 0; s[i] != '\0'; i++) {

		if (s[i] == ' ' || s[i] == '\t')
			continue;
		if (terminate_on_comment && s[i] == '#')
			break;

		quote = 0;

		argv = xreallocarray(argv, (argc + 2), sizeof(*argv));
		arg = argv[argc++] = xcalloc(1, strlen(s + i) + 1);
		argv[argc] = NULL;


		for (j = 0; s[i] != '\0'; i++) {
			if (s[i] == '\\') {
				if (s[i + 1] == '\'' ||
				    s[i + 1] == '\"' ||
				    s[i + 1] == '\\' ||
				    (quote == 0 && s[i + 1] == ' ')) {
					i++;
					arg[j++] = s[i];
				} else {

					arg[j++] = s[i];
				}
			} else if (quote == 0 && (s[i] == ' ' || s[i] == '\t'))
				break;
			else if (quote == 0 && (s[i] == '\"' || s[i] == '\''))
				quote = s[i];
			else if (quote != 0 && s[i] == quote)
				quote = 0;
			else
				arg[j++] = s[i];
		}
		if (s[i] == '\0') {
			if (quote != 0) {

				r = SSH_ERR_INVALID_FORMAT;
				goto out;
			}
			break;
		}
	}

	*argcp = argc;
	*argvp = argv;
	argc = 0;
	argv = NULL;
	r = 0;
 out:
	if (argc != 0 && argv != NULL) {
		for (i = 0; i < argc; i++)
			free(argv[i]);
		free(argv);
	}
	return r;
}
