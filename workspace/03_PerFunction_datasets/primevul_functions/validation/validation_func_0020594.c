unblock_autocmds(void)
{
    --autocmd_blocked;

# ifdef FEAT_EVAL


    if (autocmd_blocked == 0
		      && get_vim_var_str(VV_TERMRESPONSE) != old_termresponse)
	apply_autocmds(EVENT_TERMRESPONSE, NULL, NULL, FALSE, curbuf);
# endif
}
