set_rw_fname(char_u *fname, char_u *sfname)
{
#ifdef FEAT_AUTOCMD
    buf_T	*buf = curbuf;


    if (curbuf->b_p_bl)
	apply_autocmds(EVENT_BUFDELETE, NULL, NULL, FALSE, curbuf);
    apply_autocmds(EVENT_BUFWIPEOUT, NULL, NULL, FALSE, curbuf);
# ifdef FEAT_EVAL
    if (aborting())
	return FAIL;
# endif
    if (curbuf != buf)
    {

	EMSG(_(e_auchangedbuf));
	return FAIL;
    }
#endif

    if (setfname(curbuf, fname, sfname, FALSE) == OK)
	curbuf->b_flags |= BF_NOTEDITED;

#ifdef FEAT_AUTOCMD

    apply_autocmds(EVENT_BUFNEW, NULL, NULL, FALSE, curbuf);
    if (curbuf->b_p_bl)
	apply_autocmds(EVENT_BUFADD, NULL, NULL, FALSE, curbuf);
# ifdef FEAT_EVAL
    if (aborting())
	return FAIL;
# endif


    if (*curbuf->b_p_ft == NUL)
    {
	if (au_has_group((char_u *)"filetypedetect"))
	    (void)do_doautocmd((char_u *)"filetypedetect BufRead", FALSE, NULL);
	do_modelines(0);
    }
#endif

    return OK;
}
