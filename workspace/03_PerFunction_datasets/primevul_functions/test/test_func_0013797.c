cmd_source(char_u *fname, exarg_T *eap)
{
    int clearvars = FALSE;

    if (*fname != NUL && STRNCMP(fname, "++clear", 7) == 0)
    {

	clearvars = TRUE;
	fname = fname + 7;
	if (*fname != NUL)
	{
	    semsg(_(e_invalid_argument_str), eap->arg);
	    return;
	}
    }

    if (*fname != NUL && eap != NULL && eap->addr_count > 0)
    {

	emsg(_(e_no_range_allowed));
	return;
    }

    if (eap != NULL && *fname == NUL)
    {
	if (eap->forceit)

	    emsg(_(e_argument_required));
	else

	    do_source_ext(NULL, FALSE, FALSE, NULL, eap, clearvars);
    }
    else if (eap != NULL && eap->forceit)


	openscript(fname, global_busy || listcmd_busy || eap->nextcmd != NULL
#ifdef FEAT_EVAL
						 || eap->cstack->cs_idx >= 0
#endif
						 );


    else if (do_source(fname, FALSE, DOSO_NONE, NULL) == FAIL)
	semsg(_(e_cant_open_file_str), fname);
}
