cin_is_cpp_baseclass(
    cpp_baseclass_cache_T *cached)
{
    lpos_T	*pos = &cached->lpos;
    char_u	*s;
    int		class_or_struct, lookfor_ctor_init, cpp_base_class;
    linenr_T	lnum = curwin->w_cursor.lnum;
    char_u	*line = ml_get_curline();

    if (pos->lnum <= lnum)
	return cached->found;

    pos->col = 0;

    s = skipwhite(line);
    if (*s == '#')
	return FALSE;
    s = cin_skipcomment(s);
    if (*s == NUL)
	return FALSE;

    cpp_base_class = lookfor_ctor_init = class_or_struct = FALSE;


    while (lnum > 1)
    {
	line = ml_get(lnum - 1);
	s = skipwhite(line);
	if (*s == '#' || *s == NUL)
	    break;
	while (*s != NUL)
	{
	    s = cin_skipcomment(s);
	    if (*s == '{' || *s == '}'
		    || (*s == ';' && cin_nocode(s + 1)))
		break;
	    if (*s != NUL)
		++s;
	}
	if (*s != NUL)
	    break;
	--lnum;
    }

    pos->lnum = lnum;
    line = ml_get(lnum);
    s = line;
    for (;;)
    {
	if (*s == NUL)
	{
	    if (lnum == curwin->w_cursor.lnum)
		break;

	    line = ml_get(++lnum);
	    s = line;
	}
	if (s == line)
	{

	    if (cin_iscase(s, FALSE))
		break;
	    s = cin_skipcomment(line);
	    if (*s == NUL)
		continue;
	}

	if (s[0] == '"' || (s[0] == 'R' && s[1] == '"'))
	    s = skip_string(s) + 1;
	else if (s[0] == ':')
	{
	    if (s[1] == ':')
	    {


		lookfor_ctor_init = FALSE;
		s = cin_skipcomment(s + 2);
	    }
	    else if (lookfor_ctor_init || class_or_struct)
	    {


		cpp_base_class = TRUE;
		lookfor_ctor_init = class_or_struct = FALSE;
		pos->col = 0;
		s = cin_skipcomment(s + 1);
	    }
	    else
		s = cin_skipcomment(s + 1);
	}
	else if ((STRNCMP(s, "class", 5) == 0 && !vim_isIDc(s[5]))
		|| (STRNCMP(s, "struct", 6) == 0 && !vim_isIDc(s[6])))
	{
	    class_or_struct = TRUE;
	    lookfor_ctor_init = FALSE;

	    if (*s == 'c')
		s = cin_skipcomment(s + 5);
	    else
		s = cin_skipcomment(s + 6);
	}
	else
	{
	    if (s[0] == '{' || s[0] == '}' || s[0] == ';')
	    {
		cpp_base_class = lookfor_ctor_init = class_or_struct = FALSE;
	    }
	    else if (s[0] == ')')
	    {


		class_or_struct = FALSE;
		lookfor_ctor_init = TRUE;
	    }
	    else if (s[0] == '?')
	    {

		return FALSE;
	    }
	    else if (!vim_isIDc(s[0]))
	    {

		class_or_struct = FALSE;
		lookfor_ctor_init = FALSE;
	    }
	    else if (pos->col == 0)
	    {

		lookfor_ctor_init = FALSE;


		if (cpp_base_class)
		    pos->col = (colnr_T)(s - line);
	    }


	    if (lnum == curwin->w_cursor.lnum && *s == ',' && cin_nocode(s + 1))
		pos->col = 0;

	    s = cin_skipcomment(s + 1);
	}
    }

    cached->found = cpp_base_class;
    if (cpp_base_class)
	pos->lnum = lnum;
    return cpp_base_class;
}
