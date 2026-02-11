bpchar_input(const char *s, size_t len, int32 atttypmod)
{
	BpChar	   *result;
	char	   *r;
	size_t		maxlen;


	if (atttypmod < (int32) VARHDRSZ)
		maxlen = len;
	else
	{
		size_t		charlen;

		maxlen = atttypmod - VARHDRSZ;
		charlen = pg_mbstrlen_with_len(s, len);
		if (charlen > maxlen)
		{

			size_t		mbmaxlen = pg_mbcharcliplen(s, len, maxlen);
			size_t		j;


			for (j = mbmaxlen; j < len; j++)
			{
				if (s[j] != ' ')
					ereport(ERROR,
							(errcode(ERRCODE_STRING_DATA_RIGHT_TRUNCATION),
							 errmsg("value too long for type character(%d)",
									(int) maxlen)));
			}


			maxlen = len = mbmaxlen;
		}
		else
		{


			maxlen = len + (maxlen - charlen);
		}
	}

	result = (BpChar *) palloc(maxlen + VARHDRSZ);
	SET_VARSIZE(result, maxlen + VARHDRSZ);
	r = VARDATA(result);
	memcpy(r, s, len);


	if (maxlen > len)
		memset(r + len, ' ', maxlen - len);

	return result;
}
