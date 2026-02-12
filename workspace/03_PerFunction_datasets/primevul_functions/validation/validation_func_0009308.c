eval_vars(
    char_u	*src,
    char_u	*srcstart,
    int		*usedlen,
    linenr_T	*lnump,
    char	**errormsg,
    int		*escaped)

{
    int		i;
    char_u	*s;
    char_u	*result;
    char_u	*resultbuf = NULL;
    int		resultlen;
    buf_T	*buf;
    int		valid = VALID_HEAD + VALID_PATH;
    int		spec_idx;
    int		tilde_file = FALSE;
    int		skip_mod = FALSE;
    char_u	strbuf[30];

    *errormsg = NULL;
    if (escaped != NULL)
	*escaped = FALSE;


    spec_idx = find_cmdline_var(src, usedlen);
    if (spec_idx < 0)
    {
	*usedlen = 1;
	return NULL;
    }


    if (src > srcstart && src[-1] == '\\')
    {
	*usedlen = 0;
	STRMOVE(src - 1, src);
	return NULL;
    }


    if (spec_idx == SPEC_CWORD || spec_idx == SPEC_CCWORD
						     || spec_idx == SPEC_CEXPR)
    {
	resultlen = find_ident_under_cursor(&result,
		spec_idx == SPEC_CWORD ? (FIND_IDENT | FIND_STRING)
	      : spec_idx == SPEC_CEXPR ? (FIND_IDENT | FIND_STRING | FIND_EVAL)
	      : FIND_STRING);
	if (resultlen == 0)
	{
	    *errormsg = "";
	    return NULL;
	}
    }


    else
    {
	int off = 0;

	switch (spec_idx)
	{
	case SPEC_PERC:
#ifdef FEAT_EVAL
		if (!in_vim9script() || src[1] != '%')
#endif
		{

		    if (curbuf->b_fname == NULL)
		    {
			result = (char_u *)"";
			valid = 0;
		    }
		    else
		    {
			result = curbuf->b_fname;
			tilde_file = STRCMP(result, "~") == 0;
		    }
		    break;
		}
#ifdef FEAT_EVAL

		off = 1;
#endif

	case SPEC_HASH:
		if (off == 0 ? src[1] == '#' : src[2] == '%')
		{

		    result = arg_all();
		    resultbuf = result;
		    *usedlen = off + 2;
		    if (escaped != NULL)
			*escaped = TRUE;
		    skip_mod = TRUE;
		    break;
		}
		s = src + off + 1;
		if (*s == '<')
		    ++s;
		i = (int)getdigits(&s);
		if (s == src + off + 2 && src[off + 1] == '-')

		    s--;
		*usedlen = (int)(s - src);

		if (src[off + 1] == '<' && i != 0)
		{
		    if (*usedlen < off + 2)
		    {

			*usedlen = off + 1;
			return NULL;
		    }
#ifdef FEAT_EVAL
		    result = list_find_str(get_vim_var_list(VV_OLDFILES),
								     (long)i);
		    if (result == NULL)
		    {
			*errormsg = "";
			return NULL;
		    }
#else
		    *errormsg = _("E809: #< is not available without the +eval feature");
		    return NULL;
#endif
		}
		else
		{
		    if (i == 0 && src[off + 1] == '<' && *usedlen > off + 1)
			*usedlen = off + 1;
		    buf = buflist_findnr(i);
		    if (buf == NULL)
		    {
			*errormsg = _("E194: No alternate file name to substitute for '#'");
			return NULL;
		    }
		    if (lnump != NULL)
			*lnump = ECMD_LAST;
		    if (buf->b_fname == NULL)
		    {
			result = (char_u *)"";
			valid = 0;
		    }
		    else
		    {
			result = buf->b_fname;
			tilde_file = STRCMP(result, "~") == 0;
		    }
		}
		break;

#ifdef FEAT_SEARCHPATH
	case SPEC_CFILE:
		result = file_name_at_cursor(FNAME_MESS|FNAME_HYP, 1L, NULL);
		if (result == NULL)
		{
		    *errormsg = "";
		    return NULL;
		}
		resultbuf = result;
		break;
#endif

	case SPEC_AFILE:
		result = autocmd_fname;
		if (result != NULL && !autocmd_fname_full)
		{


		    autocmd_fname_full = TRUE;
		    result = FullName_save(autocmd_fname, FALSE);
		    vim_free(autocmd_fname);
		    autocmd_fname = result;
		}
		if (result == NULL)
		{
		    *errormsg = _("E495: no autocommand file name to substitute for \"<afile>\"");
		    return NULL;
		}
		result = shorten_fname1(result);
		break;

	case SPEC_ABUF:
		if (autocmd_bufnr <= 0)
		{
		    *errormsg = _("E496: no autocommand buffer number to substitute for \"<abuf>\"");
		    return NULL;
		}
		sprintf((char *)strbuf, "%d", autocmd_bufnr);
		result = strbuf;
		break;

	case SPEC_AMATCH:
		result = autocmd_match;
		if (result == NULL)
		{
		    *errormsg = _("E497: no autocommand match name to substitute for \"<amatch>\"");
		    return NULL;
		}
		break;

	case SPEC_SFILE:
	case SPEC_STACK:
		result = estack_sfile(spec_idx == SPEC_SFILE
						? ESTACK_SFILE : ESTACK_STACK);
		if (result == NULL)
		{
		    *errormsg = spec_idx == SPEC_SFILE
			? _("E498: no :source file name to substitute for \"<sfile>\"")
			: _("E489: no call stack to substitute for \"<stack>\"");
		    return NULL;
		}
		resultbuf = result;
		break;

	case SPEC_SLNUM:
		if (SOURCING_NAME == NULL || SOURCING_LNUM == 0)
		{
		    *errormsg = _("E842: no line number to use for \"<slnum>\"");
		    return NULL;
		}
		sprintf((char *)strbuf, "%ld", SOURCING_LNUM);
		result = strbuf;
		break;

#ifdef FEAT_EVAL
	case SPEC_SFLNUM:
		if (current_sctx.sc_lnum + SOURCING_LNUM == 0)
		{
		    *errormsg = _("E961: no line number to use for \"<sflnum>\"");
		    return NULL;
		}
		sprintf((char *)strbuf, "%ld",
				 (long)(current_sctx.sc_lnum + SOURCING_LNUM));
		result = strbuf;
		break;

	case SPEC_SID:
		if (current_sctx.sc_sid <= 0)
		{
		    *errormsg = _(e_usingsid);
		    return NULL;
		}
		sprintf((char *)strbuf, "<SNR>%d_", current_sctx.sc_sid);
		result = strbuf;
		break;
#endif

#ifdef FEAT_CLIENTSERVER
	case SPEC_CLIENT:
		sprintf((char *)strbuf, PRINTF_HEX_LONG_U,
							(long_u)clientWindow);
		result = strbuf;
		break;
#endif

	default:
		result = (char_u *)"";
		break;
	}

	resultlen = (int)STRLEN(result);
	if (src[*usedlen] == '<')
	{
	    ++*usedlen;
	    if ((s = vim_strrchr(result, '.')) != NULL && s >= gettail(result))
		resultlen = (int)(s - result);
	}
	else if (!skip_mod)
	{
	    valid |= modify_fname(src, tilde_file, usedlen, &result, &resultbuf,
								  &resultlen);
	    if (result == NULL)
	    {
		*errormsg = "";
		return NULL;
	    }
	}
    }

    if (resultlen == 0 || valid != VALID_HEAD + VALID_PATH)
    {
	if (valid != VALID_HEAD + VALID_PATH)

	    *errormsg = _("E499: Empty file name for '%' or '#', only works with \":p:h\"");
	else
	    *errormsg = _("E500: Evaluates to an empty string");
	result = NULL;
    }
    else
	result = vim_strnsave(result, resultlen);
    vim_free(resultbuf);
    return result;
}
