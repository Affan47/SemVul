flag_is_inter(const bitflag *flags1, const bitflag *flags2, const size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		if (flags1[i] & flags2[i]) return TRUE;

	return FALSE;
}
