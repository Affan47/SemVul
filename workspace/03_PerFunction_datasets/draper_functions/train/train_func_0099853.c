ex_undojoin(eap)
    exarg_T *eap UNUSED;
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
    if (p_ul < 0)
	return;
    else
    {

	curbuf->b_u_curhead = curbuf->b_u_newhead;
	curbuf->b_u_synced = FALSE;
    }
}
