detect_noniso (const guchar *text)
{
	guchar c;

	while ((c = *text++) != '\0')
	{
		if (c >= 0x80 && c <= 0x9F)
			return TRUE;
	}
	return FALSE;
}
