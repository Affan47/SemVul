match_file_pat(
    char_u	*pattern,
    regprog_T	**prog,
    char_u	*fname,
    char_u	*sfname,
    char_u	*tail,
    int		allow_dirs)
{
    regmatch_T	regmatch;
    int		result = FALSE;

    regmatch.rm_ic = p_fic;
    if (prog != NULL)
	regmatch.regprog = *prog;
    else
	regmatch.regprog = vim_regcomp(pattern, RE_MAGIC);


    if (regmatch.regprog != NULL
	     && ((allow_dirs
		     && (vim_regexec(&regmatch, fname, (colnr_T)0)
			 || (sfname != NULL
			     && vim_regexec(&regmatch, sfname, (colnr_T)0))))
		 || (!allow_dirs && vim_regexec(&regmatch, tail, (colnr_T)0))))
	result = TRUE;

    if (prog != NULL)
	*prog = regmatch.regprog;
    else
	vim_regfree(regmatch.regprog);
    return result;
}
