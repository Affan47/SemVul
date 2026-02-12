sslVerifyProtocolRange(const char *min, const char *max)
{
	Assert(sslVerifyProtocolVersion(min) &&
		   sslVerifyProtocolVersion(max));


	if (min == NULL || max == NULL || strlen(min) == 0 || strlen(max) == 0)
		return true;


	if (pg_strcasecmp(min, "TLSv1") == 0)
		return true;


	if (pg_strcasecmp(max, "TLSv1") == 0)
		return false;


	if (pg_strcasecmp(min, max) > 0)
		return false;

	return true;
}
