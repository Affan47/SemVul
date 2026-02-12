fix_input_buffer(char_u *buf, int len)
{
    int		i;
    char_u	*p = buf;


    for (i = len; --i >= 0; ++p)
    {
#ifdef FEAT_GUI


	if (gui.in_use && p[0] == CSI && i >= 2)
	{
	    p += 2;
	    i -= 2;
	}
# ifndef MSWIN

	else if (!gui.in_use && p[0] == CSI)
	{
	    mch_memmove(p + 3, p + 1, (size_t)i);
	    *p++ = K_SPECIAL;
	    *p++ = KS_EXTRA;
	    *p = (int)KE_CSI;
	    len += 2;
	}
# endif
	else
#endif
	if (p[0] == NUL || (p[0] == K_SPECIAL

		    && (i < 2 || p[1] != KS_EXTRA || p[2] != (int)KE_CURSORHOLD)
#if defined(MSWIN) && (!defined(FEAT_GUI) || defined(VIMDLL))

		    && (
# ifdef VIMDLL
			gui.in_use ||
# endif
			(i < 2 || p[1] != KS_MODIFIER))
#endif
		    ))
	{
	    mch_memmove(p + 3, p + 1, (size_t)i);
	    p[2] = K_THIRD(p[0]);
	    p[1] = K_SECOND(p[0]);
	    p[0] = K_SPECIAL;
	    p += 2;
	    len += 2;
	}
    }
    *p = NUL;
    return len;
}
