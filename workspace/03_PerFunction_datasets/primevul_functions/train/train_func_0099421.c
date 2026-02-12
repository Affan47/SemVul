msg_advance(int col)
{
    if (msg_silent != 0)
    {
	msg_col = col;
	return;
    }
    if (col >= Columns)
	col = Columns - 1;
#ifdef FEAT_RIGHTLEFT
    if (cmdmsg_rl)
	while (msg_col > Columns - col)
	    msg_putchar(' ');
    else
#endif
	while (msg_col < col)
	    msg_putchar(' ');
}
