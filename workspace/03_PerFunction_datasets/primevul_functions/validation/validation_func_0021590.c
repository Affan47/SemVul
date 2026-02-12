static int utf8_encoded_valid_unichar(const char *str)
{
	int len;
	int unichar;
	int i;

	len = utf8_encoded_expected_len(str);
	if (len == 0)
		return -1;


	if (len == 1)
		return 1;


	for (i = 0; i < len; i++)
		if ((str[i] & 0x80) != 0x80)
			return -1;

	unichar = utf8_encoded_to_unichar(str);


	if (utf8_unichar_to_encoded_len(unichar) != len)
		return -1;


	if (!utf8_unichar_valid_range(unichar))
		return -1;

	return len;
}
