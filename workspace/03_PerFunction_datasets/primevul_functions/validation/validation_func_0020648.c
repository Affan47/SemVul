readfile_charconvert(
    char_u	*fname,
    char_u	*fenc,
    int		*fdp)
{
    char_u	*tmpname;
    char_u	*errmsg = NULL;

    tmpname = vim_tempname('r', FALSE);
    if (tmpname == NULL)
	errmsg = (char_u *)_("Can't find temp file for conversion");
    else
    {
	close(*fdp);
	*fdp = -1;
	if (eval_charconvert(fenc, enc_utf8 ? (char_u *)"utf-8" : p_enc,
						      fname, tmpname) == FAIL)
	    errmsg = (char_u *)_("Conversion with 'charconvert' failed");
	if (errmsg == NULL && (*fdp = mch_open((char *)tmpname,
						  O_RDONLY | O_EXTRA, 0)) < 0)
	    errmsg = (char_u *)_("can't read output of 'charconvert'");
    }

    if (errmsg != NULL)
    {


	MSG(errmsg);
	if (tmpname != NULL)
	{
	    mch_remove(tmpname);
	    vim_free(tmpname);
	    tmpname = NULL;
	}
    }


    if (*fdp < 0)
	*fdp = mch_open((char *)fname, O_RDONLY | O_EXTRA, 0);

    return tmpname;
}
