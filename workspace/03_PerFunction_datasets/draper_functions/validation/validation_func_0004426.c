discardTypeList (tokenInfo *const token)
{
	int c = skipToNonWhite ();
	while (isident1 (c))
	{
		readIdentifier (token, c);
		c = skipToNonWhite ();
		if (c == '.'  ||  c == ',')
			c = skipToNonWhite ();
	}
	cppUngetc (c);
}
