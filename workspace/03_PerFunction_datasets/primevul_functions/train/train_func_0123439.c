make_tabpages(int maxcount)
{
    int		count = maxcount;
    int		todo;


    if (count > p_tpm)
	count = p_tpm;


    block_autocmds();

    for (todo = count - 1; todo > 0; --todo)
	if (win_new_tabpage(0) == FAIL)
	    break;

    unblock_autocmds();


    return (count - todo);
}
