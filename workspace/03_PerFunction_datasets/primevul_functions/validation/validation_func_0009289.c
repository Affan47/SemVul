post_chdir(cdscope_T scope)
{
    if (scope != CDSCOPE_WINDOW)

	VIM_CLEAR(curtab->tp_localdir);
    VIM_CLEAR(curwin->w_localdir);
    if (scope != CDSCOPE_GLOBAL)
    {
	char_u	*pdir = get_prevdir(scope);


	if (globaldir == NULL && pdir != NULL)
	    globaldir = vim_strsave(pdir);


	if (mch_dirname(NameBuff, MAXPATHL) == OK)
	{
	    if (scope == CDSCOPE_TABPAGE)
		curtab->tp_localdir = vim_strsave(NameBuff);
	    else
		curwin->w_localdir = vim_strsave(NameBuff);
	}
    }
    else
    {

	VIM_CLEAR(globaldir);
    }

    shorten_fnames(TRUE);
}
