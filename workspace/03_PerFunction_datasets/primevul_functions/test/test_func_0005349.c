check_linecomment(char_u *line)
{
    char_u  *p;

    p = line;

    if (curbuf->b_p_lisp)
    {
	if (vim_strchr(p, ';') != NULL)
	{
	    int in_str = FALSE;

	    p = line;
	    while ((p = vim_strpbrk(p, (char_u *)"\";")) != NULL)
	    {
		if (*p == '"')
		{
		    if (in_str)
		    {
			if (*(p - 1) != '\\')
			    in_str = FALSE;
		    }
		    else if (p == line || ((p - line) >= 2

				      && *(p - 1) != '\\' && *(p - 2) != '#'))
			in_str = TRUE;
		}
		else if (!in_str && ((p - line) < 2
				    || (*(p - 1) != '\\' && *(p - 2) != '#'))
			       && !is_pos_in_string(line, (colnr_T)(p - line)))
		    break;
		++p;
	    }
	}
	else
	    p = NULL;
    }
    else
	while ((p = vim_strchr(p, '/')) != NULL)
	{


	    if (p[1] == '/' && (p == line || p[-1] != '*' || p[2] != '*')
			       && !is_pos_in_string(line, (colnr_T)(p - line)))
		break;
	    ++p;
	}

    if (p == NULL)
	return MAXCOL;
    return (int)(p - line);
}
