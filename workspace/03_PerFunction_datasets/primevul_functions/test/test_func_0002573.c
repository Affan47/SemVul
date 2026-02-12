PQconndefaults(void)
{
	PQExpBufferData errorBuf;
	PQconninfoOption *connOptions;


	initPQExpBuffer(&errorBuf);
	if (PQExpBufferDataBroken(errorBuf))
		return NULL;

	connOptions = conninfo_init(&errorBuf);
	if (connOptions != NULL)
	{

		if (!conninfo_add_defaults(connOptions, NULL))
		{
			PQconninfoFree(connOptions);
			connOptions = NULL;
		}
	}

	termPQExpBuffer(&errorBuf);
	return connOptions;
}
