process_env(env, is_viminit)
    char_u	*env;
    int		is_viminit;
{
    char_u	*initstr;
    char_u	*save_sourcing_name;
    linenr_T	save_sourcing_lnum;
#ifdef FEAT_EVAL
    scid_T	save_sid;
#endif

    if ((initstr = mch_getenv(env)) != NULL && *initstr != NUL)
    {
	if (is_viminit)
	    vimrc_found(NULL, NULL);
	save_sourcing_name = sourcing_name;
	save_sourcing_lnum = sourcing_lnum;
	sourcing_name = env;
	sourcing_lnum = 0;
#ifdef FEAT_EVAL
	save_sid = current_SID;
	current_SID = SID_ENV;
#endif
	do_cmdline_cmd(initstr);
	sourcing_name = save_sourcing_name;
	sourcing_lnum = save_sourcing_lnum;
#ifdef FEAT_EVAL
	current_SID = save_sid;;
#endif
	return OK;
    }
    return FAIL;
}
