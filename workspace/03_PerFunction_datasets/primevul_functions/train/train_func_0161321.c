compile_expr2(char_u **arg, cctx_T *cctx, ppconst_T *ppconst)
{
    int		ppconst_used = ppconst->pp_used;


    if (compile_expr3(arg, cctx, ppconst) == FAIL)
	return FAIL;


    return compile_and_or(arg, cctx, "||", ppconst, ppconst_used);
}
