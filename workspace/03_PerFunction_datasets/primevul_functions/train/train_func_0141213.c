compile_eval(char_u *arg, cctx_T *cctx)
{
    char_u	*p = arg;
    int		name_only;
    long	lnum = SOURCING_LNUM;


    name_only = cmd_is_name_only(arg);

    if (compile_expr0(&p, cctx) == FAIL)
	return NULL;

    if (name_only && lnum == SOURCING_LNUM)
    {
	semsg(_(e_expression_without_effect_str), arg);
	return NULL;
    }


    generate_instr_drop(cctx, ISN_DROP, 1);

    return skipwhite(p);
}
