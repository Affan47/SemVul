expand_wildcards(
    int		   num_pat,
    char_u	 **pat,
    int		  *num_files,
    char_u	***files,
    int		   flags)
{
    int		retval;
    int		i, j;
    char_u	*p;
    int		non_suf_match;

    retval = gen_expand_wildcards(num_pat, pat, num_files, files, flags);


    if ((flags & EW_KEEPALL) || retval == FAIL)
	return retval;

#ifdef FEAT_WILDIGN


    if (*p_wig)
    {
	char_u	*ffname;


	for (i = 0; i < *num_files; ++i)
	{
	    ffname = FullName_save((*files)[i], FALSE);
	    if (ffname == NULL)
		break;
# ifdef VMS
	    vms_remove_version(ffname);
# endif
	    if (match_file_list(p_wig, (*files)[i], ffname))
	    {

		vim_free((*files)[i]);
		for (j = i; j + 1 < *num_files; ++j)
		    (*files)[j] = (*files)[j + 1];
		--*num_files;
		--i;
	    }
	    vim_free(ffname);
	}


	if (*num_files == 0)
	{
	    VIM_CLEAR(*files);
	    return FAIL;
	}
    }
#endif


    if (*num_files > 1)
    {
	non_suf_match = 0;
	for (i = 0; i < *num_files; ++i)
	{
	    if (!match_suffix((*files)[i]))
	    {


		p = (*files)[i];
		for (j = i; j > non_suf_match; --j)
		    (*files)[j] = (*files)[j - 1];
		(*files)[non_suf_match++] = p;
	    }
	}
    }

    return retval;
}
