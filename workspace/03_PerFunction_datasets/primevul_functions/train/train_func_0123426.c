frame_fixed_height(frame_T *frp)
{

    if (frp->fr_win != NULL)
	return frp->fr_win->w_p_wfh;

    if (frp->fr_layout == FR_ROW)
    {


	FOR_ALL_FRAMES(frp, frp->fr_child)
	    if (frame_fixed_height(frp))
		return TRUE;
	return FALSE;
    }


    FOR_ALL_FRAMES(frp, frp->fr_child)
	if (!frame_fixed_height(frp))
	    return FALSE;
    return TRUE;
}
