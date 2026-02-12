handle_subscript(
    char_u	**arg,
    typval_T	*rettv,
    evalarg_T	*evalarg,
    int		verbose)
{
    int		evaluate = evalarg != NULL
				      && (evalarg->eval_flags & EVAL_EVALUATE);
    int		ret = OK;
    dict_T	*selfdict = NULL;
    int		check_white = TRUE;
    int		getnext;
    char_u	*p;

    while (ret == OK)
    {

	p = eval_next_non_blank(*arg, evalarg, &getnext);
	if (getnext
	    && ((rettv->v_type == VAR_DICT && *p == '.' && eval_isdictc(p[1]))
		|| (p[0] == '-' && p[1] == '>' && (p[2] == '{'
			|| ASCII_ISALPHA(in_vim9script() ? *skipwhite(p + 2)
								    : p[2])))))
	{
	    *arg = eval_next_line(evalarg);
	    p = *arg;
	    check_white = FALSE;
	}

	if (rettv->v_type == VAR_ANY)
	{
	    char_u	*exp_name;
	    int		cc;
	    int		idx;
	    ufunc_T	*ufunc;
	    type_T	*type;

	    if (**arg != '.')
	    {
		if (verbose)
		    semsg(_(e_expected_str_but_got_str), "'.'", *arg);
		ret = FAIL;
		break;
	    }
	    ++*arg;
	    if (IS_WHITE_OR_NUL(**arg))
	    {
		if (verbose)
		    emsg(_(e_no_white_space_allowed_after_dot));
		ret = FAIL;
		break;
	    }

	    exp_name = *arg;
	    while (eval_isnamec(**arg))
		++*arg;
	    cc = **arg;
	    **arg = NUL;

	    idx = find_exported(rettv->vval.v_number, exp_name, &ufunc, &type,
						  evalarg->eval_cctx, verbose);
	    **arg = cc;
	    *arg = skipwhite(*arg);

	    if (idx < 0 && ufunc == NULL)
	    {
		ret = FAIL;
		break;
	    }
	    if (idx >= 0)
	    {
		scriptitem_T    *si = SCRIPT_ITEM(rettv->vval.v_number);
		svar_T		*sv = ((svar_T *)si->sn_var_vals.ga_data) + idx;

		copy_tv(sv->sv_tv, rettv);
	    }
	    else
	    {
		rettv->v_type = VAR_FUNC;
		rettv->vval.v_string = vim_strsave(ufunc->uf_name);
	    }
	}

	if ((**arg == '(' && (!evaluate || rettv->v_type == VAR_FUNC
			    || rettv->v_type == VAR_PARTIAL))
		    && (!check_white || !VIM_ISWHITE(*(*arg - 1))))
	{
	    ret = call_func_rettv(arg, evalarg, rettv, evaluate,
							       selfdict, NULL);

	    if (aborting())
	    {
		if (ret == OK)
		    clear_tv(rettv);
		ret = FAIL;
	    }
	    dict_unref(selfdict);
	    selfdict = NULL;
	}
	else if (p[0] == '-' && p[1] == '>')
	{
	    if (in_vim9script())
		*arg = skipwhite(p + 2);
	    else
		*arg = p + 2;
	    if (ret == OK)
	    {
		if (VIM_ISWHITE(**arg))
		{
		    emsg(_(e_nowhitespace));
		    ret = FAIL;
		}
		else if ((**arg == '{' && !in_vim9script()) || **arg == '(')

		    ret = eval_lambda(arg, rettv, evalarg, verbose);
		else

		    ret = eval_method(arg, rettv, evalarg, verbose);
	    }
	}

	else if (**arg == '['
		|| (**arg == '.' && (rettv->v_type == VAR_DICT
			|| (!evaluate
			    && (*arg)[1] != '.'
			    && !in_old_script(2)))))
	{
	    dict_unref(selfdict);
	    if (rettv->v_type == VAR_DICT)
	    {
		selfdict = rettv->vval.v_dict;
		if (selfdict != NULL)
		    ++selfdict->dv_refcount;
	    }
	    else
		selfdict = NULL;
	    if (eval_index(arg, rettv, evalarg, verbose) == FAIL)
	    {
		clear_tv(rettv);
		ret = FAIL;
	    }
	}
	else
	    break;
    }

    if (selfdict != NULL
	    && (rettv->v_type == VAR_FUNC
		|| (rettv->v_type == VAR_PARTIAL
		    && (rettv->vval.v_partial->pt_auto
			|| rettv->vval.v_partial->pt_dict == NULL))))
	selfdict = make_partial(selfdict, rettv);

    dict_unref(selfdict);
    return ret;
}
}
}
