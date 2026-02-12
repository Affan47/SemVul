get_func_tv(
    char_u	*name,
    int		len,
    typval_T	*rettv,
    char_u	**arg,
    evalarg_T	*evalarg,
    funcexe_T	*funcexe)
{
    char_u	*argp;
    int		ret = OK;
    typval_T	argvars[MAX_FUNC_ARGS + 1];
    int		argcount = 0;
    int		vim9script = in_vim9script();


    argp = *arg;
    while (argcount < MAX_FUNC_ARGS - (funcexe->fe_partial == NULL ? 0
					       : funcexe->fe_partial->pt_argc))
    {

	argp = skipwhite_and_linebreak(argp + 1, evalarg);

	if (*argp == ')' || *argp == ',' || *argp == NUL)
	    break;
	if (eval1(&argp, &argvars[argcount], evalarg) == FAIL)
	{
	    ret = FAIL;
	    break;
	}
	++argcount;


	if (vim9script)
	{
	    if (*argp != ',' && *skipwhite(argp) == ',')
	    {
		semsg(_(e_no_white_space_allowed_before_str_str), ",", argp);
		ret = FAIL;
		break;
	    }
	}
	else
	    argp = skipwhite(argp);
	if (*argp != ',')
	    break;
	if (vim9script && !IS_WHITE_OR_NUL(argp[1]))
	{
	    semsg(_(e_white_space_required_after_str_str), ",", argp);
	    ret = FAIL;
	    break;
	}
    }
    argp = skipwhite_and_linebreak(argp, evalarg);
    if (*argp == ')')
	++argp;
    else
	ret = FAIL;

    if (ret == OK)
    {
	int	i = 0;
	int	did_emsg_before = did_emsg;

	if (get_vim_var_nr(VV_TESTING))
	{


	    if (funcargs.ga_itemsize == 0)
		ga_init2(&funcargs, (int)sizeof(typval_T *), 50);
	    for (i = 0; i < argcount; ++i)
		if (ga_grow(&funcargs, 1) == OK)
		    ((typval_T **)funcargs.ga_data)[funcargs.ga_len++] =
								  &argvars[i];
	}

	ret = call_func(name, len, rettv, argcount, argvars, funcexe);
	if (in_vim9script() && did_emsg > did_emsg_before)
	{


	    ret = FAIL;
	    clear_tv(rettv);
	}

	funcargs.ga_len -= i;
    }
    else if (!aborting())
    {
	if (argcount == MAX_FUNC_ARGS)
	    emsg_funcname(N_("E740: Too many arguments for function %s"), name);
	else
	    emsg_funcname(e_invalid_arguments_for_function_str, name);
    }

    while (--argcount >= 0)
	clear_tv(&argvars[argcount]);

    if (in_vim9script())
	*arg = argp;
    else
	*arg = skipwhite(argp);
    return ret;
}
