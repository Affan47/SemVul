findtags_in_help_init(findtags_state_T *st)
{
    int		i;
    char_u	*s;


    if (st->is_txt)
	STRCPY(st->help_lang, "en");
    else
    {


	i = (int)STRLEN(st->tag_fname);
	if (i > 3 && st->tag_fname[i - 3] == '-')
	    vim_strncpy(st->help_lang, st->tag_fname + i - 2, 2);
	else
	    STRCPY(st->help_lang, "en");
    }


    if (st->help_lang_find != NULL
	    && STRICMP(st->help_lang, st->help_lang_find) != 0)
	return FALSE;


    if ((st->flags & TAG_KEEP_LANG)
	    && st->help_lang_find == NULL
	    && curbuf->b_fname != NULL
	    && (i = (int)STRLEN(curbuf->b_fname)) > 4
	    && curbuf->b_fname[i - 1] == 'x'
	    && curbuf->b_fname[i - 4] == '.'
	    && STRNICMP(curbuf->b_fname + i - 3, st->help_lang, 2) == 0)
	st->help_pri = 0;
    else
    {

	st->help_pri = 1;
	for (s = p_hlg; *s != NUL; ++s)
	{
	    if (STRNICMP(s, st->help_lang, 2) == 0)
		break;
	    ++st->help_pri;
	    if ((s = vim_strchr(s, ',')) == NULL)
		break;
	}
	if (s == NULL || *s == NUL)
	{


	    ++st->help_pri;
	    if (STRICMP(st->help_lang, "en") != 0)
		++st->help_pri;
	}
    }

    return TRUE;
}
