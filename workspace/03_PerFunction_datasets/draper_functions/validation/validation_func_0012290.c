utf8_aux_count(char ch)
{
	if((ch & 0xe0) == 0xc0)
	{
		return 1;
	}
	else if((ch & 0xf0) == 0xe0)
	{
		return 2;
	}
	else if ((ch & 0xf8) == 0xf0)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}
