bin(const char *str)
{
	int ret = 0;

	if (!str)
		return set_errno(EINVAL);

	if (str[0] == '0' && str[1] == 'b')
		str += 2;

	for (; *str; ++str)
	{
		ret <<= 1;

		switch (*str)
		{
			case '0': break;
			case '1': ret |= 1; break;
			default:  return set_errno(EINVAL);
		}
	}

	return ret;
}
