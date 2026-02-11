ins_ctrl_v()
{
    int		c;


    ins_redraw(FALSE);

    if (redrawing() && !char_avail())
	edit_putchar('^', TRUE);
    AppendToRedobuff((char_u *)CTRL_V_STR);

#ifdef FEAT_CMDL_INFO
    add_to_showcmd_c(Ctrl_V);
#endif

    c = get_literal();
#ifdef FEAT_CMDL_INFO
    clear_showcmd();
#endif
    insert_special(c, FALSE, TRUE);
#ifdef FEAT_RIGHTLEFT
    revins_chars++;
    revins_legal++;
#endif
}
