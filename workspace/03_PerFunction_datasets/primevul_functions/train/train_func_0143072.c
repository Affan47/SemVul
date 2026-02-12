eval7(
    char_u	**arg,
    typval_T	*rettv,
    evalarg_T	*evalarg,
    int		want_string)
{
    int		evaluate = evalarg != NULL
				      && (evalarg->eval_flags & EVAL_EVALUATE);
    int		len;
    char_u	*s;
    char_u	*name_start = NULL;
    char_u	*start_leader, *end_leader;
    int		ret = OK;
    char_u	*alias;
    static int	recurse = 0;
    int		vim9script = in_vim9script();

    rettv->v_type = VAR_UNKNOWN;

    start_leader = *arg;
    if (eval_leader(arg, vim9script) == FAIL)
	return FAIL;
    end_leader = *arg;

    if (**arg == '.' && (!isdigit(*(*arg + 1))
#ifdef FEAT_FLOAT
	    || in_old_script(2)
#endif
	    ))
    {
	semsg(_(e_invalid_expression_str), *arg);
	++*arg;
	return FAIL;
    }

    if (recurse ==
#ifdef _MSC_VER
		    300
#else
		    1000
#endif
		    )
    {
	semsg(_(e_expression_too_recursive_str), *arg);
	return FAIL;
    }
    ++recurse;

    switch (**arg)
    {

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':	ret = eval_number(arg, rettv, evaluate, want_string);

		if (ret == OK && evaluate && end_leader > start_leader
						  && rettv->v_type != VAR_BLOB)
		    ret = eval7_leader(rettv, TRUE, start_leader, &end_leader);
		break;

    case '"':	ret = eval_string(arg, rettv, evaluate);
		break;

    case '\'':	ret = eval_lit_string(arg, rettv, evaluate);
		break;

    case '[':	ret = eval_list(arg, rettv, evalarg, TRUE);
		break;

    case '#':	if (vim9script)
		{
		    ret = vim9_bad_comment(*arg) ? FAIL : NOTDONE;
		}
		else if ((*arg)[1] == '{')
		{
		    ++*arg;
		    ret = eval_dict(arg, rettv, evalarg, TRUE);
		}
		else
		    ret = NOTDONE;
		break;

    case '{':	if (vim9script)
		    ret = NOTDONE;
		else
		    ret = get_lambda_tv(arg, rettv, vim9script, evalarg);
		if (ret == NOTDONE)
		    ret = eval_dict(arg, rettv, evalarg, FALSE);
		break;

    case '&':	ret = eval_option(arg, rettv, evaluate);
		break;

    case '$':	ret = eval_env_var(arg, rettv, evaluate);
		break;

    case '@':	++*arg;
		if (evaluate)
		{
		    if (vim9script && IS_WHITE_OR_NUL(**arg))
			semsg(_(e_syntax_error_at_str), *arg);
		    else if (vim9script && !valid_yank_reg(**arg, FALSE))
			emsg_invreg(**arg);
		    else
		    {
			rettv->v_type = VAR_STRING;
			rettv->vval.v_string = get_reg_contents(**arg,
								GREG_EXPR_SRC);
		    }
		}
		if (**arg != NUL)
		    ++*arg;
		break;

    case '(':	ret = NOTDONE;
		if (vim9script)
		{
		    ret = get_lambda_tv(arg, rettv, TRUE, evalarg);
		    if (ret == OK && evaluate)
		    {
			ufunc_T *ufunc = rettv->vval.v_partial->pt_func;

			if (ufunc->uf_ret_type->tt_type == VAR_VOID)
			    ufunc->uf_ret_type = &t_unknown;
			if (compile_def_function(ufunc, FALSE,
					get_compile_type(ufunc), NULL) == FAIL)
			{
			    clear_tv(rettv);
			    ret = FAIL;
			}
		    }
		}
		if (ret == NOTDONE)
		{
		    *arg = skipwhite_and_linebreak(*arg + 1, evalarg);
		    ret = eval1(arg, rettv, evalarg);

		    *arg = skipwhite_and_linebreak(*arg, evalarg);
		    if (**arg == ')')
			++*arg;
		    else if (ret == OK)
		    {
			emsg(_(e_missing_closing_paren));
			clear_tv(rettv);
			ret = FAIL;
		    }
		}
		break;

    default:	ret = NOTDONE;
		break;
    }

    if (ret == NOTDONE)
    {

	s = *arg;
	len = get_name_len(arg, &alias, evaluate, TRUE);
	if (alias != NULL)
	    s = alias;

	if (len <= 0)
	    ret = FAIL;
	else
	{
	    int	    flags = evalarg == NULL ? 0 : evalarg->eval_flags;

	    if (evaluate && vim9script && len == 1 && *s == '_')
	    {
		emsg(_(e_cannot_use_underscore_here));
		ret = FAIL;
	    }
	    else if (evaluate && vim9script && len > 2
						 && s[0] == 's' && s[1] == ':')
	    {
		semsg(_(e_cannot_use_s_colon_in_vim9_script_str), s);
		ret = FAIL;
	    }
	    else if ((vim9script ? **arg : *skipwhite(*arg)) == '(')
	    {

		*arg = skipwhite(*arg);
		ret = eval_func(arg, evalarg, s, len, rettv, flags, NULL);
	    }
	    else if (flags & EVAL_CONSTANT)
		ret = FAIL;
	    else if (evaluate)
	    {

		ret = FAIL;
		if (vim9script)
		    ret = handle_predefined(s, len, rettv);
		if (ret == FAIL)
		{
		    name_start = s;
		    ret = eval_variable(s, len, 0, rettv, NULL,
					   EVAL_VAR_VERBOSE + EVAL_VAR_IMPORT);
		}
	    }
	    else
	    {

		check_vars(s, len);
		ret = OK;
	    }
	}
	vim_free(alias);
    }

    if (ret == OK)
	ret = handle_subscript(arg, name_start, rettv, evalarg, TRUE);

    if (ret == OK && evaluate && end_leader > start_leader)
	ret = eval7_leader(rettv, FALSE, start_leader, &end_leader);

    --recurse;
    return ret;
}
}
}
