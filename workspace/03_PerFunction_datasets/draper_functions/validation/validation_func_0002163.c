in_win_border(wp, vcol)
    win_T	*wp;
    colnr_T	vcol;
{
    int		width1;
    int		width2;

#ifdef FEAT_VERTSPLIT
    if (wp->w_width == 0)
	return FALSE;
#endif
    width1 = W_WIDTH(wp) - win_col_off(wp);
    if ((int)vcol < width1 - 1)
	return FALSE;
    if ((int)vcol == width1 - 1)
	return TRUE;
    width2 = width1 + win_col_off2(wp);
    if (width2 <= 0)
	return FALSE;
    return ((vcol - width1) % width2 == width2 - 1);
}
