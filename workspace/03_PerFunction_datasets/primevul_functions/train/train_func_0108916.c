showmap(
    mapblock_T	*mp,
    int		local)
{
    int		len = 1;
    char_u	*mapchars;

    if (message_filtered(mp->m_keys) && message_filtered(mp->m_str))
	return;

    if (msg_didout || msg_silent != 0)
    {
	msg_putchar('\n');
	if (got_int)
	    return;
    }

    mapchars = map_mode_to_chars(mp->m_mode);
    if (mapchars != NULL)
    {
	msg_puts((char *)mapchars);
	len = (int)STRLEN(mapchars);
	vim_free(mapchars);
    }

    while (++len <= 3)
	msg_putchar(' ');


    len = msg_outtrans_special(mp->m_keys, TRUE, 0);
    do
    {
	msg_putchar(' ');
	++len;
    } while (len < 12);

    if (mp->m_noremap == REMAP_NONE)
	msg_puts_attr("*", HL_ATTR(HLF_8));
    else if (mp->m_noremap == REMAP_SCRIPT)
	msg_puts_attr("&", HL_ATTR(HLF_8));
    else
	msg_putchar(' ');

    if (local)
	msg_putchar('@');
    else
	msg_putchar(' ');


    if (*mp->m_str == NUL)
	msg_puts_attr("<Nop>", HL_ATTR(HLF_8));
    else
    {


	char_u *s = vim_strsave(mp->m_str);
	if (s != NULL)
	{
	    vim_unescape_csi(s);
	    msg_outtrans_special(s, FALSE, 0);
	    vim_free(s);
	}
    }
#ifdef FEAT_EVAL
    if (p_verbose > 0)
	last_set_msg(mp->m_script_ctx);
#endif
    out_flush();
}
