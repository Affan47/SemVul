compile_endwhile(char_u *arg, cctx_T *cctx)
{
    scope_T	*scope = cctx->ctx_scope;
    garray_T	*instr = &cctx->ctx_instr;

    if (misplaced_cmdmod(cctx))
	return NULL;
    if (scope == NULL || scope->se_type != WHILE_SCOPE)
    {
	emsg(_(e_endwhile_without_while));
	return NULL;
    }
    cctx->ctx_scope = scope->se_outer;
    if (cctx->ctx_skip != SKIP_YES)
    {
	unwind_locals(cctx, scope->se_local_count);

#ifdef FEAT_PROFILE

	may_generate_prof_end(cctx, cctx->ctx_lnum);
#endif


	generate_JUMP(cctx, JUMP_ALWAYS, scope->se_u.se_while.ws_top_label);


	compile_fill_jump_to_end(&scope->se_u.se_while.ws_end_label,
							  instr->ga_len, cctx);
    }

    vim_free(scope);

    return arg;
}
