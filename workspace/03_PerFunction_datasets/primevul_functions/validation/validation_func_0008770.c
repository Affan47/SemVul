u_undo(int count)
{


    if (curbuf->b_u_synced == FALSE)
    {
	u_sync(TRUE);
	count = 1;
    }

    if (vim_strchr(p_cpo, CPO_UNDO) == NULL)
	undo_undoes = TRUE;
    else
	undo_undoes = !undo_undoes;
    u_doit(count);
}
