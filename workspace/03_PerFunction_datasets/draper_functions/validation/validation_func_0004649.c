network_show(PG_FUNCTION_ARGS)
{
	inet	   *ip = PG_GETARG_INET_P(0);
	text	   *ret;
	int			len;
	char		tmp[sizeof("xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255/128")];

	if (inet_net_ntop(ip_family(ip), ip_addr(ip), ip_maxbits(ip),
					  tmp, sizeof(tmp)) == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_BINARY_REPRESENTATION),
				 errmsg("could not format inet value: %m")));


	if (strchr(tmp, '/') == NULL)
	{
		len = strlen(tmp);
		snprintf(tmp + len, sizeof(tmp) - len, "/%u", ip_bits(ip));
	}


	len = strlen(tmp);
	ret = (text *) palloc(len + VARHDRSZ);
	SET_VARSIZE(ret, len + VARHDRSZ);
	memcpy(VARDATA(ret), tmp, len);
	PG_RETURN_TEXT_P(ret);
}
