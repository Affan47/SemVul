add_termcode(char_u *name, char_u *string, int flags)
{
    struct termcode *new_tc;
    int		    i, j;
    char_u	    *s;
    int		    len;

    if (string == NULL || *string == NUL)
    {
	del_termcode(name);
	return;
    }

#if defined(MSWIN) && !defined(FEAT_GUI)
    s = vim_strnsave(string, STRLEN(string) + 1);
#else
# ifdef VIMDLL
    if (!gui.in_use)
	s = vim_strnsave(string, STRLEN(string) + 1);
    else
# endif
	s = vim_strsave(string);
#endif
    if (s == NULL)
	return;


    if (flags != 0 && flags != ATC_FROM_TERM && term_7to8bit(string) != 0)
    {
	STRMOVE(s, s + 1);
	s[0] = term_7to8bit(string);
    }

#if defined(MSWIN) && (!defined(FEAT_GUI) || defined(VIMDLL))
# ifdef VIMDLL
    if (!gui.in_use)
# endif
    {
	if (s[0] == K_NUL)
	{
	    STRMOVE(s + 1, s);
	    s[1] = 3;
	}
    }
#endif

    len = (int)STRLEN(s);

    need_gather = TRUE;


    if (tc_len == tc_max_len)
    {
	tc_max_len += 20;
	new_tc = ALLOC_MULT(struct termcode, tc_max_len);
	if (new_tc == NULL)
	{
	    tc_max_len -= 20;
	    vim_free(s);
	    return;
	}
	for (i = 0; i < tc_len; ++i)
	    new_tc[i] = termcodes[i];
	vim_free(termcodes);
	termcodes = new_tc;
    }


    for (i = 0; i < tc_len; ++i)
    {
	if (termcodes[i].name[0] < name[0])
	    continue;
	if (termcodes[i].name[0] == name[0])
	{
	    if (termcodes[i].name[1] < name[1])
		continue;


	    if (termcodes[i].name[1] == name[1])
	    {
		if (flags == ATC_FROM_TERM && (j = termcode_star(
				    termcodes[i].code, termcodes[i].len)) > 0)
		{


		    if (len == termcodes[i].len - j
			    && STRNCMP(s, termcodes[i].code, len - 1) == 0
			    && s[len - 1]
				   == termcodes[i].code[termcodes[i].len - 1])
		    {

			vim_free(s);
			return;
		    }
		}
		else
		{

		    vim_free(termcodes[i].code);
		    --tc_len;
		    break;
		}
	    }
	}


	for (j = tc_len; j > i; --j)
	    termcodes[j] = termcodes[j - 1];
	break;
    }

    termcodes[i].name[0] = name[0];
    termcodes[i].name[1] = name[1];
    termcodes[i].code = s;
    termcodes[i].len = len;


    termcodes[i].modlen = 0;
    j = termcode_star(s, len);
    if (j > 0)
    {
	termcodes[i].modlen = len - 1 - j;

	if (termcodes[i].code[termcodes[i].modlen - 1] == '@')
	    --termcodes[i].modlen;
    }
    ++tc_len;
}
