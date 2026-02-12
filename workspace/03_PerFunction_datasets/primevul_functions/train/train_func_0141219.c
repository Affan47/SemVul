compile_break(char_u *arg, cctx_T *cctx)
{
    scope_T	*scope = cctx->ctx_scope;
    int		try_scopes = 0;
    endlabel_T	**el;

    for (;;)
    {
	if (scope == NULL)
	{
	    emsg(_(e_break_without_while_or_for));
	    return NULL;
	}
	if (scope->se_type == FOR_SCOPE)
	{
	    el = &scope->se_u.se_for.fs_end_label;
	    break;
	}
	if (scope->se_type == WHILE_SCOPE)
	{
	    el = &scope->se_u.se_while.ws_end_label;
	    break;
	}
	if (scope->se_type == TRY_SCOPE)
	    ++try_scopes;
	scope = scope->se_outer;
    }

    if (try_scopes > 0)


	generate_TRYCONT(cctx, try_scopes, cctx->ctx_instr.ga_len + 1);


    if (compile_jump_to_end(el, JUMP_ALWAYS, cctx) == FAIL)
	return FAIL;

    return arg;
}
