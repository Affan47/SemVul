compile_try(char_u *arg, cctx_T *cctx)
{
    garray_T	*instr = &cctx->ctx_instr;
    scope_T	*try_scope;
    scope_T	*scope;

    if (misplaced_cmdmod(cctx))
	return NULL;


    try_scope = new_scope(cctx, TRY_SCOPE);
    if (try_scope == NULL)
	return NULL;

    if (cctx->ctx_skip != SKIP_YES)
    {
	isn_T	*isn;


	try_scope->se_u.se_try.ts_try_label = instr->ga_len;
	if ((isn = generate_instr(cctx, ISN_TRY)) == NULL)
	    return NULL;
	isn->isn_arg.tryref.try_ref = ALLOC_CLEAR_ONE(tryref_T);
	if (isn->isn_arg.tryref.try_ref == NULL)
	    return NULL;
    }


    scope = new_scope(cctx, BLOCK_SCOPE);
    if (scope == NULL)
	return NULL;

    return arg;
}
