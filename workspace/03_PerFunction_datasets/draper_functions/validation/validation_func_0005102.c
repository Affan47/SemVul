regbranch(regex_t *preg, int *flagp )
{
	int ret;
	int chain;
	int latest;
	int flags;

	*flagp = WORST;

	ret = regnode(preg, BRANCH);
	chain = 0;
	while (*preg->regparse != '\0' && *preg->regparse != ')' &&
	       *preg->regparse != '|') {
		latest = regpiece(preg, &flags);
		if (latest == 0)
			return 0;
		*flagp |= flags&HASWIDTH;
		if (chain == 0) {
			*flagp |= flags&SPSTART;
		}
		else {
			regtail(preg, chain, latest);
		}
		chain = latest;
	}
	if (chain == 0)
		(void) regnode(preg, NOTHING);

	return(ret);
}
