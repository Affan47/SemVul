reg( int paren, int *flagp )
{
	char* ret = 0;
	char* br;
	char* ender;
	int parno = 0;
	int flags;

	*flagp = HASWIDTH;

	if (paren)
	{

		if (regnpar >= Regexp::NSUBEXP)
		{
			regerror(REGERR_TO_MANY_PAREN);
			return NULL;
		}
		parno = regnpar;
		regnpar++;
		ret = regnode(OPEN+parno);
	}


	br = regbranch(&flags);
	if (br == NULL)
		return(NULL);
	if (paren)
		regtail(ret, br);
	else
		ret = br;
	*flagp &= ~(~flags&HASWIDTH);
	*flagp |= flags&SPSTART;
	while (*regparse == '|')
	{
		regparse++;
		br = regbranch(&flags);
		if (br == NULL)
			return(NULL);
		regtail(ret, br);
		*flagp &= ~(~flags&HASWIDTH);
		*flagp |= flags&SPSTART;
	}


	ender = regnode((paren) ? CLOSE+parno : END);
	regtail(ret, ender);


	for (br = ret; br != NULL; br = regnext(br))
		regoptail(br, ender);


	if (paren && *regparse++ != ')')
	{
		regerror( REGERR_UNTERMINATED_PAREN );
		return NULL;
	}
	else if (!paren && *regparse != '\0')
	{
		if (*regparse == ')')
		{
			regerror( REGERR_UNMATCHED_PAREN );
			return NULL;
		}
		else
		{
			regerror( REGERR_INTERNAL_ERROR_JUNK );
			return NULL;
		}

	}

	return(ret);
}
