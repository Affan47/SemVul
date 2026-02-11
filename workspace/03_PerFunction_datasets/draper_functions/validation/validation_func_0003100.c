reg(regex_t *preg, int paren , int *flagp )
{
	int ret;
	int br;
	int ender;
	int parno = 0;
	int flags;

	*flagp = HASWIDTH;


	if (paren) {
		if (preg->regparse[0] == '?' && preg->regparse[1] == ':') {

			preg->regparse += 2;
			parno = -1;
		}
		else {
			parno = ++preg->re_nsub;
		}
		ret = regnode(preg, OPEN+parno);
	} else
		ret = 0;


	br = regbranch(preg, &flags);
	if (br == 0)
		return 0;
	if (ret != 0)
		regtail(preg, ret, br);
	else
		ret = br;
	if (!(flags&HASWIDTH))
		*flagp &= ~HASWIDTH;
	*flagp |= flags&SPSTART;
	while (*preg->regparse == '|') {
		preg->regparse++;
		br = regbranch(preg, &flags);
		if (br == 0)
			return 0;
		regtail(preg, ret, br);
		if (!(flags&HASWIDTH))
			*flagp &= ~HASWIDTH;
		*flagp |= flags&SPSTART;
	}


	ender = regnode(preg, (paren) ? CLOSE+parno : END);
	regtail(preg, ret, ender);


	for (br = ret; br != 0; br = regnext(preg, br))
		regoptail(preg, br, ender);


	if (paren && *preg->regparse++ != ')') {
		preg->err = REG_ERR_UNMATCHED_PAREN;
		return 0;
	} else if (!paren && *preg->regparse != '\0') {
		if (*preg->regparse == ')') {
			preg->err = REG_ERR_UNMATCHED_PAREN;
			return 0;
		} else {
			preg->err = REG_ERR_JUNK_ON_END;
			return 0;
		}
	}

	return(ret);
}
