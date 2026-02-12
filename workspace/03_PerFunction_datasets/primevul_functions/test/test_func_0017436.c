ins_eol(int c)
{
    int	    i;

    if (echeck_abbr(c + ABBR_OFF))
	return OK;
    if (stop_arrow() == FAIL)
	return FAIL;
    undisplay_dollar();


    if ((State & REPLACE_FLAG) && !(State & VREPLACE_FLAG))
	replace_push(NUL);


    if (virtual_active() && curwin->w_cursor.coladd > 0)
	coladvance(getviscol());

#ifdef FEAT_RIGHTLEFT


    if (revins_on)
	curwin->w_cursor.col += (colnr_T)STRLEN(ml_get_cursor());
#endif

    AppendToRedobuff(NL_STR);
    i = open_line(FORWARD,
	    has_format_option(FO_RET_COMS) ? OPENLINE_DO_COM : 0, old_indent,
	    NULL);
    old_indent = 0;
#ifdef FEAT_CINDENT
    can_cindent = TRUE;
#endif
#ifdef FEAT_FOLDING

    foldOpenCursor();
#endif

    return i;
}
