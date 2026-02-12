p_b_term(p, cs)
register struct parse *p;
register cset *cs;
{
	register char c;
	register char start, finish;
	register int i;


	switch ((MORE()) ? PEEK() : '\0') {
	case '[':
		c = (MORE2()) ? PEEK2() : '\0';
		break;
	case '-':
		SETERROR(REG_ERANGE);
		return;
	default:
		c = '\0';
		break;
	}

	switch (c) {
	case ':':
		NEXT2();
		if(REQUIRE(MORE(), REG_EBRACK)) {}
		c = PEEK();
		if(REQUIRE(c != '-' && c != ']', REG_ECTYPE)) {}
		p_b_cclass(p, cs);
		if(REQUIRE(MORE(), REG_EBRACK)) {}
		if(REQUIRE(EATTWO(':', ']'), REG_ECTYPE)) {}
		break;
	case '=':
		NEXT2();
		if(REQUIRE(MORE(), REG_EBRACK)) {}
		c = PEEK();
		if(REQUIRE(c != '-' && c != ']', REG_ECOLLATE)) {}
		p_b_eclass(p, cs);
		if(REQUIRE(MORE(), REG_EBRACK)) {}
		if(REQUIRE(EATTWO('=', ']'), REG_ECOLLATE)) {}
		break;
	default:

		start = p_b_symbol(p);
		if (SEE('-') && MORE2() && PEEK2() != ']') {

			NEXT();
			if (EAT('-'))
				finish = '-';
			else
				finish = p_b_symbol(p);
		} else
			finish = start;

		if(REQUIRE(start <= finish, REG_ERANGE)) {}
		for (i = start; i <= finish; i++)
			CHadd(cs, i);
		break;
	}
}
