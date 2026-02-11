ex_cfile(eap)
    exarg_T	*eap;
{
    win_T	*wp = NULL;
    qf_info_T	*qi = &ql_info;
#ifdef FEAT_AUTOCMD
    char_u	*au_name = NULL;
#endif

    if (eap->cmdidx == CMD_lfile || eap->cmdidx == CMD_lgetfile
					       || eap->cmdidx == CMD_laddfile)
	wp = curwin;

#ifdef FEAT_AUTOCMD
    switch (eap->cmdidx)
    {
	case CMD_cfile:	    au_name = (char_u *)"cfile"; break;
	case CMD_cgetfile:  au_name = (char_u *)"cgetfile"; break;
	case CMD_caddfile:  au_name = (char_u *)"caddfile"; break;
	case CMD_lfile:	    au_name = (char_u *)"lfile"; break;
	case CMD_lgetfile:  au_name = (char_u *)"lgetfile"; break;
	case CMD_laddfile:  au_name = (char_u *)"laddfile"; break;
	default: break;
    }
    if (au_name != NULL)
	apply_autocmds(EVENT_QUICKFIXCMDPRE, au_name, NULL, FALSE, curbuf);
#endif
#ifdef FEAT_BROWSE
    if (cmdmod.browse)
    {
	char_u *browse_file = do_browse(0, (char_u *)_("Error file"), eap->arg,
				   NULL, NULL, BROWSE_FILTER_ALL_FILES, NULL);
	if (browse_file == NULL)
	    return;
	set_string_option_direct((char_u *)"ef", -1, browse_file, OPT_FREE, 0);
	vim_free(browse_file);
    }
    else
#endif
    if (*eap->arg != NUL)
	set_string_option_direct((char_u *)"ef", -1, eap->arg, OPT_FREE, 0);


    if (qf_init(wp, p_ef, p_efm, (eap->cmdidx != CMD_caddfile
				  && eap->cmdidx != CMD_laddfile),
							   *eap->cmdlinep) > 0
				  && (eap->cmdidx == CMD_cfile
					     || eap->cmdidx == CMD_lfile))
    {
#ifdef FEAT_AUTOCMD
	if (au_name != NULL)
	    apply_autocmds(EVENT_QUICKFIXCMDPOST, au_name, NULL, FALSE, curbuf);
#endif
	if (wp != NULL)
	    qi = GET_LOC_LIST(wp);
	qf_jump(qi, 0, 0, eap->forceit);
    }

    else
    {
#ifdef FEAT_AUTOCMD
	if (au_name != NULL)
	    apply_autocmds(EVENT_QUICKFIXCMDPOST, au_name, NULL, FALSE, curbuf);
#endif
    }
}
