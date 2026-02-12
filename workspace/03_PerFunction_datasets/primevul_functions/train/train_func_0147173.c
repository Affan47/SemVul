call_dfunc(
	int		cdf_idx,
	partial_T	*pt,
	int		argcount_arg,
	ectx_T		*ectx)
{
    int		argcount = argcount_arg;
    dfunc_T	*dfunc = ((dfunc_T *)def_functions.ga_data) + cdf_idx;
    ufunc_T	*ufunc = dfunc->df_ufunc;
    int		did_emsg_before = did_emsg_cumul + did_emsg;
    int		arg_to_add;
    int		vararg_count = 0;
    int		varcount;
    int		idx;
    estack_T	*entry;
    funclocal_T	*floc = NULL;
    int		res = OK;

    if (dfunc->df_deleted)
    {

	emsg_funcname(e_function_was_deleted_str,
		dfunc->df_name == NULL ? (char_u *)"unknown" : dfunc->df_name);
	return FAIL;
    }

#ifdef FEAT_PROFILE
    if (do_profiling == PROF_YES)
    {
	if (GA_GROW_OK(&profile_info_ga, 1))
	{
	    profinfo_T *info = ((profinfo_T *)profile_info_ga.ga_data)
						      + profile_info_ga.ga_len;
	    ++profile_info_ga.ga_len;
	    CLEAR_POINTER(info);
	    profile_may_start_func(info, ufunc,
			(((dfunc_T *)def_functions.ga_data)
					      + ectx->ec_dfunc_idx)->df_ufunc);
	}
    }
#endif


    update_has_breakpoint(ufunc);


    if (func_needs_compiling(ufunc, COMPILE_TYPE(ufunc)))
    {
	res = compile_def_function(ufunc, FALSE, COMPILE_TYPE(ufunc), NULL);


	dfunc = ((dfunc_T *)def_functions.ga_data) + cdf_idx;
    }
    if (res == FAIL || INSTRUCTIONS(dfunc) == NULL)
    {
	if (did_emsg_cumul + did_emsg == did_emsg_before)
	    semsg(_(e_function_is_not_compiled_str),
						   printable_func_name(ufunc));
	return FAIL;
    }

    if (ufunc->uf_va_name != NULL)
    {


	vararg_count = argcount - ufunc->uf_args.ga_len;
	if (vararg_count < 0)
	    vararg_count = 0;
	else
	    argcount -= vararg_count;
	if (exe_newlist(vararg_count, ectx) == FAIL)
	    return FAIL;

	vararg_count = 1;
    }

    arg_to_add = ufunc->uf_args.ga_len - argcount;
    if (arg_to_add < 0)
    {
	if (arg_to_add == -1)
	    emsg(_(e_one_argument_too_many));
	else
	    semsg(_(e_nr_arguments_too_many), -arg_to_add);
	return FAIL;
    }


    varcount = dfunc->df_varcount + dfunc->df_has_closure;
    if (GA_GROW_FAILS(&ectx->ec_stack, arg_to_add + STACK_FRAME_SIZE + varcount))
	return FAIL;


    if (funcdepth_increment() == FAIL)
	return FAIL;
    ++ex_nesting_level;


    if (ectx->ec_funclocal.floc_restore_cmdmod)
    {
	floc = ALLOC_ONE(funclocal_T);
	if (floc == NULL)
	    return FAIL;
	*floc = ectx->ec_funclocal;
	ectx->ec_funclocal.floc_restore_cmdmod = FALSE;
    }


    if (vararg_count > 0 && arg_to_add > 0)
	*STACK_TV_BOT(arg_to_add - 1) = *STACK_TV_BOT(-1);


    for (idx = 0; idx < arg_to_add; ++idx)
	STACK_TV_BOT(idx - vararg_count)->v_type = VAR_UNKNOWN;
    ectx->ec_stack.ga_len += arg_to_add;


    STACK_TV_BOT(STACK_FRAME_FUNC_OFF)->vval.v_number = ectx->ec_dfunc_idx;
    STACK_TV_BOT(STACK_FRAME_IIDX_OFF)->vval.v_number = ectx->ec_iidx;
    STACK_TV_BOT(STACK_FRAME_INSTR_OFF)->vval.v_string = (void *)ectx->ec_instr;
    STACK_TV_BOT(STACK_FRAME_OUTER_OFF)->vval.v_string =
						    (void *)ectx->ec_outer_ref;
    STACK_TV_BOT(STACK_FRAME_FUNCLOCAL_OFF)->vval.v_string = (void *)floc;
    STACK_TV_BOT(STACK_FRAME_IDX_OFF)->vval.v_number = ectx->ec_frame_idx;
    ectx->ec_frame_idx = ectx->ec_stack.ga_len;


    for (idx = 0; idx < dfunc->df_varcount; ++idx)
    {
	typval_T *tv = STACK_TV_BOT(STACK_FRAME_SIZE + idx);

	tv->v_type = VAR_NUMBER;
	tv->vval.v_number = 0;
    }
    if (dfunc->df_has_closure)
    {
	typval_T *tv = STACK_TV_BOT(STACK_FRAME_SIZE + dfunc->df_varcount);

	tv->v_type = VAR_NUMBER;
	tv->vval.v_number = 0;
    }
    ectx->ec_stack.ga_len += STACK_FRAME_SIZE + varcount;

    if (pt != NULL || ufunc->uf_partial != NULL
					     || (ufunc->uf_flags & FC_CLOSURE))
    {
	outer_ref_T *ref = ALLOC_CLEAR_ONE(outer_ref_T);

	if (ref == NULL)
	    return FAIL;
	if (pt != NULL)
	{
	    ref->or_outer = &pt->pt_outer;
	    ++pt->pt_refcount;
	    ref->or_partial = pt;
	}
	else if (ufunc->uf_partial != NULL)
	{
	    ref->or_outer = &ufunc->uf_partial->pt_outer;
	    ++ufunc->uf_partial->pt_refcount;
	    ref->or_partial = ufunc->uf_partial;
	}
	else
	{
	    ref->or_outer = ALLOC_CLEAR_ONE(outer_T);
	    if (unlikely(ref->or_outer == NULL))
	    {
		vim_free(ref);
		return FAIL;
	    }
	    ref->or_outer_allocated = TRUE;
	    ref->or_outer->out_stack = &ectx->ec_stack;
	    ref->or_outer->out_frame_idx = ectx->ec_frame_idx;
	    if (ectx->ec_outer_ref != NULL)
		ref->or_outer->out_up = ectx->ec_outer_ref->or_outer;
	}
	ectx->ec_outer_ref = ref;
    }
    else
	ectx->ec_outer_ref = NULL;

    ++ufunc->uf_calls;


    ectx->ec_dfunc_idx = cdf_idx;
    ectx->ec_instr = INSTRUCTIONS(dfunc);
    entry = estack_push_ufunc(ufunc, 1);
    if (entry != NULL)
    {


	entry->es_save_sctx = current_sctx;
	current_sctx = ufunc->uf_script_ctx;
    }


    ectx->ec_iidx = 0;

    return OK;
}
