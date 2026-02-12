out_str(char_u *s)
{
    if (s != NULL && *s)
    {
#ifdef FEAT_GUI

	if (gui.in_use)
	{
	    out_str_nf(s);
	    return;
	}
#endif

	if (out_pos > OUT_SIZE - MAX_ESC_SEQ_LEN)
	    out_flush();
#ifdef HAVE_TGETENT
	tputs((char *)s, 1, TPUTSFUNCAST out_char_nf);
#else
	while (*s)
	    out_char_nf(*s++);
#endif


	if (p_wd)
	    out_flush();
    }
}
