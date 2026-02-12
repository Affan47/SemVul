win_split(int size, int flags)
{
    if (ERROR_IF_POPUP_WINDOW)
	return FAIL;


    if (may_open_tabpage() == OK)
	return OK;


    flags |= cmdmod.split;
    if ((flags & WSP_TOP) && (flags & WSP_BOT))
    {
	emsg(_("E442: Can't split topleft and botright at the same time"));
	return FAIL;
    }
    if (check_split_disallowed() == FAIL)
	return FAIL;


    if (flags & WSP_HELP)
	make_snapshot(SNAP_HELP_IDX);
    else
	clear_snapshot(curtab, SNAP_HELP_IDX);

    return win_split_ins(size, flags, NULL, 0);
}
