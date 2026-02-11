followed(CONST char *str)
{
	char		opt[2];

	if (str == 0) return;
	if (init()) return;


	for (opt[1] = '\0'; *str; ++str) {
		*opt = *str;
		if (ao_setopt(lam_args_optd, opt, (char *) 0, 1, AODOARGS))
		  return;
	}
}
