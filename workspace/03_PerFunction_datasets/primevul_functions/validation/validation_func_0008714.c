ex_undojoin(exarg_T *eap UNUSED)
{
    if (curbuf->b_u_newhead == NULL)
	return;
    if (curbuf->b_u_curhead != NULL)
    {
	EMSG(_("E790: undojoin is not allowed after undo"));
	return;
    }
    if (!curbuf->b_u_synced)
	return;
    if (get_undolevel() < 0)
	return;
    else

	curbuf->b_u_synced = FALSE;
}
