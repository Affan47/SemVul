can_compound(slang_T *slang, char_u *word, char_u *flags)
{
    char_u	uflags[MAXWLEN * 2];
    int		i;
    char_u	*p;

    if (slang->sl_compprog == NULL)
	return FALSE;
    if (enc_utf8)
    {

	p = uflags;
	for (i = 0; flags[i] != NUL; ++i)
	    p += utf_char2bytes(flags[i], p);
	*p = NUL;
	p = uflags;
    }
    else
	p = flags;
    if (!vim_regexec_prog(&slang->sl_compprog, FALSE, p, 0))
	return FALSE;


    if (slang->sl_compsylmax < MAXWLEN
		       && count_syllables(slang, word) > slang->sl_compsylmax)
	return (int)STRLEN(flags) < slang->sl_compmax;
    return TRUE;
}
