u_save(linenr_T top, linenr_T bot)
{
    if (undo_off)
	return OK;

    if (top > curbuf->b_ml.ml_line_count
	    || top >= bot
	    || bot > curbuf->b_ml.ml_line_count + 1)
	return FALSE;

    if (top + 2 == bot)
	u_saveline((linenr_T)(top + 1));

    return (u_savecommon(top, bot, (linenr_T)0, FALSE));
}
