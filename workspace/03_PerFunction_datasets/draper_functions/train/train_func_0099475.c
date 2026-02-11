varchar(PG_FUNCTION_ARGS)
{
	VarChar    *source = PG_GETARG_VARCHAR_PP(0);
	int32		typmod = PG_GETARG_INT32(1);
	bool		isExplicit = PG_GETARG_BOOL(2);
	VarChar    *result;
	int32		len,
				maxlen;
	size_t		maxmblen;
	int			i;
	char	   *s_data;

	len = VARSIZE_ANY_EXHDR(source);
	s_data = VARDATA_ANY(source);
	maxlen = typmod - VARHDRSZ;


	if (maxlen < 0 || len <= maxlen)
		PG_RETURN_VARCHAR_P(source);


	maxmblen = pg_mbcharcliplen(s_data, len, maxlen);

	if (!isExplicit)
	{
		for (i = maxmblen; i < len; i++)
			if (s_data[i] != ' ')
				ereport(ERROR,
						(errcode(ERRCODE_STRING_DATA_RIGHT_TRUNCATION),
					  errmsg("value too long for type character varying(%d)",
							 maxlen)));
	}

	result = palloc(maxmblen + VARHDRSZ);
	SET_VARSIZE(result, maxmblen + VARHDRSZ);
	memcpy(VARDATA(result), s_data, maxmblen);

	PG_RETURN_VARCHAR_P(result);
}
