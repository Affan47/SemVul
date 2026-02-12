ins_ctrl_v(void)
{
    int		c;
    int		did_putchar = FALSE;
    int		prev_mod_mask = mod_mask;


    ins_redraw(FALSE);

    if (redrawing() && !char_avail())
    {
	edit_putchar('^', TRUE);
	did_putchar = TRUE;
    }
    AppendToRedobuff((char_u *)CTRL_V_STR);

#ifdef FEAT_CMDL_INFO
    add_to_showcmd_c(Ctrl_V);
#endif

    c = get_literal();
    if (did_putchar)


	edit_unputchar();
#ifdef FEAT_CMDL_INFO
    clear_showcmd();
#endif

    if ((c == ESC || c == CSI) && !(prev_mod_mask & MOD_MASK_SHIFT))


	c = decodeModifyOtherKeys(c);

    insert_special(c, FALSE, TRUE);
#ifdef FEAT_RIGHTLEFT
    revins_chars++;
    revins_legal++;
#endif
}
