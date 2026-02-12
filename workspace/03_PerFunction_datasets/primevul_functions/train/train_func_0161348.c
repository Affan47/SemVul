compile_call(
	char_u	    **arg,
	size_t	    varlen,
	cctx_T	    *cctx,
	ppconst_T   *ppconst,
	int	    argcount_init)
{
    char_u	*name = *arg;
    char_u	*p;
    int		argcount = argcount_init;
    char_u	namebuf[100];
    char_u	fname_buf[FLEN_FIXED + 1];
    char_u	*tofree = NULL;
    int		error = FCERR_NONE;
    ufunc_T	*ufunc = NULL;
    int		res = FAIL;
    int		is_autoload;
    int		is_searchpair;


    if ((varlen == 3 && STRNCMP(*arg, "has", 3) == 0)
	    || (varlen == 15 && STRNCMP(*arg, "exists_compiled", 6) == 0))
    {
	char_u	    *s = skipwhite(*arg + varlen + 1);
	typval_T    argvars[2];
	int	    is_has = **arg == 'h';

	argvars[0].v_type = VAR_UNKNOWN;
	if (*s == '"')
	    (void)eval_string(&s, &argvars[0], TRUE);
	else if (*s == '\'')
	    (void)eval_lit_string(&s, &argvars[0], TRUE);
	s = skipwhite(s);
	if (*s == ')' && argvars[0].v_type == VAR_STRING
	       && ((is_has && !dynamic_feature(argvars[0].vval.v_string))
		    || !is_has))
	{
	    typval_T	*tv = &ppconst->pp_tv[ppconst->pp_used];

	    *arg = s + 1;
	    argvars[1].v_type = VAR_UNKNOWN;
	    tv->v_type = VAR_NUMBER;
	    tv->vval.v_number = 0;
	    if (is_has)
		f_has(argvars, tv);
	    else
		f_exists(argvars, tv);
	    clear_tv(&argvars[0]);
	    ++ppconst->pp_used;
	    return OK;
	}
	clear_tv(&argvars[0]);
	if (!is_has)
	{
	    emsg(_(e_argument_of_exists_compiled_must_be_literal_string));
	    return FAIL;
	}
    }

    if (generate_ppconst(cctx, ppconst) == FAIL)
	return FAIL;

    if (varlen >= sizeof(namebuf))
    {
	semsg(_(e_name_too_long_str), name);
	return FAIL;
    }
    vim_strncpy(namebuf, *arg, varlen);
    name = fname_trans_sid(namebuf, fname_buf, &tofree, &error);


    is_searchpair = (varlen == 6 && STRNCMP(*arg, "search", 6) == 0)
	         || (varlen == 9 && STRNCMP(*arg, "searchpos", 9) == 0)
	        || (varlen == 10 && STRNCMP(*arg, "searchpair", 10) == 0)
	        || (varlen == 13 && STRNCMP(*arg, "searchpairpos", 13) == 0);

    *arg = skipwhite(*arg + varlen + 1);
    if (compile_arguments(arg, cctx, &argcount, is_searchpair) == FAIL)
	goto theend;

    is_autoload = vim_strchr(name, AUTOLOAD_CHAR) != NULL;
    if (ASCII_ISLOWER(*name) && name[1] != ':' && !is_autoload)
    {
	int	    idx;


	idx = find_internal_func(name);
	if (idx >= 0)
	{
	    if (STRCMP(name, "flatten") == 0)
	    {
		emsg(_(e_cannot_use_flatten_in_vim9_script));
		goto theend;
	    }

	    if (STRCMP(name, "add") == 0 && argcount == 2)
	    {
		type_T	    *type = get_type_on_stack(cctx, 1);


		if (type->tt_type == VAR_LIST)
		{

		    res = generate_LISTAPPEND(cctx);
		    idx = -1;
		}
		else if (type->tt_type == VAR_BLOB)
		{

		    res = generate_BLOBAPPEND(cctx);
		    idx = -1;
		}
	    }

	    if (idx >= 0)
		res = generate_BCALL(cctx, idx, argcount, argcount_init == 1);
	}
	else
	    semsg(_(e_unknown_function_str), namebuf);
	goto theend;
    }


    if (lookup_local(namebuf, varlen, NULL, cctx) == FAIL
	    && arg_exists(namebuf, varlen, NULL, NULL, NULL, cctx) != OK)
    {


	ufunc = find_func(name, FALSE, cctx);
	if (ufunc != NULL && !func_is_global(ufunc))
	{
	    res = generate_CALL(cctx, ufunc, argcount);
	    goto theend;
	}
    }


    p = namebuf;
    if (STRNCMP(namebuf, "g:", 2) != 0 && !is_autoload
	    && compile_load(&p, namebuf + varlen, cctx, FALSE, FALSE) == OK)
    {
	type_T	    *type = get_type_on_stack(cctx, 0);

	res = generate_PCALL(cctx, argcount, namebuf, type, FALSE);
	goto theend;
    }


    if (ufunc != NULL)
    {
	res = generate_CALL(cctx, ufunc, argcount);
	goto theend;
    }


    if (STRNCMP(namebuf, "g:", 2) == 0 || is_autoload)
	res = generate_UCALL(cctx, name, argcount);
    else
	semsg(_(e_unknown_function_str), namebuf);

theend:
    vim_free(tofree);
    return res;
}
