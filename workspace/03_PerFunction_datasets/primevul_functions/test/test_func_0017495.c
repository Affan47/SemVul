replace_termcodes(
    char_u	*from,
    char_u	**bufp,
    int		flags,
    int		*did_simplify)
{
    int		i;
    int		slen;
    int		key;
    size_t	dlen = 0;
    char_u	*src;
    int		do_backslash;
    int		do_special;
    int		do_key_code;
    char_u	*result;
    garray_T	ga;

    do_backslash = (vim_strchr(p_cpo, CPO_BSLASH) == NULL);
    do_special = (vim_strchr(p_cpo, CPO_SPECI) == NULL)
						  || (flags & REPTERM_SPECIAL);
    do_key_code = (vim_strchr(p_cpo, CPO_KEYCODE) == NULL);
    src = from;


    ga_init2(&ga, 1L, 100);
    if (ga_grow(&ga, (int)(STRLEN(src) * 6 + 1)) == FAIL)
    {
	*bufp = NULL;
	return from;
    }
    result = ga.ga_data;


    if ((flags & REPTERM_FROM_PART) && src[0] == '#' && VIM_ISDIGIT(src[1]))
    {
	result[dlen++] = K_SPECIAL;
	result[dlen++] = 'k';
	if (src[1] == '0')
	    result[dlen++] = ';';
	else
	    result[dlen++] = src[1];
	src += 2;
    }


    while (*src != NUL)
    {


	if (do_special && ((flags & REPTERM_DO_LT)
					      || STRNCMP(src, "<lt>", 4) != 0))
	{
#ifdef FEAT_EVAL


	    if (STRNICMP(src, "<SID>", 5) == 0)
	    {
		if (current_sctx.sc_sid <= 0)
		    emsg(_(e_using_sid_not_in_script_context));
		else
		{
		    char_u  *dot;
		    long    sid = current_sctx.sc_sid;

		    src += 5;
		    if (in_vim9script()
				       && (dot = vim_strchr(src, '.')) != NULL)
		    {
			imported_T *imp = find_imported(src, dot - src, FALSE);

			if (imp != NULL)
			{
			    scriptitem_T    *si = SCRIPT_ITEM(imp->imp_sid);
			    size_t	    len;

			    src = dot + 1;
			    if (si->sn_autoload_prefix != NULL)
			    {


				len = STRLEN(si->sn_autoload_prefix);
				if (ga_grow(&ga,
				     (int)(STRLEN(src) * 6 + len + 1)) == FAIL)
				{
				    ga_clear(&ga);
				    *bufp = NULL;
				    return from;
				}
				result = ga.ga_data;
				STRCPY(result + dlen, si->sn_autoload_prefix);
				dlen += len;
				continue;
			    }
			    sid = imp->imp_sid;
			}
		    }

		    result[dlen++] = K_SPECIAL;
		    result[dlen++] = (int)KS_EXTRA;
		    result[dlen++] = (int)KE_SNR;
		    sprintf((char *)result + dlen, "%ld", sid);
		    dlen += STRLEN(result + dlen);
		    result[dlen++] = '_';
		    continue;
		}
	    }
#endif
	    slen = trans_special(&src, result + dlen, FSK_KEYCODE
			  | ((flags & REPTERM_NO_SIMPLIFY) ? 0 : FSK_SIMPLIFY),
							   TRUE, did_simplify);
	    if (slen)
	    {
		dlen += slen;
		continue;
	    }
	}


	if (do_key_code)
	{
	    i = find_term_bykeys(src);
	    if (i >= 0)
	    {
		result[dlen++] = K_SPECIAL;
		result[dlen++] = termcodes[i].name[0];
		result[dlen++] = termcodes[i].name[1];
		src += termcodes[i].len;

		continue;
	    }
	}

#ifdef FEAT_EVAL
	if (do_special)
	{
	    char_u	*p, *s, len;


	    if (STRNICMP(src, "<Leader>", 8) == 0)
	    {
		len = 8;
		p = get_var_value((char_u *)"g:mapleader");
	    }
	    else if (STRNICMP(src, "<LocalLeader>", 13) == 0)
	    {
		len = 13;
		p = get_var_value((char_u *)"g:maplocalleader");
	    }
	    else
	    {
		len = 0;
		p = NULL;
	    }
	    if (len != 0)
	    {

		if (p == NULL || *p == NUL || STRLEN(p) > 8 * 6)
		    s = (char_u *)"\\";
		else
		    s = p;
		while (*s != NUL)
		    result[dlen++] = *s++;
		src += len;
		continue;
	    }
	}
#endif


	key = *src;
	if (key == Ctrl_V || (do_backslash && key == '\\'))
	{
	    ++src;
	    if (*src == NUL)
	    {
		if (flags & REPTERM_FROM_PART)
		    result[dlen++] = key;
		break;
	    }
	}


	for (i = (*mb_ptr2len)(src); i > 0; --i)
	{


	    if (*src == K_SPECIAL)
	    {
		result[dlen++] = K_SPECIAL;
		result[dlen++] = KS_SPECIAL;
		result[dlen++] = KE_FILLER;
	    }
# ifdef FEAT_GUI
	    else if (*src == CSI)
	    {
		result[dlen++] = K_SPECIAL;
		result[dlen++] = KS_EXTRA;
		result[dlen++] = (int)KE_CSI;
	    }
# endif
	    else
		result[dlen++] = *src;
	    ++src;
	}
    }
    result[dlen] = NUL;


    if ((*bufp = vim_strsave(result)) != NULL)
	from = *bufp;
    vim_free(result);
    return from;
}
