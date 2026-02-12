u_sync(
    int	    force)
{

    if (curbuf->b_u_synced || (!force && no_u_sync > 0))
	return;
#if defined(FEAT_XIM) && defined(FEAT_GUI_GTK)
    if (im_is_preediting())
	return;
#endif
    if (get_undolevel() < 0)
	curbuf->b_u_synced = TRUE;
    else
    {
	u_getbot();
	curbuf->b_u_curhead = NULL;
    }
}
