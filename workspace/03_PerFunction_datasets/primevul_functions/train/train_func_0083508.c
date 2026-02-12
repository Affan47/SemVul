find_help_tags(
    char_u	*arg,
    int		*num_matches,
    char_u	***matches,
    int		keep_lang)
{
    char_u	*s, *d;
    int		i;

    static char *(except_tbl[][2]) = {
	{"*",		"star"},
	{"g*",		"gstar"},
	{"[*",		"[star"},
	{"]*",		"]star"},
	{":*",		":star"},
	{"/*",		"/star"},
	{"/\\*",	"/\\\\star"},
	{"\"*",		"quotestar"},
	{"**",		"starstar"},
	{"cpo-*",	"cpo-star"},
	{"/\\(\\)",	"/\\\\(\\\\)"},
	{"/\\%(\\)",	"/\\\\%(\\\\)"},
	{"?",		"?"},
	{"??",		"??"},
	{":?",		":?"},
	{"?<CR>",	"?<CR>"},
	{"g?",		"g?"},
	{"g?g?",	"g?g?"},
	{"g??",		"g??"},
	{"-?",		"-?"},
	{"q?",		"q?"},
	{"v_g?",	"v_g?"},
	{"/\\?",	"/\\\\?"},
	{"/\\z(\\)",	"/\\\\z(\\\\)"},
	{"\\=",		"\\\\="},
	{":s\\=",	":s\\\\="},
	{"[count]",	"\\[count]"},
	{"[quotex]",	"\\[quotex]"},
	{"[range]",	"\\[range]"},
	{":[range]",	":\\[range]"},
	{"[pattern]",	"\\[pattern]"},
	{"\\|",		"\\\\bar"},
	{"\\%$",	"/\\\\%\\$"},
	{"s/\\~",	"s/\\\\\\~"},
	{"s/\\U",	"s/\\\\U"},
	{"s/\\L",	"s/\\\\L"},
	{"s/\\1",	"s/\\\\1"},
	{"s/\\2",	"s/\\\\2"},
	{"s/\\3",	"s/\\\\3"},
	{"s/\\9",	"s/\\\\9"},
	{NULL, NULL}
    };
    static char *(expr_table[]) = {"!=?", "!~?", "<=?", "<?", "==?", "=~?",
				   ">=?", ">?", "is?", "isnot?"};
    int flags;

    d = IObuff;
    d[0] = NUL;

    if (STRNICMP(arg, "expr-", 5) == 0)
    {

	for (i = (int)ARRAY_LENGTH(expr_table); --i >= 0; )
	    if (STRCMP(arg + 5, expr_table[i]) == 0)
	    {
		int si = 0, di = 0;

		for (;;)
		{
		    if (arg[si] == '~')
			d[di++] = '\\';
		    d[di++] = arg[si];
		    if (arg[si] == NUL)
			break;
		    ++si;
		}
		break;
	    }
    }
    else
    {

	for (i = 0; except_tbl[i][0] != NULL; ++i)
	    if (STRCMP(arg, except_tbl[i][0]) == 0)
	    {
		STRCPY(d, except_tbl[i][1]);
		break;
	    }
    }

    if (d[0] == NUL)
    {

	if (arg[0] == '\\'
		&& ((arg[1] != NUL && arg[2] == NUL)
		    || (vim_strchr((char_u *)"%_z@", arg[1]) != NULL
							   && arg[2] != NUL)))
	{
	    STRCPY(d, "/\\\\");
	    STRCPY(d + 3, arg + 1);

	    if (d[3] == '_' && d[4] == '$')
		STRCPY(d + 4, "\\$");
	}
	else
	{

	    if ((arg[0] == '[' && (arg[1] == ':'
			 || (arg[1] == '+' && arg[2] == '+')))
		    || (arg[0] == '\\' && arg[1] == '{'))
	      *d++ = '\\';

	  if (*arg == '(' && arg[1] == '\'')
	      arg++;
	  for (s = arg; *s; ++s)
	  {

	    if (d - IObuff > IOSIZE - 10)
		break;
	    switch (*s)
	    {
		case '|':   STRCPY(d, "bar");
			    d += 3;
			    continue;
		case '"':   STRCPY(d, "quote");
			    d += 5;
			    continue;
		case '*':   *d++ = '.';
			    break;
		case '?':   *d++ = '.';
			    continue;
		case '$':
		case '.':
		case '~':   *d++ = '\\';
			    break;
	    }

	    if (*s < ' ' || (*s == '^' && s[1] && (ASCII_ISALPHA(s[1])
			   || vim_strchr((char_u *)"?@[\\]^", s[1]) != NULL)))
	    {
		if (d > IObuff && d[-1] != '_' && d[-1] != '\\')
		    *d++ = '_';
		STRCPY(d, "CTRL-");
		d += 5;
		if (*s < ' ')
		{
#ifdef EBCDIC
		    *d++ = CtrlChar(*s);
#else
		    *d++ = *s + '@';
#endif
		    if (d[-1] == '\\')
			*d++ = '\\';
		}
		else
		    *d++ = *++s;
		if (s[1] != NUL && s[1] != '_')
		    *d++ = '_';
		continue;
	    }
	    else if (*s == '^')
		*d++ = '\\';

	    else if (s[0] == '\\' && s[1] != '\\'
					       && *arg == '/' && s == arg + 1)
		*d++ = '\\';

	    if (STRNICMP(s, "CTRL-\\_", 7) == 0)
	    {
		STRCPY(d, "CTRL-\\\\");
		d += 7;
		s += 6;
	    }

	    *d++ = *s;

	    if (*s == '(' && (s[1] == '{' || s[1] =='['))
		break;

	    if (*s == '\'' && s > arg && *arg == '\'')
		break;

	    if (*s == '}' && s > arg && *arg == '{')
		break;
	  }
	  *d = NUL;

	  if (*IObuff == '`')
	  {
	      if (d > IObuff + 2 && d[-1] == '`')
	      {

		  mch_memmove(IObuff, IObuff + 1, STRLEN(IObuff));
		  d[-2] = NUL;
	      }
	      else if (d > IObuff + 3 && d[-2] == '`' && d[-1] == ',')
	      {

		  mch_memmove(IObuff, IObuff + 1, STRLEN(IObuff));
		  d[-3] = NUL;
	      }
	      else if (d > IObuff + 4 && d[-3] == '`'
					     && d[-2] == '\\' && d[-1] == '.')
	      {

		  mch_memmove(IObuff, IObuff + 1, STRLEN(IObuff));
		  d[-4] = NUL;
	      }
	  }
	}
    }

    *matches = (char_u **)"";
    *num_matches = 0;
    flags = TAG_HELP | TAG_REGEXP | TAG_NAMES | TAG_VERBOSE | TAG_NO_TAGFUNC;
    if (keep_lang)
	flags |= TAG_KEEP_LANG;
    if (find_tags(IObuff, num_matches, matches, flags, (int)MAXCOL, NULL) == OK
	    && *num_matches > 0)
    {

	qsort((void *)*matches, (size_t)*num_matches,
					      sizeof(char_u *), help_compare);

	while (*num_matches > TAG_MANY)
	    vim_free((*matches)[--*num_matches]);
    }
    return OK;
}
}
}
