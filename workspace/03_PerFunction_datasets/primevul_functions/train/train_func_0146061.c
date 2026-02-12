cin_islabel(void)
{
    char_u	*s;

    s = cin_skipcomment(ml_get_curline());


    if (cin_isdefault(s))
	return FALSE;
    if (cin_isscopedecl(s))
	return FALSE;

    if (cin_islabel_skip(&s))
    {


	pos_T	cursor_save;
	pos_T	*trypos;
	char_u	*line;

	cursor_save = curwin->w_cursor;
	while (curwin->w_cursor.lnum > 1)
	{
	    --curwin->w_cursor.lnum;


	    curwin->w_cursor.col = 0;
	    if ((trypos = ind_find_start_CORS(NULL)) != NULL)
		curwin->w_cursor = *trypos;

	    line = ml_get_curline();
	    if (cin_ispreproc(line))
		continue;
	    if (*(line = cin_skipcomment(line)) == NUL)
		continue;

	    curwin->w_cursor = cursor_save;
	    if (cin_isterminated(line, TRUE, FALSE)
		    || cin_isscopedecl(line)
		    || cin_iscase(line, TRUE)
		    || (cin_islabel_skip(&line) && cin_nocode(line)))
		return TRUE;
	    return FALSE;
	}
	curwin->w_cursor = cursor_save;
	return TRUE;
    }
    return FALSE;
}
