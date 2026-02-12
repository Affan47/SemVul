match_zref(
    int		subidx,
    int		*bytelen)
{
    int		len;

    cleanup_zsubexpr();
    if (re_extmatch_in == NULL || re_extmatch_in->matches[subidx] == NULL)
    {

	*bytelen = 0;
	return TRUE;
    }

    len = (int)STRLEN(re_extmatch_in->matches[subidx]);
    if (cstrncmp(re_extmatch_in->matches[subidx], rex.input, &len) == 0)
    {
	*bytelen = len;
	return TRUE;
    }
    return FALSE;
}
