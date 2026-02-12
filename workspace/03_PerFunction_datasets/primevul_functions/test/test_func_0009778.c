alert_match_word (char *word, char *masks)
{
	char *p = masks;
	char endchar;
	int res;

	if (masks[0] == 0)
		return FALSE;

	while (1)
	{

		if (*p == 0 || *p == ' ' || *p == ',')
		{
			endchar = *p;
			*p = 0;
			res = match (masks, word);
			*p = endchar;

			if (res)
				return TRUE;

			masks = p + 1;
			if (*p == 0)
				return FALSE;
		}
		p++;
	}
}
