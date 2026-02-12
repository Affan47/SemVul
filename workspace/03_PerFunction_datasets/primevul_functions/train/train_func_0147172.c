exec_instructions(ectx_T *ectx)
{
    int		ret = FAIL;
    int		save_trylevel_at_start = ectx->ec_trylevel_at_start;
    int		dict_stack_len_at_start = dict_stack.ga_len;


    ectx->ec_iidx = 0;


    ectx->ec_trylevel_at_start = trylevel;

    for (;;)
    {
	static int  breakcheck_count = 0;
	isn_T	    *iptr;
	typval_T    *tv;

	if (unlikely(++breakcheck_count >= 100))
	{
	    line_breakcheck();
	    breakcheck_count = 0;
	}
	if (unlikely(got_int))
	{

	    got_int = FALSE;
	    if (throw_exception("Vim:Interrupt", ET_INTERRUPT, NULL) == FAIL)
		goto theend;
	    did_throw = TRUE;
	}

	if (unlikely(did_emsg && msg_list != NULL && *msg_list != NULL))
	{

	    did_emsg = FALSE;
	    if (throw_exception(*msg_list, ET_ERROR, NULL) == FAIL)
		goto theend;
	    did_throw = TRUE;
	    *msg_list = NULL;
	}

	if (unlikely(did_throw))
	{
	    garray_T	*trystack = &ectx->ec_trystack;
	    trycmd_T    *trycmd = NULL;
	    int		index = trystack->ga_len;


	    while (index > 0)
	    {
		trycmd = ((trycmd_T *)trystack->ga_data) + index - 1;
		if (!trycmd->tcd_in_catch || trycmd->tcd_finally_idx != 0)
		    break;


		--index;
		trycmd = NULL;
	    }
	    if (trycmd != NULL && trycmd->tcd_frame_idx == ectx->ec_frame_idx)
	    {
		if (trycmd->tcd_in_catch)
		{

		    ectx->ec_iidx = trycmd->tcd_finally_idx;
		    trycmd->tcd_finally_idx = 0;
		}
		else

		    ectx->ec_iidx = trycmd->tcd_catch_idx;
		trycmd->tcd_in_catch = TRUE;
		did_throw = FALSE;
		trycmd->tcd_did_throw = TRUE;
	    }
	    else
	    {


		if (GA_GROW_FAILS(&ectx->ec_stack, 1))
		    goto theend;
		tv = STACK_TV_BOT(0);
		tv->v_type = VAR_NUMBER;
		tv->vval.v_number = 0;
		++ectx->ec_stack.ga_len;
		if (ectx->ec_frame_idx == ectx->ec_initial_frame_idx)
		{

		    need_rethrow = TRUE;
		    if (handle_closure_in_use(ectx, FALSE) == FAIL)
			goto theend;
		    goto done;
		}

		if (func_return(ectx) == FAIL)
		    goto theend;
	    }
	    continue;
	}

	iptr = &ectx->ec_instr[ectx->ec_iidx++];
	switch (iptr->isn_type)
	{

	    case ISN_EXEC:
		if (exec_command(iptr) == FAIL)
		    goto on_error;
		break;


	    case ISN_EXEC_SPLIT:
		{
		    source_cookie_T cookie;
		    char_u	    *line;

		    SOURCING_LNUM = iptr->isn_lnum;
		    CLEAR_FIELD(cookie);
		    cookie.sourcing_lnum = iptr->isn_lnum - 1;
		    cookie.nextline = iptr->isn_arg.string;
		    line = get_split_sourceline(0, &cookie, 0, 0);
		    if (do_cmdline(line,
				get_split_sourceline, &cookie,
				   DOCMD_VERBOSE|DOCMD_NOWAIT|DOCMD_KEYTYPED)
									== FAIL
				|| did_emsg)
		    {
			vim_free(line);
			goto on_error;
		    }
		    vim_free(line);
		}
		break;


	    case ISN_EXECRANGE:
		{
		    exarg_T	ea;
		    char	*error = NULL;

		    CLEAR_FIELD(ea);
		    ea.cmdidx = CMD_SIZE;
		    ea.addr_type = ADDR_LINES;
		    ea.cmd = iptr->isn_arg.string;
		    parse_cmd_address(&ea, &error, FALSE);
		    if (ea.cmd == NULL)
			goto on_error;
		    if (error == NULL)
			error = ex_range_without_command(&ea);
		    if (error != NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(error);
			goto on_error;
		    }
		}
		break;


	    case ISN_LEGACY_EVAL:
		{
		    char_u  *arg = iptr->isn_arg.string;
		    int	    res;
		    int	    save_flags = cmdmod.cmod_flags;

		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    tv = STACK_TV_BOT(0);
		    init_tv(tv);
		    cmdmod.cmod_flags |= CMOD_LEGACY;
		    res = eval0(arg, tv, NULL, &EVALARG_EVALUATE);
		    cmdmod.cmod_flags = save_flags;
		    if (res == FAIL)
			goto on_error;
		    ++ectx->ec_stack.ga_len;
		}
		break;


	    case ISN_INSTR:
		{
		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    tv = STACK_TV_BOT(0);
		    tv->vval.v_instr = ALLOC_ONE(instr_T);
		    if (tv->vval.v_instr == NULL)
			goto on_error;
		    ++ectx->ec_stack.ga_len;

		    tv->v_type = VAR_INSTR;
		    tv->vval.v_instr->instr_ectx = ectx;
		    tv->vval.v_instr->instr_instr = iptr->isn_arg.instr;
		}
		break;


	    case ISN_SUBSTITUTE:
		{
		    subs_T		*subs = &iptr->isn_arg.subs;
		    source_cookie_T	cookie;
		    struct subs_expr_S	*save_instr = substitute_instr;
		    struct subs_expr_S	subs_instr;
		    int			res;

		    subs_instr.subs_ectx = ectx;
		    subs_instr.subs_instr = subs->subs_instr;
		    subs_instr.subs_status = OK;
		    substitute_instr = &subs_instr;

		    SOURCING_LNUM = iptr->isn_lnum;

		    CLEAR_FIELD(cookie);
		    cookie.sourcing_lnum = iptr->isn_lnum - 1;
		    res = do_cmdline(subs->subs_cmd,
				getsourceline, &cookie,
				   DOCMD_VERBOSE|DOCMD_NOWAIT|DOCMD_KEYTYPED);
		    substitute_instr = save_instr;

		    if (res == FAIL || did_emsg
					     || subs_instr.subs_status == FAIL)
			goto on_error;
		}
		break;

	    case ISN_FINISH:
		goto done;

	    case ISN_REDIRSTART:

		if (alloc_redir_lval() == FAIL)
		    goto on_error;


		init_redir_ga();
		redir_vname = 1;
		break;

	    case ISN_REDIREND:
		{
		    char_u *res = get_clear_redir_ga();


		    clear_redir_lval();
		    redir_vname = 0;

		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
		    {
			vim_free(res);
			goto theend;
		    }
		    tv = STACK_TV_BOT(0);
		    tv->v_type = VAR_STRING;
		    tv->vval.v_string = res;
		    ++ectx->ec_stack.ga_len;
		}
		break;

	    case ISN_CEXPR_AUCMD:
#ifdef FEAT_QUICKFIX
		if (trigger_cexpr_autocmd(iptr->isn_arg.number) == FAIL)
		    goto on_error;
#endif
		break;

	    case ISN_CEXPR_CORE:
#ifdef FEAT_QUICKFIX
		{
		    exarg_T ea;
		    int	    res;

		    CLEAR_FIELD(ea);
		    ea.cmdidx = iptr->isn_arg.cexpr.cexpr_ref->cer_cmdidx;
		    ea.forceit = iptr->isn_arg.cexpr.cexpr_ref->cer_forceit;
		    ea.cmdlinep = &iptr->isn_arg.cexpr.cexpr_ref->cer_cmdline;
		    --ectx->ec_stack.ga_len;
		    tv = STACK_TV_BOT(0);
		    res = cexpr_core(&ea, tv);
		    clear_tv(tv);
		    if (res == FAIL)
			goto on_error;
		}
#endif
		break;


	    case ISN_EXECCONCAT:
		{
		    int	    count = iptr->isn_arg.number;
		    size_t  len = 0;
		    int	    pass;
		    int	    i;
		    char_u  *cmd = NULL;
		    char_u  *str;

		    for (pass = 1; pass <= 2; ++pass)
		    {
			for (i = 0; i < count; ++i)
			{
			    tv = STACK_TV_BOT(i - count);
			    str = tv->vval.v_string;
			    if (str != NULL && *str != NUL)
			    {
				if (pass == 2)
				    STRCPY(cmd + len, str);
				len += STRLEN(str);
			    }
			    if (pass == 2)
				clear_tv(tv);
			}
			if (pass == 1)
			{
			    cmd = alloc(len + 1);
			    if (unlikely(cmd == NULL))
				goto theend;
			    len = 0;
			}
		    }

		    SOURCING_LNUM = iptr->isn_lnum;
		    do_cmdline_cmd(cmd);
		    vim_free(cmd);
		}
		break;


	    case ISN_ECHO:
		{
		    int count = iptr->isn_arg.echo.echo_count;
		    int	atstart = TRUE;
		    int needclr = TRUE;
		    int	idx;

		    for (idx = 0; idx < count; ++idx)
		    {
			tv = STACK_TV_BOT(idx - count);
			echo_one(tv, iptr->isn_arg.echo.echo_with_white,
							   &atstart, &needclr);
			clear_tv(tv);
		    }
		    if (needclr)
			msg_clr_eos();
		    ectx->ec_stack.ga_len -= count;
		}
		break;


	    case ISN_EXECUTE:
	    case ISN_ECHOMSG:
	    case ISN_ECHOCONSOLE:
	    case ISN_ECHOERR:
		{
		    int		count = iptr->isn_arg.number;
		    garray_T	ga;
		    char_u	buf[NUMBUFLEN];
		    char_u	*p;
		    int		len;
		    int		failed = FALSE;
		    int		idx;

		    ga_init2(&ga, 1, 80);
		    for (idx = 0; idx < count; ++idx)
		    {
			tv = STACK_TV_BOT(idx - count);
			if (iptr->isn_type == ISN_EXECUTE)
			{
			    if (tv->v_type == VAR_CHANNEL
						      || tv->v_type == VAR_JOB)
			    {
				SOURCING_LNUM = iptr->isn_lnum;
				semsg(_(e_using_invalid_value_as_string_str),
						    vartype_name(tv->v_type));
				break;
			    }
			    else
				p = tv_get_string_buf(tv, buf);
			}
			else
			    p = tv_stringify(tv, buf);

			len = (int)STRLEN(p);
			if (GA_GROW_FAILS(&ga, len + 2))
			    failed = TRUE;
			else
			{
			    if (ga.ga_len > 0)
				((char_u *)(ga.ga_data))[ga.ga_len++] = ' ';
			    STRCPY((char_u *)(ga.ga_data) + ga.ga_len, p);
			    ga.ga_len += len;
			}
			clear_tv(tv);
		    }
		    ectx->ec_stack.ga_len -= count;
		    if (failed)
		    {
			ga_clear(&ga);
			goto on_error;
		    }

		    if (ga.ga_data != NULL)
		    {
			if (iptr->isn_type == ISN_EXECUTE)
			{
			    SOURCING_LNUM = iptr->isn_lnum;
			    do_cmdline_cmd((char_u *)ga.ga_data);
			    if (did_emsg)
			    {
				ga_clear(&ga);
				goto on_error;
			    }
			}
			else
			{
			    msg_sb_eol();
			    if (iptr->isn_type == ISN_ECHOMSG)
			    {
				msg_attr(ga.ga_data, echo_attr);
				out_flush();
			    }
			    else if (iptr->isn_type == ISN_ECHOCONSOLE)
			    {
				ui_write(ga.ga_data, (int)STRLEN(ga.ga_data),
									 TRUE);
				ui_write((char_u *)"\r\n", 2, TRUE);
			    }
			    else
			    {
				SOURCING_LNUM = iptr->isn_lnum;
				emsg(ga.ga_data);
			    }
			}
		    }
		    ga_clear(&ga);
		}
		break;


	    case ISN_LOAD:
		if (GA_GROW_FAILS(&ectx->ec_stack, 1))
		    goto theend;
		copy_tv(STACK_TV_VAR(iptr->isn_arg.number), STACK_TV_BOT(0));
		++ectx->ec_stack.ga_len;
		break;


	    case ISN_LOADV:
		if (GA_GROW_FAILS(&ectx->ec_stack, 1))
		    goto theend;
		copy_tv(get_vim_var_tv(iptr->isn_arg.number), STACK_TV_BOT(0));
		++ectx->ec_stack.ga_len;
		break;


	    case ISN_LOADSCRIPT:
		{
		    scriptref_T	*sref = iptr->isn_arg.script.scriptref;
		    svar_T	 *sv;

		    sv = get_script_svar(sref, ectx->ec_dfunc_idx);
		    if (sv == NULL)
			goto theend;
		    allocate_if_null(sv->sv_tv);
		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    copy_tv(sv->sv_tv, STACK_TV_BOT(0));
		    ++ectx->ec_stack.ga_len;
		}
		break;


	    case ISN_LOADS:
		{
		    hashtab_T	*ht = &SCRIPT_VARS(
					       iptr->isn_arg.loadstore.ls_sid);
		    char_u	*name = iptr->isn_arg.loadstore.ls_name;
		    dictitem_T	*di = find_var_in_ht(ht, 0, name, TRUE);

		    if (di == NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			semsg(_(e_undefined_variable_str), name);
			goto on_error;
		    }
		    else
		    {
			if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			    goto theend;
			copy_tv(&di->di_tv, STACK_TV_BOT(0));
			++ectx->ec_stack.ga_len;
		    }
		}
		break;


	    case ISN_LOADG:
	    case ISN_LOADB:
	    case ISN_LOADW:
	    case ISN_LOADT:
		{
		    dictitem_T *di = NULL;
		    hashtab_T *ht = NULL;
		    char namespace;

		    switch (iptr->isn_type)
		    {
			case ISN_LOADG:
			    ht = get_globvar_ht();
			    namespace = 'g';
			    break;
			case ISN_LOADB:
			    ht = &curbuf->b_vars->dv_hashtab;
			    namespace = 'b';
			    break;
			case ISN_LOADW:
			    ht = &curwin->w_vars->dv_hashtab;
			    namespace = 'w';
			    break;
			case ISN_LOADT:
			    ht = &curtab->tp_vars->dv_hashtab;
			    namespace = 't';
			    break;
			default:
			    goto theend;
		    }
		    di = find_var_in_ht(ht, 0, iptr->isn_arg.string, TRUE);

		    if (di == NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			semsg(_(e_undefined_variable_char_str),
					     namespace, iptr->isn_arg.string);
			goto on_error;
		    }
		    else
		    {
			if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			    goto theend;
			copy_tv(&di->di_tv, STACK_TV_BOT(0));
			++ectx->ec_stack.ga_len;
		    }
		}
		break;


	    case ISN_LOADAUTO:
		{
		    char_u *name = iptr->isn_arg.string;

		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    SOURCING_LNUM = iptr->isn_lnum;
		    if (eval_variable(name, (int)STRLEN(name), 0,
			      STACK_TV_BOT(0), NULL, EVAL_VAR_VERBOSE) == FAIL)
			goto on_error;
		    ++ectx->ec_stack.ga_len;
		}
		break;


	    case ISN_LOADGDICT:
	    case ISN_LOADBDICT:
	    case ISN_LOADWDICT:
	    case ISN_LOADTDICT:
		{
		    dict_T *d = NULL;

		    switch (iptr->isn_type)
		    {
			case ISN_LOADGDICT: d = get_globvar_dict(); break;
			case ISN_LOADBDICT: d = curbuf->b_vars; break;
			case ISN_LOADWDICT: d = curwin->w_vars; break;
			case ISN_LOADTDICT: d = curtab->tp_vars; break;
			default:
			    goto theend;
		    }
		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    tv = STACK_TV_BOT(0);
		    tv->v_type = VAR_DICT;
		    tv->v_lock = 0;
		    tv->vval.v_dict = d;
		    ++d->dv_refcount;
		    ++ectx->ec_stack.ga_len;
		}
		break;


	    case ISN_LOADOPT:
		{
		    typval_T	optval;
		    char_u	*name = iptr->isn_arg.string;


		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    if (eval_option(&name, &optval, TRUE) == FAIL)
			goto theend;
		    *STACK_TV_BOT(0) = optval;
		    ++ectx->ec_stack.ga_len;
		}
		break;


	    case ISN_LOADENV:
		{
		    typval_T	optval;
		    char_u	*name = iptr->isn_arg.string;

		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;

		    (void)eval_env_var(&name, &optval, TRUE);
		    *STACK_TV_BOT(0) = optval;
		    ++ectx->ec_stack.ga_len;
		}
		break;


	    case ISN_LOADREG:
		if (GA_GROW_FAILS(&ectx->ec_stack, 1))
		    goto theend;
		tv = STACK_TV_BOT(0);
		tv->v_type = VAR_STRING;
		tv->v_lock = 0;


		tv->vval.v_string = get_reg_contents(
					  iptr->isn_arg.number, GREG_EXPR_SRC);
		++ectx->ec_stack.ga_len;
		break;


	    case ISN_STORE:
		--ectx->ec_stack.ga_len;
		tv = STACK_TV_VAR(iptr->isn_arg.number);
		clear_tv(tv);
		*tv = *STACK_TV_BOT(0);
		break;


	    case ISN_STORES:
		{
		    hashtab_T	*ht = &SCRIPT_VARS(
					       iptr->isn_arg.loadstore.ls_sid);
		    char_u	*name = iptr->isn_arg.loadstore.ls_name;
		    dictitem_T	*di = find_var_in_ht(ht, 0, name + 2, TRUE);

		    --ectx->ec_stack.ga_len;
		    if (di == NULL)
			store_var(name, STACK_TV_BOT(0));
		    else
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			if (var_check_permission(di, name) == FAIL)
			{
			    clear_tv(STACK_TV_BOT(0));
			    goto on_error;
			}
			clear_tv(&di->di_tv);
			di->di_tv = *STACK_TV_BOT(0);
		    }
		}
		break;


	    case ISN_STORESCRIPT:
		{
		    scriptref_T	    *sref = iptr->isn_arg.script.scriptref;
		    svar_T	    *sv;

		    sv = get_script_svar(sref, ectx->ec_dfunc_idx);
		    if (sv == NULL)
			goto theend;
		    --ectx->ec_stack.ga_len;


		    SOURCING_LNUM = iptr->isn_lnum;
		    if (value_check_lock(sv->sv_tv->v_lock, sv->sv_name, FALSE))
		    {
			clear_tv(STACK_TV_BOT(0));
			goto on_error;
		    }

		    clear_tv(sv->sv_tv);
		    *sv->sv_tv = *STACK_TV_BOT(0);
		}
		break;


	    case ISN_STOREOPT:
	    case ISN_STOREFUNCOPT:
		{
		    char_u	*opt_name = iptr->isn_arg.storeopt.so_name;
		    int		opt_flags = iptr->isn_arg.storeopt.so_flags;
		    long	n = 0;
		    char_u	*s = NULL;
		    char	*msg;
		    char_u	numbuf[NUMBUFLEN];
		    char_u	*tofree = NULL;

		    --ectx->ec_stack.ga_len;
		    tv = STACK_TV_BOT(0);
		    if (tv->v_type == VAR_STRING)
		    {
			s = tv->vval.v_string;
			if (s == NULL)
			    s = (char_u *)"";
		    }
		    else if (iptr->isn_type == ISN_STOREFUNCOPT)
		    {
			SOURCING_LNUM = iptr->isn_lnum;


			s = tv2string(tv, &tofree, numbuf, 0);
			if (s == NULL || *s == NUL)
			{
			    clear_tv(tv);
			    goto on_error;
			}
		    }
		    else

			n = tv->vval.v_number;
		    msg = set_option_value(opt_name, n, s, opt_flags);
		    clear_tv(tv);
		    vim_free(tofree);
		    if (msg != NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(_(msg));
			goto on_error;
		    }
		}
		break;


	    case ISN_STOREENV:
		--ectx->ec_stack.ga_len;
		tv = STACK_TV_BOT(0);
		vim_setenv_ext(iptr->isn_arg.string, tv_get_string(tv));
		clear_tv(tv);
		break;


	    case ISN_STOREREG:
		{
		    int	reg = iptr->isn_arg.number;

		    --ectx->ec_stack.ga_len;
		    tv = STACK_TV_BOT(0);
		    write_reg_contents(reg, tv_get_string(tv), -1, FALSE);
		    clear_tv(tv);
		}
		break;


	    case ISN_STOREV:
		--ectx->ec_stack.ga_len;
		if (set_vim_var_tv(iptr->isn_arg.number, STACK_TV_BOT(0))
								       == FAIL)

		    goto on_error;
		break;


	    case ISN_STOREG:
	    case ISN_STOREB:
	    case ISN_STOREW:
	    case ISN_STORET:
		{
		    dictitem_T	*di;
		    hashtab_T	*ht;
		    char_u	*name = iptr->isn_arg.string + 2;

		    switch (iptr->isn_type)
		    {
			case ISN_STOREG:
			    ht = get_globvar_ht();
			    break;
			case ISN_STOREB:
			    ht = &curbuf->b_vars->dv_hashtab;
			    break;
			case ISN_STOREW:
			    ht = &curwin->w_vars->dv_hashtab;
			    break;
			case ISN_STORET:
			    ht = &curtab->tp_vars->dv_hashtab;
			    break;
			default:
			    goto theend;
		    }

		    --ectx->ec_stack.ga_len;
		    di = find_var_in_ht(ht, 0, name, TRUE);
		    if (di == NULL)
			store_var(iptr->isn_arg.string, STACK_TV_BOT(0));
		    else
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			if (var_check_permission(di, name) == FAIL)
			    goto on_error;
			clear_tv(&di->di_tv);
			di->di_tv = *STACK_TV_BOT(0);
		    }
		}
		break;


	    case ISN_STOREAUTO:
		SOURCING_LNUM = iptr->isn_lnum;
		set_var(iptr->isn_arg.string, STACK_TV_BOT(-1), TRUE);
		clear_tv(STACK_TV_BOT(-1));
		--ectx->ec_stack.ga_len;
		break;


	    case ISN_STORENR:
		tv = STACK_TV_VAR(iptr->isn_arg.storenr.stnr_idx);
		clear_tv(tv);
		tv->v_type = VAR_NUMBER;
		tv->vval.v_number = iptr->isn_arg.storenr.stnr_val;
		break;


	    case ISN_STOREINDEX:
		{
		    vartype_T	dest_type = iptr->isn_arg.vartype;
		    typval_T	*tv_idx = STACK_TV_BOT(-2);
		    typval_T	*tv_dest = STACK_TV_BOT(-1);
		    int		status = OK;


		    tv = STACK_TV_BOT(-3);
		    SOURCING_LNUM = iptr->isn_lnum;
		    if (dest_type == VAR_ANY)
		    {
			dest_type = tv_dest->v_type;
			if (dest_type == VAR_DICT)
			    status = do_2string(tv_idx, TRUE, FALSE);
			else if (dest_type == VAR_LIST
					       && tv_idx->v_type != VAR_NUMBER)
			{
			    emsg(_(e_number_expected));
			    status = FAIL;
			}
		    }
		    else if (dest_type != tv_dest->v_type)
		    {

			semsg(_(e_expected_str_but_got_str),
				    vartype_name(dest_type),
				    vartype_name(tv_dest->v_type));
			status = FAIL;
		    }

		    if (status == OK && dest_type == VAR_LIST)
		    {
			long	    lidx = (long)tv_idx->vval.v_number;
			list_T	    *list = tv_dest->vval.v_list;

			if (list == NULL)
			{
			    emsg(_(e_list_not_set));
			    goto on_error;
			}
			if (lidx < 0 && list->lv_len + lidx >= 0)

			    lidx = list->lv_len + lidx;
			if (lidx < 0 || lidx > list->lv_len)
			{
			    semsg(_(e_list_index_out_of_range_nr), lidx);
			    goto on_error;
			}
			if (lidx < list->lv_len)
			{
			    listitem_T *li = list_find(list, lidx);

			    if (error_if_locked(li->li_tv.v_lock,
						    e_cannot_change_list_item))
				goto on_error;

			    clear_tv(&li->li_tv);
			    li->li_tv = *tv;
			}
			else
			{
			    if (error_if_locked(list->lv_lock,
							 e_cannot_change_list))
				goto on_error;

			    if (list_append_tv(list, tv) == FAIL)
				goto theend;
			    clear_tv(tv);
			}
		    }
		    else if (status == OK && dest_type == VAR_DICT)
		    {
			char_u		*key = tv_idx->vval.v_string;
			dict_T		*dict = tv_dest->vval.v_dict;
			dictitem_T	*di;

			SOURCING_LNUM = iptr->isn_lnum;
			if (dict == NULL)
			{
			    emsg(_(e_dictionary_not_set));
			    goto on_error;
			}
			if (key == NULL)
			    key = (char_u *)"";
			di = dict_find(dict, key, -1);
			if (di != NULL)
			{
			    if (error_if_locked(di->di_tv.v_lock,
						    e_cannot_change_dict_item))
				goto on_error;

			    clear_tv(&di->di_tv);
			    di->di_tv = *tv;
			}
			else
			{
			    if (error_if_locked(dict->dv_lock,
							 e_cannot_change_dict))
				goto on_error;

			    if (dict_add_tv(dict, (char *)key, tv) == FAIL)
				goto theend;
			    clear_tv(tv);
			}
		    }
		    else if (status == OK && dest_type == VAR_BLOB)
		    {
			long	    lidx = (long)tv_idx->vval.v_number;
			blob_T	    *blob = tv_dest->vval.v_blob;
			varnumber_T nr;
			int	    error = FALSE;
			int	    len;

			if (blob == NULL)
			{
			    emsg(_(e_blob_not_set));
			    goto on_error;
			}
			len = blob_len(blob);
			if (lidx < 0 && len + lidx >= 0)

			    lidx = len + lidx;


			if (lidx < 0 || lidx > len)
			{
			    semsg(_(e_blob_index_out_of_range_nr), lidx);
			    goto on_error;
			}
			if (value_check_lock(blob->bv_lock,
						      (char_u *)"blob", FALSE))
			    goto on_error;
			nr = tv_get_number_chk(tv, &error);
			if (error)
			    goto on_error;
			blob_set_append(blob, lidx, nr);
		    }
		    else
		    {
			status = FAIL;
			semsg(_(e_cannot_index_str), vartype_name(dest_type));
		    }

		    clear_tv(tv_idx);
		    clear_tv(tv_dest);
		    ectx->ec_stack.ga_len -= 3;
		    if (status == FAIL)
		    {
			clear_tv(tv);
			goto on_error;
		    }
		}
		break;


	    case ISN_STORERANGE:
		{
		    typval_T	*tv_idx1 = STACK_TV_BOT(-3);
		    typval_T	*tv_idx2 = STACK_TV_BOT(-2);
		    typval_T	*tv_dest = STACK_TV_BOT(-1);
		    int		status = OK;


		    tv = STACK_TV_BOT(-4);
		    if (tv_dest->v_type == VAR_LIST)
		    {
			long	n1;
			long	n2;
			int	error = FALSE;

			SOURCING_LNUM = iptr->isn_lnum;
			n1 = (long)tv_get_number_chk(tv_idx1, &error);
			if (error)
			    status = FAIL;
			else
			{
			    if (tv_idx2->v_type == VAR_SPECIAL
					&& tv_idx2->vval.v_number == VVAL_NONE)
				n2 = list_len(tv_dest->vval.v_list) - 1;
			    else
				n2 = (long)tv_get_number_chk(tv_idx2, &error);
			    if (error)
				status = FAIL;
			    else
			    {
				listitem_T *li1 = check_range_index_one(
					tv_dest->vval.v_list, &n1, FALSE);

				if (li1 == NULL)
				    status = FAIL;
				else
				{
				    status = check_range_index_two(
					    tv_dest->vval.v_list,
					    &n1, li1, &n2, FALSE);
				    if (status != FAIL)
					status = list_assign_range(
						tv_dest->vval.v_list,
						tv->vval.v_list,
						n1,
						n2,
						tv_idx2->v_type == VAR_SPECIAL,
						(char_u *)"=",
						(char_u *)"[unknown]");
				}
			    }
			}
		    }
		    else if (tv_dest->v_type == VAR_BLOB)
		    {
			varnumber_T n1;
			varnumber_T n2;
			int	    error = FALSE;

			n1 = tv_get_number_chk(tv_idx1, &error);
			if (error)
			    status = FAIL;
			else
			{
			    if (tv_idx2->v_type == VAR_SPECIAL
					&& tv_idx2->vval.v_number == VVAL_NONE)
				n2 = blob_len(tv_dest->vval.v_blob) - 1;
			    else
				n2 = tv_get_number_chk(tv_idx2, &error);
			    if (error)
				status = FAIL;
			    else
			    {
				long  bloblen = blob_len(tv_dest->vval.v_blob);

				if (check_blob_index(bloblen,
							     n1, FALSE) == FAIL
					|| check_blob_range(bloblen,
							n1, n2, FALSE) == FAIL)
				    status = FAIL;
				else
				    status = blob_set_range(
					     tv_dest->vval.v_blob, n1, n2, tv);
			    }
			}
		    }
		    else
		    {
			status = FAIL;
			emsg(_(e_blob_required));
		    }

		    clear_tv(tv_idx1);
		    clear_tv(tv_idx2);
		    clear_tv(tv_dest);
		    ectx->ec_stack.ga_len -= 4;
		    clear_tv(tv);

		    if (status == FAIL)
			goto on_error;
		}
		break;


	    case ISN_LOADOUTER:
	    case ISN_STOREOUTER:
		{
		    int		depth = iptr->isn_arg.outer.outer_depth;
		    outer_T	*outer = ectx->ec_outer_ref == NULL ? NULL
						: ectx->ec_outer_ref->or_outer;

		    while (depth > 1 && outer != NULL)
		    {
			outer = outer->out_up;
			--depth;
		    }
		    if (outer == NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			if (ectx->ec_frame_idx == ectx->ec_initial_frame_idx
						 || ectx->ec_outer_ref == NULL)


			    emsg(_(e_closure_called_from_invalid_context));
			else
			    iemsg("LOADOUTER depth more than scope levels");
			goto theend;
		    }
		    tv = ((typval_T *)outer->out_stack->ga_data)
				    + outer->out_frame_idx + STACK_FRAME_SIZE
				    + iptr->isn_arg.outer.outer_idx;
		    if (iptr->isn_type == ISN_LOADOUTER)
		    {
			if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			    goto theend;
			copy_tv(tv, STACK_TV_BOT(0));
			++ectx->ec_stack.ga_len;
		    }
		    else
		    {
			--ectx->ec_stack.ga_len;
			clear_tv(tv);
			*tv = *STACK_TV_BOT(0);
		    }
		}
		break;


	    case ISN_UNLETINDEX:
		{
		    typval_T	*tv_idx = STACK_TV_BOT(-2);
		    typval_T	*tv_dest = STACK_TV_BOT(-1);
		    int		status = OK;


		    if (tv_dest->v_type == VAR_DICT)
		    {

			if (tv_idx->v_type != VAR_STRING)
			{
			    SOURCING_LNUM = iptr->isn_lnum;
			    semsg(_(e_expected_str_but_got_str),
					vartype_name(VAR_STRING),
					vartype_name(tv_idx->v_type));
			    status = FAIL;
			}
			else
			{
			    dict_T	*d = tv_dest->vval.v_dict;
			    char_u	*key = tv_idx->vval.v_string;
			    dictitem_T  *di = NULL;

			    if (d != NULL && value_check_lock(
						      d->dv_lock, NULL, FALSE))
				status = FAIL;
			    else
			    {
				SOURCING_LNUM = iptr->isn_lnum;
				if (key == NULL)
				    key = (char_u *)"";
				if (d != NULL)
				    di = dict_find(d, key, (int)STRLEN(key));
				if (di == NULL)
				{

				    semsg(_(e_key_not_present_in_dictionary), key);
				    status = FAIL;
				}
				else if (var_check_fixed(di->di_flags,
								   NULL, FALSE)
					|| var_check_ro(di->di_flags,
								  NULL, FALSE))
				    status = FAIL;
				else
				    dictitem_remove(d, di);
			    }
			}
		    }
		    else if (tv_dest->v_type == VAR_LIST)
		    {

			SOURCING_LNUM = iptr->isn_lnum;
			if (check_for_number(tv_idx) == FAIL)
			{
			    status = FAIL;
			}
			else
			{
			    list_T	*l = tv_dest->vval.v_list;
			    long	n = (long)tv_idx->vval.v_number;

			    if (l != NULL && value_check_lock(
						      l->lv_lock, NULL, FALSE))
				status = FAIL;
			    else
			    {
				listitem_T	*li = list_find(l, n);

				if (li == NULL)
				{
				    SOURCING_LNUM = iptr->isn_lnum;
				    semsg(_(e_list_index_out_of_range_nr), n);
				    status = FAIL;
				}
				else if (value_check_lock(li->li_tv.v_lock,
								  NULL, FALSE))
				    status = FAIL;
				else
				    listitem_remove(l, li);
			    }
			}
		    }
		    else
		    {
			status = FAIL;
			semsg(_(e_cannot_index_str),
						vartype_name(tv_dest->v_type));
		    }

		    clear_tv(tv_idx);
		    clear_tv(tv_dest);
		    ectx->ec_stack.ga_len -= 2;
		    if (status == FAIL)
			goto on_error;
		}
		break;


	    case ISN_UNLETRANGE:
		{


		    typval_T	*tv_idx1 = STACK_TV_BOT(-3);
		    typval_T	*tv_idx2 = STACK_TV_BOT(-2);
		    typval_T	*tv_dest = STACK_TV_BOT(-1);
		    int		status = OK;

		    if (tv_dest->v_type == VAR_LIST)
		    {

			SOURCING_LNUM = iptr->isn_lnum;
			if (check_for_number(tv_idx1) == FAIL
				|| (tv_idx2->v_type != VAR_SPECIAL
					 && check_for_number(tv_idx2) == FAIL))
			{
			    status = FAIL;
			}
			else
			{
			    list_T	*l = tv_dest->vval.v_list;
			    long	n1 = (long)tv_idx1->vval.v_number;
			    long	n2 = tv_idx2->v_type == VAR_SPECIAL
					    ? 0 : (long)tv_idx2->vval.v_number;
			    listitem_T	*li;

			    li = list_find_index(l, &n1);
			    if (li == NULL)
				status = FAIL;
			    else
			    {
				if (n1 < 0)
				    n1 = list_idx_of_item(l, li);
				if (n2 < 0)
				{
				    listitem_T *li2 = list_find(l, n2);

				    if (li2 == NULL)
					status = FAIL;
				    else
					n2 = list_idx_of_item(l, li2);
				}
				if (status != FAIL
					&& tv_idx2->v_type != VAR_SPECIAL
					&& n2 < n1)
				{
				    semsg(_(e_list_index_out_of_range_nr), n2);
				    status = FAIL;
				}
				if (status != FAIL
					&& list_unlet_range(l, li, NULL, n1,
					    tv_idx2->v_type != VAR_SPECIAL, n2)
								       == FAIL)
				    status = FAIL;
			    }
			}
		    }
		    else
		    {
			status = FAIL;
			SOURCING_LNUM = iptr->isn_lnum;
			semsg(_(e_cannot_index_str),
						vartype_name(tv_dest->v_type));
		    }

		    clear_tv(tv_idx1);
		    clear_tv(tv_idx2);
		    clear_tv(tv_dest);
		    ectx->ec_stack.ga_len -= 3;
		    if (status == FAIL)
			goto on_error;
		}
		break;


	    case ISN_PUSHNR:
	    case ISN_PUSHBOOL:
	    case ISN_PUSHSPEC:
	    case ISN_PUSHF:
	    case ISN_PUSHS:
	    case ISN_PUSHBLOB:
	    case ISN_PUSHFUNC:
	    case ISN_PUSHCHANNEL:
	    case ISN_PUSHJOB:
		if (GA_GROW_FAILS(&ectx->ec_stack, 1))
		    goto theend;
		tv = STACK_TV_BOT(0);
		tv->v_lock = 0;
		++ectx->ec_stack.ga_len;
		switch (iptr->isn_type)
		{
		    case ISN_PUSHNR:
			tv->v_type = VAR_NUMBER;
			tv->vval.v_number = iptr->isn_arg.number;
			break;
		    case ISN_PUSHBOOL:
			tv->v_type = VAR_BOOL;
			tv->vval.v_number = iptr->isn_arg.number;
			break;
		    case ISN_PUSHSPEC:
			tv->v_type = VAR_SPECIAL;
			tv->vval.v_number = iptr->isn_arg.number;
			break;
#ifdef FEAT_FLOAT
		    case ISN_PUSHF:
			tv->v_type = VAR_FLOAT;
			tv->vval.v_float = iptr->isn_arg.fnumber;
			break;
#endif
		    case ISN_PUSHBLOB:
			blob_copy(iptr->isn_arg.blob, tv);
			break;
		    case ISN_PUSHFUNC:
			tv->v_type = VAR_FUNC;
			if (iptr->isn_arg.string == NULL)
			    tv->vval.v_string = NULL;
			else
			    tv->vval.v_string =
					     vim_strsave(iptr->isn_arg.string);
			break;
		    case ISN_PUSHCHANNEL:
#ifdef FEAT_JOB_CHANNEL
			tv->v_type = VAR_CHANNEL;
			tv->vval.v_channel = iptr->isn_arg.channel;
			if (tv->vval.v_channel != NULL)
			    ++tv->vval.v_channel->ch_refcount;
#endif
			break;
		    case ISN_PUSHJOB:
#ifdef FEAT_JOB_CHANNEL
			tv->v_type = VAR_JOB;
			tv->vval.v_job = iptr->isn_arg.job;
			if (tv->vval.v_job != NULL)
			    ++tv->vval.v_job->jv_refcount;
#endif
			break;
		    default:
			tv->v_type = VAR_STRING;
			tv->vval.v_string = vim_strsave(
				iptr->isn_arg.string == NULL
					? (char_u *)"" : iptr->isn_arg.string);
		}
		break;

	    case ISN_UNLET:
		if (do_unlet(iptr->isn_arg.unlet.ul_name,
				       iptr->isn_arg.unlet.ul_forceit) == FAIL)
		    goto on_error;
		break;
	    case ISN_UNLETENV:
		vim_unsetenv(iptr->isn_arg.unlet.ul_name);
		break;

	    case ISN_LOCKUNLOCK:
		{
		    typval_T	*lval_root_save = lval_root;
		    int		res;


		    --ectx->ec_stack.ga_len;
		    lval_root = STACK_TV_BOT(0);
		    res = exec_command(iptr);
		    clear_tv(lval_root);
		    lval_root = lval_root_save;
		    if (res == FAIL)
			goto on_error;
		}
		break;

	    case ISN_LOCKCONST:
		item_lock(STACK_TV_BOT(-1), 100, TRUE, TRUE);
		break;


	    case ISN_NEWLIST:
		if (exe_newlist(iptr->isn_arg.number, ectx) == FAIL)
		    goto theend;
		break;


	    case ISN_NEWDICT:
		{
		    int		count = iptr->isn_arg.number;
		    dict_T	*dict = dict_alloc();
		    dictitem_T	*item;
		    char_u	*key;
		    int		idx;

		    if (unlikely(dict == NULL))
			goto theend;
		    for (idx = 0; idx < count; ++idx)
		    {

			tv = STACK_TV_BOT(2 * (idx - count));

			key = tv->vval.v_string == NULL
					    ? (char_u *)"" : tv->vval.v_string;
			item = dict_find(dict, key, -1);
			if (item != NULL)
			{
			    SOURCING_LNUM = iptr->isn_lnum;
			    semsg(_(e_duplicate_key_in_dicitonary), key);
			    dict_unref(dict);
			    goto on_error;
			}
			item = dictitem_alloc(key);
			clear_tv(tv);
			if (unlikely(item == NULL))
			{
			    dict_unref(dict);
			    goto theend;
			}
			item->di_tv = *STACK_TV_BOT(2 * (idx - count) + 1);
			item->di_tv.v_lock = 0;
			if (dict_add(dict, item) == FAIL)
			{

			    dict_unref(dict);
			    goto theend;
			}
		    }

		    if (count > 0)
			ectx->ec_stack.ga_len -= 2 * count - 1;
		    else if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    else
			++ectx->ec_stack.ga_len;
		    tv = STACK_TV_BOT(-1);
		    tv->v_type = VAR_DICT;
		    tv->v_lock = 0;
		    tv->vval.v_dict = dict;
		    ++dict->dv_refcount;
		}
		break;


	    case ISN_DCALL:
		SOURCING_LNUM = iptr->isn_lnum;
		if (call_dfunc(iptr->isn_arg.dfunc.cdf_idx,
				NULL,
				iptr->isn_arg.dfunc.cdf_argcount,
				ectx) == FAIL)
		    goto on_error;
		break;


	    case ISN_BCALL:
		SOURCING_LNUM = iptr->isn_lnum;
		if (call_bfunc(iptr->isn_arg.bfunc.cbf_idx,
			      iptr->isn_arg.bfunc.cbf_argcount,
			      ectx) == FAIL)
		    goto on_error;
		break;


	    case ISN_PCALL:
		{
		    cpfunc_T	*pfunc = &iptr->isn_arg.pfunc;
		    int		r;
		    typval_T	partial_tv;

		    SOURCING_LNUM = iptr->isn_lnum;
		    if (pfunc->cpf_top)
		    {

			tv = STACK_TV_BOT(-pfunc->cpf_argcount - 1);
		    }
		    else
		    {

			--ectx->ec_stack.ga_len;
			partial_tv = *STACK_TV_BOT(0);
			tv = &partial_tv;
		    }
		    r = call_partial(tv, pfunc->cpf_argcount, ectx);
		    if (tv == &partial_tv)
			clear_tv(&partial_tv);
		    if (r == FAIL)
			goto on_error;
		}
		break;

	    case ISN_PCALL_END:


		--ectx->ec_stack.ga_len;
		clear_tv(STACK_TV_BOT(-1));
		*STACK_TV_BOT(-1) = *STACK_TV_BOT(0);
		break;


	    case ISN_UCALL:
		{
		    cufunc_T	*cufunc = &iptr->isn_arg.ufunc;

		    SOURCING_LNUM = iptr->isn_lnum;
		    if (call_eval_func(cufunc->cuf_name, cufunc->cuf_argcount,
							   ectx, iptr) == FAIL)
			goto on_error;
		}
		break;


	    case ISN_RETURN_VOID:
		if (GA_GROW_FAILS(&ectx->ec_stack, 1))
		    goto theend;
		tv = STACK_TV_BOT(0);
		++ectx->ec_stack.ga_len;
		tv->v_type = VAR_VOID;
		tv->vval.v_number = 0;
		tv->v_lock = 0;


	    case ISN_RETURN:
		{
		    garray_T	*trystack = &ectx->ec_trystack;
		    trycmd_T    *trycmd = NULL;

		    if (trystack->ga_len > 0)
			trycmd = ((trycmd_T *)trystack->ga_data)
							+ trystack->ga_len - 1;
		    if (trycmd != NULL
				 && trycmd->tcd_frame_idx == ectx->ec_frame_idx)
		    {

			if (trycmd->tcd_finally_idx != 0)
			    ectx->ec_iidx = trycmd->tcd_finally_idx;
			else
			    ectx->ec_iidx = trycmd->tcd_endtry_idx;
			trycmd->tcd_return = TRUE;
		    }
		    else
			goto func_return;
		}
		break;


	    case ISN_FUNCREF:
		{
		    partial_T   *pt = ALLOC_CLEAR_ONE(partial_T);
		    ufunc_T	*ufunc;
		    funcref_T	*funcref = &iptr->isn_arg.funcref;

		    if (pt == NULL)
			goto theend;
		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
		    {
			vim_free(pt);
			goto theend;
		    }
		    if (funcref->fr_func_name == NULL)
		    {
			dfunc_T	*pt_dfunc = ((dfunc_T *)def_functions.ga_data)
						       + funcref->fr_dfunc_idx;

			ufunc = pt_dfunc->df_ufunc;
		    }
		    else
		    {
			ufunc = find_func(funcref->fr_func_name, FALSE, NULL);
		    }
		    if (ufunc == NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(_(e_function_reference_invalid));
			goto theend;
		    }
		    if (fill_partial_and_closure(pt, ufunc, ectx) == FAIL)
			goto theend;
		    tv = STACK_TV_BOT(0);
		    ++ectx->ec_stack.ga_len;
		    tv->vval.v_partial = pt;
		    tv->v_type = VAR_PARTIAL;
		    tv->v_lock = 0;
		}
		break;


	    case ISN_NEWFUNC:
		{
		    newfunc_T	*newfunc = &iptr->isn_arg.newfunc;

		    if (copy_func(newfunc->nf_lambda, newfunc->nf_global,
								 ectx) == FAIL)
			goto theend;
		}
		break;


	    case ISN_DEF:
		if (iptr->isn_arg.string == NULL)
		    list_functions(NULL);
		else
		{
		    exarg_T	ea;
		    garray_T	lines_to_free;

		    CLEAR_FIELD(ea);
		    ea.cmd = ea.arg = iptr->isn_arg.string;
		    ga_init2(&lines_to_free, sizeof(char_u *), 50);
		    define_function(&ea, NULL, &lines_to_free);
		    ga_clear_strings(&lines_to_free);
		}
		break;


	    case ISN_JUMP:
		{
		    jumpwhen_T	when = iptr->isn_arg.jump.jump_when;
		    int		error = FALSE;
		    int		jump = TRUE;

		    if (when != JUMP_ALWAYS)
		    {
			tv = STACK_TV_BOT(-1);
			if (when == JUMP_IF_COND_FALSE
				|| when == JUMP_IF_FALSE
				|| when == JUMP_IF_COND_TRUE)
			{
			    SOURCING_LNUM = iptr->isn_lnum;
			    jump = tv_get_bool_chk(tv, &error);
			    if (error)
				goto on_error;
			}
			else
			    jump = tv2bool(tv);
			if (when == JUMP_IF_FALSE
					     || when == JUMP_AND_KEEP_IF_FALSE
					     || when == JUMP_IF_COND_FALSE)
			    jump = !jump;
			if (when == JUMP_IF_FALSE || !jump)
			{

			    clear_tv(tv);
			    --ectx->ec_stack.ga_len;
			}
		    }
		    if (jump)
			ectx->ec_iidx = iptr->isn_arg.jump.jump_where;
		}
		break;


	    case ISN_JUMP_IF_ARG_SET:
		tv = STACK_TV_VAR(iptr->isn_arg.jumparg.jump_arg_off);
		if (tv->v_type != VAR_UNKNOWN
			&& !(tv->v_type == VAR_SPECIAL
					    && tv->vval.v_number == VVAL_NONE))
		    ectx->ec_iidx = iptr->isn_arg.jumparg.jump_where;
		break;


	    case ISN_FOR:
		{
		    typval_T	*ltv = STACK_TV_BOT(-1);
		    typval_T	*idxtv =
				   STACK_TV_VAR(iptr->isn_arg.forloop.for_idx);

		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    if (ltv->v_type == VAR_LIST)
		    {
			list_T *list = ltv->vval.v_list;


			++idxtv->vval.v_number;
			if (list == NULL
				       || idxtv->vval.v_number >= list->lv_len)
			{

			    ectx->ec_iidx = iptr->isn_arg.forloop.for_end;
			    may_restore_cmdmod(&ectx->ec_funclocal);
			}
			else if (list->lv_first == &range_list_item)
			{

			    tv = STACK_TV_BOT(0);
			    tv->v_type = VAR_NUMBER;
			    tv->v_lock = 0;
			    tv->vval.v_number = list_find_nr(
					     list, idxtv->vval.v_number, NULL);
			    ++ectx->ec_stack.ga_len;
			}
			else
			{
			    listitem_T *li = list_find(list,
							 idxtv->vval.v_number);

			    copy_tv(&li->li_tv, STACK_TV_BOT(0));
			    ++ectx->ec_stack.ga_len;
			}
		    }
		    else if (ltv->v_type == VAR_STRING)
		    {
			char_u	*str = ltv->vval.v_string;


			++idxtv->vval.v_number;
			if (str == NULL || str[idxtv->vval.v_number] == NUL)
			{

			    ectx->ec_iidx = iptr->isn_arg.forloop.for_end;
			    may_restore_cmdmod(&ectx->ec_funclocal);
			}
			else
			{
			    int	clen = mb_ptr2len(str + idxtv->vval.v_number);


			    tv = STACK_TV_BOT(0);
			    tv->v_type = VAR_STRING;
			    tv->vval.v_string = vim_strnsave(
					     str + idxtv->vval.v_number, clen);
			    ++ectx->ec_stack.ga_len;
			    idxtv->vval.v_number += clen - 1;
			}
		    }
		    else if (ltv->v_type == VAR_BLOB)
		    {
			blob_T	*blob = ltv->vval.v_blob;


			if (idxtv->vval.v_number == -1 && blob != NULL)
			{
			    blob_copy(blob, ltv);
			    blob_unref(blob);
			    blob = ltv->vval.v_blob;
			}


			++idxtv->vval.v_number;
			if (blob == NULL
				     || idxtv->vval.v_number >= blob_len(blob))
			{

			    ectx->ec_iidx = iptr->isn_arg.forloop.for_end;
			    may_restore_cmdmod(&ectx->ec_funclocal);
			}
			else
			{

			    tv = STACK_TV_BOT(0);
			    tv->v_type = VAR_NUMBER;
			    tv->vval.v_number = blob_get(blob,
							 idxtv->vval.v_number);
			    ++ectx->ec_stack.ga_len;
			}
		    }
		    else
		    {
			semsg(_(e_for_loop_on_str_not_supported),
						    vartype_name(ltv->v_type));
			goto theend;
		    }
		}
		break;


	    case ISN_TRY:
		{
		    trycmd_T    *trycmd = NULL;

		    if (GA_GROW_FAILS(&ectx->ec_trystack, 1))
			goto theend;
		    trycmd = ((trycmd_T *)ectx->ec_trystack.ga_data)
						     + ectx->ec_trystack.ga_len;
		    ++ectx->ec_trystack.ga_len;
		    ++trylevel;
		    CLEAR_POINTER(trycmd);
		    trycmd->tcd_frame_idx = ectx->ec_frame_idx;
		    trycmd->tcd_stack_len = ectx->ec_stack.ga_len;
		    trycmd->tcd_catch_idx =
				       iptr->isn_arg.tryref.try_ref->try_catch;
		    trycmd->tcd_finally_idx =
				     iptr->isn_arg.tryref.try_ref->try_finally;
		    trycmd->tcd_endtry_idx =
				      iptr->isn_arg.tryref.try_ref->try_endtry;
		}
		break;

	    case ISN_PUSHEXC:
		if (current_exception == NULL)
		{
		    SOURCING_LNUM = iptr->isn_lnum;
		    iemsg("Evaluating catch while current_exception is NULL");
		    goto theend;
		}
		if (GA_GROW_FAILS(&ectx->ec_stack, 1))
		    goto theend;
		tv = STACK_TV_BOT(0);
		++ectx->ec_stack.ga_len;
		tv->v_type = VAR_STRING;
		tv->v_lock = 0;
		tv->vval.v_string = vim_strsave(
					   (char_u *)current_exception->value);
		break;

	    case ISN_CATCH:
		{
		    garray_T	*trystack = &ectx->ec_trystack;

		    may_restore_cmdmod(&ectx->ec_funclocal);
		    if (trystack->ga_len > 0)
		    {
			trycmd_T    *trycmd = ((trycmd_T *)trystack->ga_data)
							+ trystack->ga_len - 1;
			trycmd->tcd_caught = TRUE;
			trycmd->tcd_did_throw = FALSE;
		    }
		    did_emsg = got_int = did_throw = FALSE;
		    force_abort = need_rethrow = FALSE;
		    catch_exception(current_exception);
		}
		break;

	    case ISN_TRYCONT:
		{
		    garray_T	*trystack = &ectx->ec_trystack;
		    trycont_T	*trycont = &iptr->isn_arg.trycont;
		    int		i;
		    trycmd_T    *trycmd;
		    int		iidx = trycont->tct_where;

		    if (trystack->ga_len < trycont->tct_levels)
		    {
			siemsg("TRYCONT: expected %d levels, found %d",
					trycont->tct_levels, trystack->ga_len);
			goto theend;
		    }


		    for (i = trycont->tct_levels; i > 0; --i)
		    {
			trycmd = ((trycmd_T *)trystack->ga_data)
							+ trystack->ga_len - i;


			trycmd->tcd_cont = iidx + 1;
			iidx = trycmd->tcd_finally_idx == 0
			    ? trycmd->tcd_endtry_idx : trycmd->tcd_finally_idx;
		    }

		    ectx->ec_iidx = iidx;
		}
		break;

	    case ISN_FINALLY:
		{
		    garray_T	*trystack = &ectx->ec_trystack;
		    trycmd_T    *trycmd = ((trycmd_T *)trystack->ga_data)
							+ trystack->ga_len - 1;


		    trycmd->tcd_finally_idx = 0;
		    break;
		}


	    case ISN_ENDTRY:
		{
		    garray_T	*trystack = &ectx->ec_trystack;

		    if (trystack->ga_len > 0)
		    {
			trycmd_T    *trycmd;

			--trystack->ga_len;
			--trylevel;
			trycmd = ((trycmd_T *)trystack->ga_data)
							    + trystack->ga_len;
			if (trycmd->tcd_did_throw)
			    did_throw = TRUE;
			if (trycmd->tcd_caught && current_exception != NULL)
			{

			    if (caught_stack == current_exception)
				caught_stack = caught_stack->caught;
			    discard_current_exception();
			}

			if (trycmd->tcd_return)
			    goto func_return;

			while (ectx->ec_stack.ga_len > trycmd->tcd_stack_len)
			{
			    --ectx->ec_stack.ga_len;
			    clear_tv(STACK_TV_BOT(0));
			}
			if (trycmd->tcd_cont != 0)


			    ectx->ec_iidx = trycmd->tcd_cont - 1;
		    }
		}
		break;

	    case ISN_THROW:
		{
		    garray_T	*trystack = &ectx->ec_trystack;

		    if (trystack->ga_len == 0 && trylevel == 0 && emsg_silent)
		    {


			tv = STACK_TV_BOT(-1);
			clear_tv(tv);
			tv->v_type = VAR_NUMBER;
			tv->vval.v_number = 0;
			goto done;
		    }
		    --ectx->ec_stack.ga_len;
		    tv = STACK_TV_BOT(0);
		    if (tv->vval.v_string == NULL
				       || *skipwhite(tv->vval.v_string) == NUL)
		    {
			vim_free(tv->vval.v_string);
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(_(e_throw_with_empty_string));
			goto theend;
		    }


		    if (trystack->ga_len > 0)
		    {
			trycmd_T    *trycmd = ((trycmd_T *)trystack->ga_data)
							+ trystack->ga_len - 1;
			if (trycmd->tcd_caught && current_exception != NULL)
			{

			    if (caught_stack == current_exception)
				caught_stack = caught_stack->caught;
			    discard_current_exception();
			    trycmd->tcd_caught = FALSE;
			}
		    }

		    if (throw_exception(tv->vval.v_string, ET_USER, NULL)
								       == FAIL)
		    {
			vim_free(tv->vval.v_string);
			goto theend;
		    }
		    did_throw = TRUE;
		}
		break;


	    case ISN_COMPAREBOOL:
	    case ISN_COMPARESPECIAL:
		{
		    typval_T	*tv1 = STACK_TV_BOT(-2);
		    typval_T	*tv2 = STACK_TV_BOT(-1);
		    varnumber_T arg1 = tv1->vval.v_number;
		    varnumber_T arg2 = tv2->vval.v_number;
		    int		res;

		    switch (iptr->isn_arg.op.op_type)
		    {
			case EXPR_EQUAL: res = arg1 == arg2; break;
			case EXPR_NEQUAL: res = arg1 != arg2; break;
			default: res = 0; break;
		    }

		    --ectx->ec_stack.ga_len;
		    tv1->v_type = VAR_BOOL;
		    tv1->vval.v_number = res ? VVAL_TRUE : VVAL_FALSE;
		}
		break;


	    case ISN_OPNR:
	    case ISN_COMPARENR:
		{
		    typval_T	*tv1 = STACK_TV_BOT(-2);
		    typval_T	*tv2 = STACK_TV_BOT(-1);
		    varnumber_T arg1 = tv1->vval.v_number;
		    varnumber_T arg2 = tv2->vval.v_number;
		    varnumber_T res = 0;
		    int		div_zero = FALSE;

		    switch (iptr->isn_arg.op.op_type)
		    {
			case EXPR_MULT: res = arg1 * arg2; break;
			case EXPR_DIV:  if (arg2 == 0)
					    div_zero = TRUE;
					else
					    res = arg1 / arg2;
					break;
			case EXPR_REM:  if (arg2 == 0)
					    div_zero = TRUE;
					else
					    res = arg1 % arg2;
					break;
			case EXPR_SUB: res = arg1 - arg2; break;
			case EXPR_ADD: res = arg1 + arg2; break;

			case EXPR_EQUAL: res = arg1 == arg2; break;
			case EXPR_NEQUAL: res = arg1 != arg2; break;
			case EXPR_GREATER: res = arg1 > arg2; break;
			case EXPR_GEQUAL: res = arg1 >= arg2; break;
			case EXPR_SMALLER: res = arg1 < arg2; break;
			case EXPR_SEQUAL: res = arg1 <= arg2; break;
			default: break;
		    }

		    --ectx->ec_stack.ga_len;
		    if (iptr->isn_type == ISN_COMPARENR)
		    {
			tv1->v_type = VAR_BOOL;
			tv1->vval.v_number = res ? VVAL_TRUE : VVAL_FALSE;
		    }
		    else
			tv1->vval.v_number = res;
		    if (div_zero)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(_(e_divide_by_zero));
			goto on_error;
		    }
		}
		break;


	    case ISN_OPFLOAT:
	    case ISN_COMPAREFLOAT:
#ifdef FEAT_FLOAT
		{
		    typval_T	*tv1 = STACK_TV_BOT(-2);
		    typval_T	*tv2 = STACK_TV_BOT(-1);
		    float_T	arg1 = tv1->vval.v_float;
		    float_T	arg2 = tv2->vval.v_float;
		    float_T	res = 0;
		    int		cmp = FALSE;

		    switch (iptr->isn_arg.op.op_type)
		    {
			case EXPR_MULT: res = arg1 * arg2; break;
			case EXPR_DIV: res = arg1 / arg2; break;
			case EXPR_SUB: res = arg1 - arg2; break;
			case EXPR_ADD: res = arg1 + arg2; break;

			case EXPR_EQUAL: cmp = arg1 == arg2; break;
			case EXPR_NEQUAL: cmp = arg1 != arg2; break;
			case EXPR_GREATER: cmp = arg1 > arg2; break;
			case EXPR_GEQUAL: cmp = arg1 >= arg2; break;
			case EXPR_SMALLER: cmp = arg1 < arg2; break;
			case EXPR_SEQUAL: cmp = arg1 <= arg2; break;
			default: cmp = 0; break;
		    }
		    --ectx->ec_stack.ga_len;
		    if (iptr->isn_type == ISN_COMPAREFLOAT)
		    {
			tv1->v_type = VAR_BOOL;
			tv1->vval.v_number = cmp ? VVAL_TRUE : VVAL_FALSE;
		    }
		    else
			tv1->vval.v_float = res;
		}
#endif
		break;

	    case ISN_COMPARELIST:
	    case ISN_COMPAREDICT:
	    case ISN_COMPAREFUNC:
	    case ISN_COMPARESTRING:
	    case ISN_COMPAREBLOB:
		{
		    typval_T	*tv1 = STACK_TV_BOT(-2);
		    typval_T	*tv2 = STACK_TV_BOT(-1);
		    exprtype_T	exprtype = iptr->isn_arg.op.op_type;
		    int		ic = iptr->isn_arg.op.op_ic;
		    int		res = FALSE;
		    int		status = OK;

		    SOURCING_LNUM = iptr->isn_lnum;
		    if (iptr->isn_type == ISN_COMPARELIST)
		    {
			status = typval_compare_list(tv1, tv2,
							   exprtype, ic, &res);
		    }
		    else if (iptr->isn_type == ISN_COMPAREDICT)
		    {
			status = typval_compare_dict(tv1, tv2,
							   exprtype, ic, &res);
		    }
		    else if (iptr->isn_type == ISN_COMPAREFUNC)
		    {
			status = typval_compare_func(tv1, tv2,
							   exprtype, ic, &res);
		    }
		    else if (iptr->isn_type == ISN_COMPARESTRING)
		    {
			status = typval_compare_string(tv1, tv2,
							   exprtype, ic, &res);
		    }
		    else
		    {
			status = typval_compare_blob(tv1, tv2, exprtype, &res);
		    }
		    --ectx->ec_stack.ga_len;
		    clear_tv(tv1);
		    clear_tv(tv2);
		    tv1->v_type = VAR_BOOL;
		    tv1->vval.v_number = res ? VVAL_TRUE : VVAL_FALSE;
		    if (status == FAIL)
			goto theend;
		}
		break;

	    case ISN_COMPAREANY:
		{
		    typval_T	*tv1 = STACK_TV_BOT(-2);
		    typval_T	*tv2 = STACK_TV_BOT(-1);
		    exprtype_T	exprtype = iptr->isn_arg.op.op_type;
		    int		ic = iptr->isn_arg.op.op_ic;
		    int		status;

		    SOURCING_LNUM = iptr->isn_lnum;
		    status = typval_compare(tv1, tv2, exprtype, ic);
		    clear_tv(tv2);
		    --ectx->ec_stack.ga_len;
		    if (status == FAIL)
			goto theend;
		}
		break;

	    case ISN_ADDLIST:
	    case ISN_ADDBLOB:
		{
		    typval_T *tv1 = STACK_TV_BOT(-2);
		    typval_T *tv2 = STACK_TV_BOT(-1);


		    if (iptr->isn_type == ISN_ADDLIST)
		    {
			if (iptr->isn_arg.op.op_type == EXPR_APPEND
						   && tv1->vval.v_list != NULL)
			    list_extend(tv1->vval.v_list, tv2->vval.v_list,
									 NULL);
			else
			    eval_addlist(tv1, tv2);
		    }
		    else
			eval_addblob(tv1, tv2);
		    clear_tv(tv2);
		    --ectx->ec_stack.ga_len;
		}
		break;

	    case ISN_LISTAPPEND:
		{
		    typval_T	*tv1 = STACK_TV_BOT(-2);
		    typval_T	*tv2 = STACK_TV_BOT(-1);
		    list_T	*l = tv1->vval.v_list;


		    SOURCING_LNUM = iptr->isn_lnum;
		    if (l == NULL)
		    {
			emsg(_(e_cannot_add_to_null_list));
			goto on_error;
		    }
		    if (value_check_lock(l->lv_lock, NULL, FALSE))
			goto on_error;
		    if (list_append_tv(l, tv2) == FAIL)
			goto theend;
		    clear_tv(tv2);
		    --ectx->ec_stack.ga_len;
		}
		break;

	    case ISN_BLOBAPPEND:
		{
		    typval_T	*tv1 = STACK_TV_BOT(-2);
		    typval_T	*tv2 = STACK_TV_BOT(-1);
		    blob_T	*b = tv1->vval.v_blob;
		    int		error = FALSE;
		    varnumber_T n;


		    if (b == NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(_(e_cannot_add_to_null_blob));
			goto on_error;
		    }
		    n = tv_get_number_chk(tv2, &error);
		    if (error)
			goto on_error;
		    ga_append(&b->bv_ga, (int)n);
		    --ectx->ec_stack.ga_len;
		}
		break;


	    case ISN_OPANY:
		{
		    typval_T	*tv1 = STACK_TV_BOT(-2);
		    typval_T	*tv2 = STACK_TV_BOT(-1);
		    varnumber_T	n1, n2;
#ifdef FEAT_FLOAT
		    float_T	f1 = 0, f2 = 0;
#endif
		    int		error = FALSE;

		    if (iptr->isn_arg.op.op_type == EXPR_ADD)
		    {
			if (tv1->v_type == VAR_LIST && tv2->v_type == VAR_LIST)
			{
			    eval_addlist(tv1, tv2);
			    clear_tv(tv2);
			    --ectx->ec_stack.ga_len;
			    break;
			}
			else if (tv1->v_type == VAR_BLOB
						    && tv2->v_type == VAR_BLOB)
			{
			    eval_addblob(tv1, tv2);
			    clear_tv(tv2);
			    --ectx->ec_stack.ga_len;
			    break;
			}
		    }
#ifdef FEAT_FLOAT
		    if (tv1->v_type == VAR_FLOAT)
		    {
			f1 = tv1->vval.v_float;
			n1 = 0;
		    }
		    else
#endif
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			n1 = tv_get_number_chk(tv1, &error);
			if (error)
			    goto on_error;
#ifdef FEAT_FLOAT
			if (tv2->v_type == VAR_FLOAT)
			    f1 = n1;
#endif
		    }
#ifdef FEAT_FLOAT
		    if (tv2->v_type == VAR_FLOAT)
		    {
			f2 = tv2->vval.v_float;
			n2 = 0;
		    }
		    else
#endif
		    {
			n2 = tv_get_number_chk(tv2, &error);
			if (error)
			    goto on_error;
#ifdef FEAT_FLOAT
			if (tv1->v_type == VAR_FLOAT)
			    f2 = n2;
#endif
		    }
#ifdef FEAT_FLOAT

		    if (tv1->v_type == VAR_FLOAT || tv2->v_type == VAR_FLOAT)
		    {
			switch (iptr->isn_arg.op.op_type)
			{
			    case EXPR_MULT: f1 = f1 * f2; break;
			    case EXPR_DIV:  f1 = f1 / f2; break;
			    case EXPR_SUB:  f1 = f1 - f2; break;
			    case EXPR_ADD:  f1 = f1 + f2; break;
			    default: SOURCING_LNUM = iptr->isn_lnum;
				     emsg(_(e_cannot_use_percent_with_float));
				     goto on_error;
			}
			clear_tv(tv1);
			clear_tv(tv2);
			tv1->v_type = VAR_FLOAT;
			tv1->vval.v_float = f1;
			--ectx->ec_stack.ga_len;
		    }
		    else
#endif
		    {
			int failed = FALSE;

			switch (iptr->isn_arg.op.op_type)
			{
			    case EXPR_MULT: n1 = n1 * n2; break;
			    case EXPR_DIV:  n1 = num_divide(n1, n2, &failed);
					    if (failed)
						goto on_error;
					    break;
			    case EXPR_SUB:  n1 = n1 - n2; break;
			    case EXPR_ADD:  n1 = n1 + n2; break;
			    default:	    n1 = num_modulus(n1, n2, &failed);
					    if (failed)
						goto on_error;
					    break;
			}
			clear_tv(tv1);
			clear_tv(tv2);
			tv1->v_type = VAR_NUMBER;
			tv1->vval.v_number = n1;
			--ectx->ec_stack.ga_len;
		    }
		}
		break;

	    case ISN_CONCAT:
		{
		    char_u *str1 = STACK_TV_BOT(-2)->vval.v_string;
		    char_u *str2 = STACK_TV_BOT(-1)->vval.v_string;
		    char_u *res;

		    res = concat_str(str1, str2);
		    clear_tv(STACK_TV_BOT(-2));
		    clear_tv(STACK_TV_BOT(-1));
		    --ectx->ec_stack.ga_len;
		    STACK_TV_BOT(-1)->vval.v_string = res;
		}
		break;

	    case ISN_STRINDEX:
	    case ISN_STRSLICE:
		{
		    int		is_slice = iptr->isn_type == ISN_STRSLICE;
		    varnumber_T	n1 = 0, n2;
		    char_u	*res;


		    if (is_slice)
		    {
			tv = STACK_TV_BOT(-2);
			n1 = tv->vval.v_number;
		    }

		    tv = STACK_TV_BOT(-1);
		    n2 = tv->vval.v_number;

		    ectx->ec_stack.ga_len -= is_slice ? 2 : 1;
		    tv = STACK_TV_BOT(-1);
		    if (is_slice)

			res = string_slice(tv->vval.v_string, n1, n2, FALSE);
		    else


			res = char_from_string(tv->vval.v_string, n2);
		    vim_free(tv->vval.v_string);
		    tv->vval.v_string = res;
		}
		break;

	    case ISN_LISTINDEX:
	    case ISN_LISTSLICE:
	    case ISN_BLOBINDEX:
	    case ISN_BLOBSLICE:
		{
		    int		is_slice = iptr->isn_type == ISN_LISTSLICE
					    || iptr->isn_type == ISN_BLOBSLICE;
		    int		is_blob = iptr->isn_type == ISN_BLOBINDEX
					    || iptr->isn_type == ISN_BLOBSLICE;
		    varnumber_T	n1, n2;
		    typval_T	*val_tv;


		    val_tv = is_slice ? STACK_TV_BOT(-3) : STACK_TV_BOT(-2);

		    tv = STACK_TV_BOT(-1);
		    n1 = n2 = tv->vval.v_number;
		    clear_tv(tv);

		    if (is_slice)
		    {
			tv = STACK_TV_BOT(-2);
			n1 = tv->vval.v_number;
			clear_tv(tv);
		    }

		    ectx->ec_stack.ga_len -= is_slice ? 2 : 1;
		    tv = STACK_TV_BOT(-1);
		    SOURCING_LNUM = iptr->isn_lnum;
		    if (is_blob)
		    {
			if (blob_slice_or_index(val_tv->vval.v_blob, is_slice,
						    n1, n2, FALSE, tv) == FAIL)
			    goto on_error;
		    }
		    else
		    {
			if (list_slice_or_index(val_tv->vval.v_list, is_slice,
					      n1, n2, FALSE, tv, TRUE) == FAIL)
			    goto on_error;
		    }
		}
		break;

	    case ISN_ANYINDEX:
	    case ISN_ANYSLICE:
		{
		    int		is_slice = iptr->isn_type == ISN_ANYSLICE;
		    typval_T	*var1, *var2;
		    int		res;


		    tv = is_slice ? STACK_TV_BOT(-3) : STACK_TV_BOT(-2);
		    SOURCING_LNUM = iptr->isn_lnum;
		    if (check_can_index(tv, TRUE, TRUE) == FAIL)
			goto on_error;
		    var1 = is_slice ? STACK_TV_BOT(-2) : STACK_TV_BOT(-1);
		    var2 = is_slice ? STACK_TV_BOT(-1) : NULL;
		    res = eval_index_inner(tv, is_slice, var1, var2,
							FALSE, NULL, -1, TRUE);
		    clear_tv(var1);
		    if (is_slice)
			clear_tv(var2);
		    ectx->ec_stack.ga_len -= is_slice ? 2 : 1;
		    if (res == FAIL)
			goto on_error;
		}
		break;

	    case ISN_SLICE:
		{
		    list_T	*list;
		    int		count = iptr->isn_arg.number;


		    tv = STACK_TV_BOT(-1);
		    list = tv->vval.v_list;


		    if (list != NULL && list->lv_len >= count)
		    {
			list_T	*newlist = list_slice(list,
						      count, list->lv_len - 1);

			if (newlist != NULL)
			{
			    list_unref(list);
			    tv->vval.v_list = newlist;
			    ++newlist->lv_refcount;
			}
		    }
		}
		break;

	    case ISN_GETITEM:
		{
		    listitem_T	*li;
		    getitem_T	*gi = &iptr->isn_arg.getitem;


		    tv = STACK_TV_BOT(-1 - gi->gi_with_op);
		    li = list_find(tv->vval.v_list, gi->gi_index);

		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    ++ectx->ec_stack.ga_len;
		    copy_tv(&li->li_tv, STACK_TV_BOT(-1));


		    ectx->ec_where.wt_index = gi->gi_index + 1;
		    ectx->ec_where.wt_variable = TRUE;
		}
		break;

	    case ISN_MEMBER:
		{
		    dict_T	*dict;
		    char_u	*key;
		    dictitem_T	*di;


		    tv = STACK_TV_BOT(-2);

		    dict = tv->vval.v_dict;

		    tv = STACK_TV_BOT(-1);

		    key = tv->vval.v_string;
		    if (key == NULL)
			key = (char_u *)"";

		    if ((di = dict_find(dict, key, -1)) == NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			semsg(_(e_key_not_present_in_dictionary), key);


			clear_tv(tv);
			--ectx->ec_stack.ga_len;
			tv = STACK_TV_BOT(-1);
			(void) dict_stack_save(tv);
			tv->v_type = VAR_NUMBER;
			tv->vval.v_number = 0;
			goto on_fatal_error;
		    }
		    clear_tv(tv);
		    --ectx->ec_stack.ga_len;


		    tv = STACK_TV_BOT(-1);
		    if (dict_stack_save(tv) == FAIL)
			goto on_fatal_error;
		    copy_tv(&di->di_tv, tv);
		}
		break;


	    case ISN_STRINGMEMBER:
		{
		    dict_T	*dict;
		    dictitem_T	*di;

		    tv = STACK_TV_BOT(-1);
		    if (tv->v_type != VAR_DICT || tv->vval.v_dict == NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(_(e_dictionary_required));
			goto on_error;
		    }
		    dict = tv->vval.v_dict;

		    if ((di = dict_find(dict, iptr->isn_arg.string, -1))
								       == NULL)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			semsg(_(e_key_not_present_in_dictionary), iptr->isn_arg.string);
			goto on_error;
		    }


		    if (dict_stack_save(tv) == FAIL)
			goto on_fatal_error;

		    copy_tv(&di->di_tv, tv);
		}
		break;

	    case ISN_CLEARDICT:
		dict_stack_drop();
		break;

	    case ISN_USEDICT:
		{
		    typval_T *dict_tv = dict_stack_get_tv();


		    tv = STACK_TV_BOT(-1);
		    if (dict_tv != NULL
			    && dict_tv->v_type == VAR_DICT
			    && dict_tv->vval.v_dict != NULL
			    && (tv->v_type == VAR_FUNC
				|| (tv->v_type == VAR_PARTIAL
				    && (tv->vval.v_partial->pt_auto
				     || tv->vval.v_partial->pt_dict == NULL))))
		    dict_tv->vval.v_dict =
					make_partial(dict_tv->vval.v_dict, tv);
		    dict_stack_drop();
		}
		break;

	    case ISN_NEGATENR:
		tv = STACK_TV_BOT(-1);
		if (tv->v_type != VAR_NUMBER
#ifdef FEAT_FLOAT
			&& tv->v_type != VAR_FLOAT
#endif
			)
		{
		    SOURCING_LNUM = iptr->isn_lnum;
		    emsg(_(e_number_expected));
		    goto on_error;
		}
#ifdef FEAT_FLOAT
		if (tv->v_type == VAR_FLOAT)
		    tv->vval.v_float = -tv->vval.v_float;
		else
#endif
		    tv->vval.v_number = -tv->vval.v_number;
		break;

	    case ISN_CHECKNR:
		{
		    int		error = FALSE;

		    tv = STACK_TV_BOT(-1);
		    SOURCING_LNUM = iptr->isn_lnum;
		    if (check_not_string(tv) == FAIL)
			goto on_error;
		    (void)tv_get_number_chk(tv, &error);
		    if (error)
			goto on_error;
		}
		break;

	    case ISN_CHECKTYPE:
		{
		    checktype_T *ct = &iptr->isn_arg.type;

		    tv = STACK_TV_BOT((int)ct->ct_off);
		    SOURCING_LNUM = iptr->isn_lnum;
		    if (!ectx->ec_where.wt_variable)
			ectx->ec_where.wt_index = ct->ct_arg_idx;
		    if (check_typval_type(ct->ct_type, tv, ectx->ec_where)
								       == FAIL)
			goto on_error;
		    if (!ectx->ec_where.wt_variable)
			ectx->ec_where.wt_index = 0;


		    if (tv->v_type == VAR_NUMBER
			    && ct->ct_type->tt_type == VAR_BOOL
			    && (tv->vval.v_number == 0
						|| tv->vval.v_number == 1))
		    {
			tv->v_type = VAR_BOOL;
			tv->vval.v_number = tv->vval.v_number
						      ? VVAL_TRUE : VVAL_FALSE;
		    }
		}
		break;

	    case ISN_CHECKLEN:
		{
		    int	    min_len = iptr->isn_arg.checklen.cl_min_len;
		    list_T  *list = NULL;

		    tv = STACK_TV_BOT(-1);
		    if (tv->v_type == VAR_LIST)
			    list = tv->vval.v_list;
		    if (list == NULL || list->lv_len < min_len
			    || (list->lv_len > min_len
					&& !iptr->isn_arg.checklen.cl_more_OK))
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			semsg(_(e_expected_nr_items_but_got_nr),
				     min_len, list == NULL ? 0 : list->lv_len);
			goto on_error;
		    }
		}
		break;

	    case ISN_SETTYPE:
		{
		    checktype_T *ct = &iptr->isn_arg.type;

		    tv = STACK_TV_BOT(-1);
		    if (tv->v_type == VAR_DICT && tv->vval.v_dict != NULL)
		    {
			free_type(tv->vval.v_dict->dv_type);
			tv->vval.v_dict->dv_type = alloc_type(ct->ct_type);
		    }
		    else if (tv->v_type == VAR_LIST && tv->vval.v_list != NULL)
		    {
			free_type(tv->vval.v_list->lv_type);
			tv->vval.v_list->lv_type = alloc_type(ct->ct_type);
		    }
		}
		break;

	    case ISN_2BOOL:
	    case ISN_COND2BOOL:
		{
		    int n;
		    int error = FALSE;

		    if (iptr->isn_type == ISN_2BOOL)
		    {
			tv = STACK_TV_BOT(iptr->isn_arg.tobool.offset);
			n = tv2bool(tv);
			if (iptr->isn_arg.tobool.invert)
			    n = !n;
		    }
		    else
		    {
			tv = STACK_TV_BOT(-1);
			SOURCING_LNUM = iptr->isn_lnum;
			n = tv_get_bool_chk(tv, &error);
			if (error)
			    goto on_error;
		    }
		    clear_tv(tv);
		    tv->v_type = VAR_BOOL;
		    tv->vval.v_number = n ? VVAL_TRUE : VVAL_FALSE;
		}
		break;

	    case ISN_2STRING:
	    case ISN_2STRING_ANY:
		SOURCING_LNUM = iptr->isn_lnum;
		if (do_2string(STACK_TV_BOT(iptr->isn_arg.tostring.offset),
				iptr->isn_type == ISN_2STRING_ANY,
				      iptr->isn_arg.tostring.tolerant) == FAIL)
			    goto on_error;
		break;

	    case ISN_RANGE:
		{
		    exarg_T	ea;
		    char	*errormsg;

		    ea.line2 = 0;
		    ea.addr_count = 0;
		    ea.addr_type = ADDR_LINES;
		    ea.cmd = iptr->isn_arg.string;
		    ea.skip = FALSE;
		    if (parse_cmd_address(&ea, &errormsg, FALSE) == FAIL)
			goto on_error;

		    if (GA_GROW_FAILS(&ectx->ec_stack, 1))
			goto theend;
		    ++ectx->ec_stack.ga_len;
		    tv = STACK_TV_BOT(-1);
		    tv->v_type = VAR_NUMBER;
		    tv->v_lock = 0;
		    if (ea.addr_count == 0)
			tv->vval.v_number = curwin->w_cursor.lnum;
		    else
			tv->vval.v_number = ea.line2;
		}
		break;

	    case ISN_PUT:
		{
		    int		regname = iptr->isn_arg.put.put_regname;
		    linenr_T	lnum = iptr->isn_arg.put.put_lnum;
		    char_u	*expr = NULL;
		    int		dir = FORWARD;

		    if (lnum < -2)
		    {

			tv = STACK_TV_BOT(-1);
			curwin->w_cursor.lnum = tv->vval.v_number;
			if (lnum == LNUM_VARIABLE_RANGE_ABOVE)
			    dir = BACKWARD;
			--ectx->ec_stack.ga_len;
		    }
		    else if (lnum == -2)

			dir = BACKWARD;
		    else if (lnum >= 0)
			curwin->w_cursor.lnum = iptr->isn_arg.put.put_lnum;

		    if (regname == '=')
		    {
			tv = STACK_TV_BOT(-1);
			if (tv->v_type == VAR_STRING)
			    expr = tv->vval.v_string;
			else
			{
			    expr = typval2string(tv, TRUE);
			    clear_tv(tv);
			}
			--ectx->ec_stack.ga_len;
		    }
		    check_cursor();
		    do_put(regname, expr, dir, 1L, PUT_LINE|PUT_CURSLINE);
		    vim_free(expr);
		}
		break;

	    case ISN_CMDMOD:
		ectx->ec_funclocal.floc_save_cmdmod = cmdmod;
		ectx->ec_funclocal.floc_restore_cmdmod = TRUE;
		ectx->ec_funclocal.floc_restore_cmdmod_stacklen =
							 ectx->ec_stack.ga_len;
		cmdmod = *iptr->isn_arg.cmdmod.cf_cmdmod;
		apply_cmdmod(&cmdmod);
		break;

	    case ISN_CMDMOD_REV:

		cmdmod.cmod_filter_regmatch.regprog = NULL;
		undo_cmdmod(&cmdmod);
		cmdmod = ectx->ec_funclocal.floc_save_cmdmod;
		ectx->ec_funclocal.floc_restore_cmdmod = FALSE;
		break;

	    case ISN_UNPACK:
		{
		    int		count = iptr->isn_arg.unpack.unp_count;
		    int		semicolon = iptr->isn_arg.unpack.unp_semicolon;
		    list_T	*l;
		    listitem_T	*li;
		    int		i;


		    tv = STACK_TV_BOT(-1);
		    if (tv->v_type != VAR_LIST)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(_(e_for_argument_must_be_sequence_of_lists));
			goto on_error;
		    }
		    l = tv->vval.v_list;
		    if (l == NULL
				|| l->lv_len < (semicolon ? count - 1 : count))
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(_(e_list_value_does_not_have_enough_items));
			goto on_error;
		    }
		    else if (!semicolon && l->lv_len > count)
		    {
			SOURCING_LNUM = iptr->isn_lnum;
			emsg(_(e_list_value_has_more_items_than_targets));
			goto on_error;
		    }

		    CHECK_LIST_MATERIALIZE(l);
		    if (GA_GROW_FAILS(&ectx->ec_stack, count - 1))
			goto theend;
		    ectx->ec_stack.ga_len += count - 1;


		    if (semicolon)
		    {
			list_T	*rem_list =
				  list_alloc_with_items(l->lv_len - count + 1);

			if (rem_list == NULL)
			    goto theend;
			tv = STACK_TV_BOT(-count);
			tv->vval.v_list = rem_list;
			++rem_list->lv_refcount;
			tv->v_lock = 0;
			li = l->lv_first;
			for (i = 0; i < count - 1; ++i)
			    li = li->li_next;
			for (i = 0; li != NULL; ++i)
			{
			    list_set_item(rem_list, i, &li->li_tv);
			    li = li->li_next;
			}
			--count;
		    }


		    li = l->lv_first;
		    for (i = 0; i < count; ++i)
		    {
			tv = STACK_TV_BOT(-i - 1);
			copy_tv(&li->li_tv, tv);
			li = li->li_next;
		    }

		    list_unref(l);
		}
		break;

	    case ISN_PROF_START:
	    case ISN_PROF_END:
		{
#ifdef FEAT_PROFILE
		    funccall_T cookie;
		    ufunc_T	    *cur_ufunc =
				    (((dfunc_T *)def_functions.ga_data)
					       + ectx->ec_dfunc_idx)->df_ufunc;

		    cookie.func = cur_ufunc;
		    if (iptr->isn_type == ISN_PROF_START)
		    {
			func_line_start(&cookie, iptr->isn_lnum);

			func_line_exec(&cookie);
		    }
		    else
			func_line_end(&cookie);
#endif
		}
		break;

	    case ISN_DEBUG:
		handle_debug(iptr, ectx);
		break;

	    case ISN_SHUFFLE:
		{
		    typval_T	tmp_tv;
		    int		item = iptr->isn_arg.shuffle.shfl_item;
		    int		up = iptr->isn_arg.shuffle.shfl_up;

		    tmp_tv = *STACK_TV_BOT(-item);
		    for ( ; up > 0 && item > 1; --up)
		    {
			*STACK_TV_BOT(-item) = *STACK_TV_BOT(-item + 1);
			--item;
		    }
		    *STACK_TV_BOT(-item) = tmp_tv;
		}
		break;

	    case ISN_DROP:
		--ectx->ec_stack.ga_len;
		clear_tv(STACK_TV_BOT(0));
		ectx->ec_where.wt_index = 0;
		ectx->ec_where.wt_variable = FALSE;
		break;
	}
	continue;

func_return:


	if (ectx->ec_frame_idx == ectx->ec_initial_frame_idx)
	    goto done;

	if (func_return(ectx) == FAIL)

	    goto theend;
	continue;

on_error:


	if (did_emsg_cumul + did_emsg == ectx->ec_did_emsg_before
					   && emsg_silent && did_emsg_def == 0)
	{


	    if (ectx->ec_funclocal.floc_restore_cmdmod)
	    {
		while (ectx->ec_stack.ga_len
			     > ectx->ec_funclocal.floc_restore_cmdmod_stacklen)
		{
		    --ectx->ec_stack.ga_len;
		    clear_tv(STACK_TV_BOT(0));
		}
		while (ectx->ec_instr[ectx->ec_iidx].isn_type != ISN_CMDMOD_REV)
		    ++ectx->ec_iidx;
	    }
	    continue;
	}
on_fatal_error:


	if (trylevel <= ectx->ec_trylevel_at_start)
	    goto theend;
    }

done:
    ret = OK;
theend:
    dict_stack_clear(dict_stack_len_at_start);
    ectx->ec_trylevel_at_start = save_trylevel_at_start;
    return ret;
}
