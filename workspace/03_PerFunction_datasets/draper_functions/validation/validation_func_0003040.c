TextWidth(const char *text, int min, int max)
{
	if(!picture)
		return 0;
	int ofs, x = 0, i = min;
	while((text[i] != '\0') && (i < max))
	{
		if(text[i] == ' ')
		{
			x += spacew;
			i++;
		}
		else if((text[i] >= START_CHAR) && (text[i] <= max_i))
		{
			ofs = text[i] - START_CHAR;
			x += Spacing[ofs];
			i++;
		}
		else
			i++;
	}
	return x;
}
