ins_compl_infercase_gettext(
	char_u	*str,
	int	char_len,
	int	compl_char_len,
	int	min_len,
	char_u  **tofree)
{
    int		*wca;
    char_u	*p;
    int		i, c;
    int		has_lower = FALSE;
    int		was_letter = FALSE;
    garray_T	gap;

    IObuff[0] = NUL;


    wca = ALLOC_MULT(int, char_len);
    if (wca == NULL)
	return IObuff;

    p = str;
    for (i = 0; i < char_len; ++i)
	if (has_mbyte)
	    wca[i] = mb_ptr2char_adv(&p);
	else
	    wca[i] = *(p++);


    p = compl_orig_text;
    for (i = 0; i < min_len; ++i)
    {
	if (has_mbyte)
	    c = mb_ptr2char_adv(&p);
	else
	    c = *(p++);
	if (MB_ISLOWER(c))
	{
	    has_lower = TRUE;
	    if (MB_ISUPPER(wca[i]))
	    {

		for (i = compl_char_len; i < char_len; ++i)
		    wca[i] = MB_TOLOWER(wca[i]);
		break;
	    }
	}
    }


    if (!has_lower)
    {
	p = compl_orig_text;
	for (i = 0; i < min_len; ++i)
	{
	    if (has_mbyte)
		c = mb_ptr2char_adv(&p);
	    else
		c = *(p++);
	    if (was_letter && MB_ISUPPER(c) && MB_ISLOWER(wca[i]))
	    {

		for (i = compl_char_len; i < char_len; ++i)
		    wca[i] = MB_TOUPPER(wca[i]);
		break;
	    }
	    was_letter = MB_ISLOWER(c) || MB_ISUPPER(c);
	}
    }


    p = compl_orig_text;
    for (i = 0; i < min_len; ++i)
    {
	if (has_mbyte)
	    c = mb_ptr2char_adv(&p);
	else
	    c = *(p++);
	if (MB_ISLOWER(c))
	    wca[i] = MB_TOLOWER(wca[i]);
	else if (MB_ISUPPER(c))
	    wca[i] = MB_TOUPPER(wca[i]);
    }


    p = IObuff;
    i = 0;
    ga_init2(&gap, 1, 500);
    while (i < char_len)
    {
	if (gap.ga_data != NULL)
	{
	    if (ga_grow(&gap, 10) == FAIL)
	    {
		ga_clear(&gap);
		return (char_u *)"[failed]";
	    }
	    p = (char_u *)gap.ga_data + gap.ga_len;
	    if (has_mbyte)
		gap.ga_len += (*mb_char2bytes)(wca[i++], p);
	    else
	    {
		*p = wca[i++];
		++gap.ga_len;
	    }
	}
	else if ((p - IObuff) + 6 >= IOSIZE)
	{


	    if (ga_grow(&gap, IOSIZE) == FAIL)
		return (char_u *)"[failed]";
	    *p = NUL;
	    STRCPY(gap.ga_data, IObuff);
	    gap.ga_len = (int)STRLEN(IObuff);
	}
	else if (has_mbyte)
	    p += (*mb_char2bytes)(wca[i++], p);
	else
	    *(p++) = wca[i++];
    }
    vim_free(wca);

    if (gap.ga_data != NULL)
    {
	*tofree = gap.ga_data;
	return gap.ga_data;
    }

    *p = NUL;
    return IObuff;
}
