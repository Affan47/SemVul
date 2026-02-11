ToInteger(const RakWString &rs)
{
	unsigned long hash = 0;
	int c;

	const char *str = (const char *)rs.C_String();
	size_t i;
	for (i=0; i < rs.GetLength()*MAX_BYTES_PER_UNICODE_CHAR*sizeof(wchar_t); i++)
	{
		c = *str++;
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}
