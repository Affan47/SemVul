clip_free_selection(cbd)
    VimClipboard	*cbd;
{
    struct yankreg *y_ptr = y_current;

    if (cbd == &clip_plus)
	y_current = &y_regs[PLUS_REGISTER];
    else
	y_current = &y_regs[STAR_REGISTER];
    free_yank_all();
    y_current->y_size = 0;
    y_current = y_ptr;
}
