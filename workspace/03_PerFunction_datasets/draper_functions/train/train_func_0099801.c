menu_text(str, mnemonic, actext)
    char_u	*str;
    int		*mnemonic;
    char_u	**actext;
{
    char_u	*p;
    char_u	*text;


    p = vim_strchr(str, TAB);
    if (p != NULL)
    {
	if (actext != NULL)
	    *actext = vim_strsave(p + 1);
	text = vim_strnsave(str, (int)(p - str));
    }
    else
	text = vim_strsave(str);


    for (p = text; p != NULL; )
    {
	p = vim_strchr(p, '&');
	if (p != NULL)
	{
	    if (p[1] == NUL)
		break;
	    if (mnemonic != NULL && p[1] != '&')
#if !defined(__MVS__) || defined(MOTIF390_MNEMONIC_FIXED)
		*mnemonic = p[1];
#else
	    {


		char c = p[1];
		__etoa_l(&c, 1);
		*mnemonic = c;
	    }
#endif
	    STRMOVE(p, p + 1);
	    p = p + 1;
	}
    }
    return text;
}
