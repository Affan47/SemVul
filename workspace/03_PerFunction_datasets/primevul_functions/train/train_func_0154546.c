find_viminfo_parameter(int type)
{
    char_u  *p;

    for (p = p_viminfo; *p; ++p)
    {
	if (*p == type)
	    return p + 1;
	if (*p == 'n')
	    break;
	p = vim_strchr(p, ',');
	if (p == NULL)
	    break;
    }
    return NULL;
}
