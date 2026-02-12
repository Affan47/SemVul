expand_wildcards_eval(
    char_u	 **pat,
    int		  *num_file,
    char_u	***file,
    int		   flags)
{
    int		ret = FAIL;
    char_u	*eval_pat = NULL;
    char_u	*exp_pat = *pat;
    char      *ignored_msg;
    int		usedlen;

    if (*exp_pat == '%' || *exp_pat == '#' || *exp_pat == '<')
    {
	++emsg_off;
	eval_pat = eval_vars(exp_pat, exp_pat, &usedlen,
						    NULL, &ignored_msg, NULL);
	--emsg_off;
	if (eval_pat != NULL)
	    exp_pat = concat_str(eval_pat, exp_pat + usedlen);
    }

    if (exp_pat != NULL)
	ret = expand_wildcards(1, &exp_pat, num_file, file, flags);

    if (eval_pat != NULL)
    {
	vim_free(exp_pat);
	vim_free(eval_pat);
    }

    return ret;
}
