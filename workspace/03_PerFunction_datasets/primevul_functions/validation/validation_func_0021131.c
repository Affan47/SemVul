read_charflags_section(FILE *fd)
{
    char_u	*flags;
    char_u	*fol;
    int		flagslen, follen;


    flags = read_cnt_string(fd, 1, &flagslen);
    if (flagslen < 0)
	return flagslen;


    fol = read_cnt_string(fd, 2, &follen);
    if (follen < 0)
    {
	vim_free(flags);
	return follen;
    }


    if (flags != NULL && fol != NULL)
	set_spell_charflags(flags, flagslen, fol);

    vim_free(flags);
    vim_free(fol);


    if ((flags == NULL) != (fol == NULL))
	return SP_FORMERROR;
    return 0;
}
