ses_win_rec(fd, fr)
    FILE	*fd;
    frame_T	*fr;
{
    frame_T	*frc;
    int		count = 0;

    if (fr->fr_layout != FR_LEAF)
    {


	frc = ses_skipframe(fr->fr_child);
	if (frc != NULL)
	    while ((frc = ses_skipframe(frc->fr_next)) != NULL)
	    {


		if (put_line(fd, "wincmd _ | wincmd |") == FAIL
			|| put_line(fd, fr->fr_layout == FR_COL
						? "split" : "vsplit") == FAIL)
		    return FAIL;
		++count;
	    }


	if (count > 0 && (fprintf(fd, fr->fr_layout == FR_COL
			? "%dwincmd k" : "%dwincmd h", count) < 0
						      || put_eol(fd) == FAIL))
	    return FAIL;


	frc = ses_skipframe(fr->fr_child);
	while (frc != NULL)
	{
	    ses_win_rec(fd, frc);
	    frc = ses_skipframe(frc->fr_next);

	    if (frc != NULL && put_line(fd, "wincmd w") == FAIL)
		return FAIL;
	}
    }
    return OK;
}
