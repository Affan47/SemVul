may_open_tabpage(void)
{
    int		n = (cmdmod.tab == 0) ? postponed_split_tab : cmdmod.tab;

    if (n != 0)
    {
	cmdmod.tab = 0;
	postponed_split_tab = 0;
	return win_new_tabpage(n);
    }
    return FAIL;
}
