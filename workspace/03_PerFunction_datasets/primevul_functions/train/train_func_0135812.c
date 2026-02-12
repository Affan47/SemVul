static BOOL rdg_skip_seed_payload(rdpTls* tls, SSIZE_T lastResponseLength)
{
	BYTE seed_payload[10];
	const size_t size = sizeof(seed_payload);

	assert(size < SSIZE_MAX);


	if (lastResponseLength < (SSIZE_T)size)
	{
		if (!rdg_read_all(tls, seed_payload, size - lastResponseLength))
		{
			return FALSE;
		}
	}

	return TRUE;
}
