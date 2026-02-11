ExpandEscape(xp, str, numfiles, files, options)
    expand_T	*xp;
    char_u	*str;
    int		numfiles;
    char_u	**files;
    int		options;
{
    int		i;
    char_u	*p;


    if (options & WILD_HOME_REPLACE)
	tilde_replace(str, numfiles, files);

    if (options & WILD_ESCAPE)
    {
	if (xp->xp_context == EXPAND_FILES
		|| xp->xp_context == EXPAND_SHELLCMD
		|| xp->xp_context == EXPAND_BUFFERS
		|| xp->xp_context == EXPAND_DIRECTORIES)
	{


	    for (i = 0; i < numfiles; ++i)
	    {

		if (xp->xp_backslash == XP_BS_THREE)
		{
		    p = vim_strsave_escaped(files[i], (char_u *)" ");
		    if (p != NULL)
		    {
			vim_free(files[i]);
			files[i] = p;
#if defined(BACKSLASH_IN_FILENAME)
			p = vim_strsave_escaped(files[i], (char_u *)" ");
			if (p != NULL)
			{
			    vim_free(files[i]);
			    files[i] = p;
			}
#endif
		    }
		}
#ifdef BACKSLASH_IN_FILENAME
		p = vim_strsave_fnameescape(files[i], FALSE);
#else
		p = vim_strsave_fnameescape(files[i], xp->xp_shell);
#endif
		if (p != NULL)
		{
		    vim_free(files[i]);
		    files[i] = p;
		}


		if (str[0] == '\\' && str[1] == '~' && files[i][0] == '~')
		    escape_fname(&files[i]);
	    }
	    xp->xp_backslash = XP_BS_NONE;


	    if (*files[0] == '+')
		escape_fname(&files[0]);
	}
	else if (xp->xp_context == EXPAND_TAGS)
	{


	    for (i = 0; i < numfiles; ++i)
	    {
		p = vim_strsave_escaped(files[i], (char_u *)"\\|\"");
		if (p != NULL)
		{
		    vim_free(files[i]);
		    files[i] = p;
		}
	    }
	}
    }
}
