scanf_fmt_to_regpat(
	char_u	**pefmp,
	char_u	*efm,
	int	len,
	char_u	*regpat)
{
    char_u	*efmp = *pefmp;

    if (*efmp == '[' || *efmp == '\\')
    {
	if ((*regpat++ = *efmp) == '[')
	{
	    if (efmp[1] == '^')
		*regpat++ = *++efmp;
	    if (efmp < efm + len)
	    {
		*regpat++ = *++efmp;
		while (efmp < efm + len
			&& (*regpat++ = *++efmp) != ']')

		if (efmp == efm + len)
		{
		    emsg(_(e_missing_rsb_in_format_string));
		    return NULL;
		}
	    }
	}
	else if (efmp < efm + len)
	    *regpat++ = *++efmp;
	*regpat++ = '\\';
	*regpat++ = '+';
    }
    else
    {

	semsg(_(e_unsupported_chr_in_format_string), *efmp);
	return NULL;
    }

    *pefmp = efmp;

    return regpat;
}
