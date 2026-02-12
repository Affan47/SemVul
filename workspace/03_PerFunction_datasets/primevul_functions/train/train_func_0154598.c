compile_cap_prog(synblock_T *synblock)
{
    regprog_T   *rp = synblock->b_cap_prog;
    char_u	*re;

    if (*synblock->b_p_spc == NUL)
	synblock->b_cap_prog = NULL;
    else
    {

	re = concat_str((char_u *)"^", synblock->b_p_spc);
	if (re != NULL)
	{
	    synblock->b_cap_prog = vim_regcomp(re, RE_MAGIC);
	    vim_free(re);
	    if (synblock->b_cap_prog == NULL)
	    {
		synblock->b_cap_prog = rp;
		return e_invarg;
	    }
	}
    }

    vim_regfree(rp);
    return NULL;
}
