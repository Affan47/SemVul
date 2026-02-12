show_sb_text(void)
{
    msgchunk_T	*mp;


    mp = msg_sb_start(last_msgchunk);
    if (mp == NULL || mp->sb_prev == NULL)
	vim_beep(BO_MESS);
    else
    {
	do_more_prompt('G');
	wait_return(FALSE);
    }
}
