parse_timeout(char *buf, unsigned *timeout)
{
	int i;

	if (buf == NULL) {
		*timeout = IP_VS_TEMPLATE_TIMEOUT;
		return 1;
	}

	if ((i = string_to_number(buf, 0, 86400 * 31)) == -1)
		return 0;

	*timeout = i * (IP_VS_TEMPLATE_TIMEOUT / (6*60));
	return 1;
}
