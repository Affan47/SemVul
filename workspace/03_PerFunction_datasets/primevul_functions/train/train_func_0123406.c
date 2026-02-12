frame_fixed_width(frame_T *frp)
{

    if (frp->fr_win != NULL)
	return frp->fr_win->w_p_wfw;

    if (frp->fr_layout == FR_COL)
    {


	FOR_ALL_FRAMES(frp, frp->fr_child)
	    if (frame_fixed_width(frp))
		return TRUE;
	return FALSE;
    }


    FOR_ALL_FRAMES(frp, frp->fr_child)
	if (!frame_fixed_width(frp))
	    return FALSE;
    return TRUE;
}
