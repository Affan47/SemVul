peekchr(void)
{
    static int	after_slash = FALSE;

    if (curchr == -1)
    {
	switch (curchr = regparse[0])
	{
	case '.':
	case '[':
	case '~':

	    if (reg_magic >= MAGIC_ON)
		curchr = Magic(curchr);
	    break;
	case '(':
	case ')':
	case '{':
	case '%':
	case '+':
	case '=':
	case '?':
	case '@':
	case '!':
	case '&':
	case '|':
	case '<':
	case '>':
	case '#':
	case '"':
	case '\'':
	case ',':
	case '-':
	case ':':
	case ';':
	case '`':
	case '/':

	    if (reg_magic == MAGIC_ALL)
		curchr = Magic(curchr);
	    break;
	case '*':

	    if (reg_magic >= MAGIC_ON
		    && !at_start
		    && !(prev_at_start && prevchr == Magic('^'))
		    && (after_slash
			|| (prevchr != Magic('(')
			    && prevchr != Magic('&')
			    && prevchr != Magic('|'))))
		curchr = Magic('*');
	    break;
	case '^':

	    if (reg_magic >= MAGIC_OFF
		    && (at_start
			|| reg_magic == MAGIC_ALL
			|| prevchr == Magic('(')
			|| prevchr == Magic('|')
			|| prevchr == Magic('&')
			|| prevchr == Magic('n')
			|| (no_Magic(prevchr) == '('
			    && prevprevchr == Magic('%'))))
	    {
		curchr = Magic('^');
		at_start = TRUE;
		prev_at_start = FALSE;
	    }
	    break;
	case '$':

	    if (reg_magic >= MAGIC_OFF)
	    {
		char_u *p = regparse + 1;
		int is_magic_all = (reg_magic == MAGIC_ALL);

		while (p[0] == '\\' && (p[1] == 'c' || p[1] == 'C'
				|| p[1] == 'm' || p[1] == 'M'
				|| p[1] == 'v' || p[1] == 'V' || p[1] == 'Z'))
		{
		    if (p[1] == 'v')
			is_magic_all = TRUE;
		    else if (p[1] == 'm' || p[1] == 'M' || p[1] == 'V')
			is_magic_all = FALSE;
		    p += 2;
		}
		if (p[0] == NUL
			|| (p[0] == '\\'
			    && (p[1] == '|' || p[1] == '&' || p[1] == ')'
				|| p[1] == 'n'))
			|| (is_magic_all
			       && (p[0] == '|' || p[0] == '&' || p[0] == ')'))
			|| reg_magic == MAGIC_ALL)
		    curchr = Magic('$');
	    }
	    break;
	case '\\':
	    {
		int c = regparse[1];

		if (c == NUL)
		    curchr = '\\';
		else if (
#ifdef EBCDIC
			vim_strchr(META, c)
#else
			c <= '~' && META_flags[c]
#endif
			)
		{

		    curchr = -1;
		    prev_at_start = at_start;
		    at_start = FALSE;
		    ++regparse;
		    ++after_slash;
		    peekchr();
		    --regparse;
		    --after_slash;
		    curchr = toggle_Magic(curchr);
		}
		else if (vim_strchr(REGEXP_ABBR, c))
		{

		    curchr = backslash_trans(c);
		}
		else if (reg_magic == MAGIC_NONE && (c == '$' || c == '^'))
		    curchr = toggle_Magic(c);
		else
		{

		    if (has_mbyte)
			curchr = (*mb_ptr2char)(regparse + 1);
		    else
			curchr = c;
		}
		break;
	    }

	default:
	    if (has_mbyte)
		curchr = (*mb_ptr2char)(regparse);
	}
    }

    return curchr;
}
}
