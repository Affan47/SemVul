nfa_regcomp_start(
    char_u	*expr,
    int		re_flags)
{
    size_t	postfix_size;
    int		nstate_max;

    nstate = 0;
    istate = 0;

    nstate_max = (int)(STRLEN(expr) + 1) * 25;


    nstate_max += 1000;


    postfix_size = sizeof(int) * nstate_max;

    post_start = alloc(postfix_size);
    if (post_start == NULL)
	return FAIL;
    post_ptr = post_start;
    post_end = post_start + nstate_max;
    wants_nfa = FALSE;
    rex.nfa_has_zend = FALSE;
    rex.nfa_has_backref = FALSE;


    regcomp_start(expr, re_flags);

    return OK;
}
