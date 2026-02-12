ends_in_white(linenr_T lnum)
{
    char_u	*s = ml_get(lnum);
    size_t	l;

    if (*s == NUL)
	return FALSE;


    l = STRLEN(s) - 1;
    return VIM_ISWHITE(s[l]);
}
