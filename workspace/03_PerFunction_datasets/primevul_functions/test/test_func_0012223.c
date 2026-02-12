regpiece(int *flagp)
{
    char_u	    *ret;
    int		    op;
    char_u	    *next;
    int		    flags;
    long	    minval;
    long	    maxval;

    ret = regatom(&flags);
    if (ret == NULL)
	return NULL;

    op = peekchr();
    if (re_multi_type(op) == NOT_MULTI)
    {
	*flagp = flags;
	return ret;
    }

    *flagp = (WORST | SPSTART | (flags & (HASNL | HASLOOKBH)));

    skipchr();
    switch (op)
    {
	case Magic('*'):
	    if (flags & SIMPLE)
		reginsert(STAR, ret);
	    else
	    {

		reginsert(BRANCH, ret);
		regoptail(ret, regnode(BACK));
		regoptail(ret, ret);
		regtail(ret, regnode(BRANCH));
		regtail(ret, regnode(NOTHING));
	    }
	    break;

	case Magic('+'):
	    if (flags & SIMPLE)
		reginsert(PLUS, ret);
	    else
	    {

		next = regnode(BRANCH);
		regtail(ret, next);
		regtail(regnode(BACK), ret);
		regtail(next, regnode(BRANCH));
		regtail(ret, regnode(NOTHING));
	    }
	    *flagp = (WORST | HASWIDTH | (flags & (HASNL | HASLOOKBH)));
	    break;

	case Magic('@'):
	    {
		int	lop = END;
		long	nr;

		nr = getdecchrs();
		switch (no_Magic(getchr()))
		{
		    case '=': lop = MATCH; break;
		    case '!': lop = NOMATCH; break;
		    case '>': lop = SUBPAT; break;
		    case '<': switch (no_Magic(getchr()))
			      {
				  case '=': lop = BEHIND; break;
				  case '!': lop = NOBEHIND; break;
			      }
		}
		if (lop == END)
		    EMSG2_RET_NULL(_(e_invalid_character_after_str_at),
						      reg_magic == MAGIC_ALL);

		if (lop == BEHIND || lop == NOBEHIND)
		{
		    regtail(ret, regnode(BHPOS));
		    *flagp |= HASLOOKBH;
		}
		regtail(ret, regnode(END));
		if (lop == BEHIND || lop == NOBEHIND)
		{
		    if (nr < 0)
			nr = 0;
		    reginsert_nr(lop, nr, ret);
		}
		else
		    reginsert(lop, ret);
		break;
	    }

	case Magic('?'):
	case Magic('='):

	    reginsert(BRANCH, ret);
	    regtail(ret, regnode(BRANCH));
	    next = regnode(NOTHING);
	    regtail(ret, next);
	    regoptail(ret, next);
	    break;

	case Magic('{'):
	    if (!read_limits(&minval, &maxval))
		return NULL;
	    if (flags & SIMPLE)
	    {
		reginsert(BRACE_SIMPLE, ret);
		reginsert_limits(BRACE_LIMITS, minval, maxval, ret);
	    }
	    else
	    {
		if (num_complex_braces >= 10)
		    EMSG2_RET_NULL(_(e_too_many_complex_str_curly),
						      reg_magic == MAGIC_ALL);
		reginsert(BRACE_COMPLEX + num_complex_braces, ret);
		regoptail(ret, regnode(BACK));
		regoptail(ret, ret);
		reginsert_limits(BRACE_LIMITS, minval, maxval, ret);
		++num_complex_braces;
	    }
	    if (minval > 0 && maxval > 0)
		*flagp = (HASWIDTH | (flags & (HASNL | HASLOOKBH)));
	    break;
    }
    if (re_multi_type(peekchr()) != NOT_MULTI)
    {

	if (peekchr() == Magic('*'))
	    EMSG2_RET_NULL(_(e_nested_str), reg_magic >= MAGIC_ON);
	EMSG3_RET_NULL(_(e_nested_str_chr), reg_magic == MAGIC_ALL,
							  no_Magic(peekchr()));
    }

    return ret;
}
}
