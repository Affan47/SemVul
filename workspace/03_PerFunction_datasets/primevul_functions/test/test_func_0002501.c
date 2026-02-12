parse_int_param(const char *value, int *result, PGconn *conn,
				const char *context)
{
	char	   *end;
	long		numval;

	Assert(value != NULL);

	*result = 0;


	errno = 0;
	numval = strtol(value, &end, 10);


	if (value == end || errno != 0 || numval != (int) numval)
		goto error;


	while (*end != '\0' && isspace((unsigned char) *end))
		end++;

	if (*end != '\0')
		goto error;

	*result = numval;
	return true;

error:
	appendPQExpBuffer(&conn->errorMessage,
					  libpq_gettext("invalid integer value \"%s\" for connection option \"%s\"\n"),
					  value, context);
	return false;
}
