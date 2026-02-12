soundfold_find(slang_T *slang, char_u *word)
{
    idx_T	arridx = 0;
    int		len;
    int		wlen = 0;
    int		c;
    char_u	*ptr = word;
    char_u	*byts;
    idx_T	*idxs;
    int		wordnr = 0;

    byts = slang->sl_sbyts;
    idxs = slang->sl_sidxs;

    for (;;)
    {

	len = byts[arridx++];


	c = ptr[wlen];
	if (byts[arridx] == NUL)
	{
	    if (c == NUL)
		break;


	    while (len > 0 && byts[arridx] == NUL)
	    {
		++arridx;
		--len;
	    }
	    if (len == 0)
		return -1;
	    ++wordnr;
	}


	if (c == NUL)
	    return -1;


	if (c == TAB)
	    c = ' ';
	while (byts[arridx] < c)
	{

	    wordnr += idxs[idxs[arridx]];
	    ++arridx;
	    if (--len == 0)
		return -1;
	}
	if (byts[arridx] != c)
	    return -1;


	arridx = idxs[arridx];
	++wlen;


	if (c == ' ')
	    while (ptr[wlen] == ' ' || ptr[wlen] == TAB)
		++wlen;
    }

    return wordnr;
}
