get_str(Pe *pe, char *strnum)
{
	size_t sz;
	unsigned long num;
	char *strtab;
	uint32_t strtabsz;


	sz = strnlen(strnum, 11);
	if (sz == 11)
		return NULL;

	errno = 0;
	num = strtoul(strnum, NULL, 10);
	if (errno != 0)
		return NULL;

	strtab = get_strtab(pe);
	if (!strtab)
		return NULL;

	strtabsz = *(uint32_t *)strtab;
	if (num >= strtabsz)
		return NULL;

	if (strnlen(&strtab[num], strtabsz - num) > strtabsz - num - 1)
		return NULL;

	return &strtab[num];
}
