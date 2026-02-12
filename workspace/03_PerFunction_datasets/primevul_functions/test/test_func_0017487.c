out_char(unsigned c)
{
#if defined(UNIX) || defined(VMS) || defined(AMIGA) || defined(MACOS_X)
    if (c == '\n')
	out_char('\r');
#endif

    out_buf[out_pos++] = c;


    if (out_pos >= OUT_SIZE || p_wd)
	out_flush();
}
