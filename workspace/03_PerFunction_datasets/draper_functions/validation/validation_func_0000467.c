hexToInt(char s[], int len)
{
	int i = 0;
	int convert = -1;
	int value = 0;


	while (i < len)
	{
		if (s[i] != '0' || (i == 1 && toupper((int)s[i]) != 'X'))
			break;

		++i;
	}


	while (i < len)
	{
		convert = hexCharToInt((unsigned char)s[i]);


		if (convert == -1)
			return -1;

		value = (value * HEX_BASE) + convert;

		++i;
	}


	return value;
}
