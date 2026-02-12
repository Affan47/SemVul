check_mtime(buf_T *buf, stat_T *st)
{
    if (buf->b_mtime_read != 0
	    && time_differs((long)st->st_mtime, buf->b_mtime_read))
    {
	msg_scroll = TRUE;
	msg_silent = 0;

	MSG_ATTR(_("WARNING: The file has been changed since reading it!!!"),
						       HL_ATTR(HLF_E));
	if (ask_yesno((char_u *)_("Do you really want to write to it"),
								 TRUE) == 'n')
	    return FAIL;
	msg_scroll = FALSE;
    }
    return OK;
}
