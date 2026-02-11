SubstituteChar(Translator *tr, unsigned int c, unsigned int next_in, int *insert)
{
	int ix;
	unsigned int word;
	unsigned int new_c, c2, c_lower;
	int upper_case = 0;
	static int ignore_next = 0;
	const unsigned int *replace_chars;

	if(ignore_next)
	{
		ignore_next = 0;
		return(8);
	}
	if(c == 0) return(0);

	if((replace_chars = tr->langopts.replace_chars) == NULL)
		return(c);


	if(iswupper(c_lower = c))
	{
		c_lower = towlower(c);
		upper_case = 1;
	}

	new_c = 0;
	for(ix=0; (word = replace_chars[ix]) != 0; ix+=2)
	{
		if(c_lower == (word & 0xffff))
		{
			if((word >> 16) == 0)
			{
				new_c = replace_chars[ix+1];
				break;
			}
			if((word >> 16) == (unsigned int)towlower(next_in))
			{
				new_c = replace_chars[ix+1];
				ignore_next = 1;
				break;
			}
		}
	}

	if(new_c == 0)
		return(c);

	if(new_c & 0xffe00000)
	{


		c2 = new_c >> 16;
		if(upper_case && iswupper(next_in))
			c2 = towupper(c2);
		*insert = c2;
		new_c &= 0xffff;
	}

	if(upper_case)
		new_c = towupper(new_c);
	return(new_c);

}
