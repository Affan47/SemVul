linelen(int *has_tab)
{
    char_u  *line;
    char_u  *first;
    char_u  *last;
    int	    save;
    int	    len;


    line = ml_get_curline();
    if (*line == NUL)
	return 0;


    first = skipwhite(line);


    for (last = first + STRLEN(first);
				last > first && VIM_ISWHITE(last[-1]); --last)
	;
    save = *last;
    *last = NUL;
    len = linetabsize(line);
    if (has_tab != NULL)
	*has_tab = (vim_strchr(first, TAB) != NULL);
    *last = save;

    return len;
}
