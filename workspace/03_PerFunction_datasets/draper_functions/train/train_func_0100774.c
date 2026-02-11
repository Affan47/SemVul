is_one_or_even(uint32_t a)
{
	if (a == 1)
		return 1;
	if (a & 1)
		return 0;

	return 1;
}
