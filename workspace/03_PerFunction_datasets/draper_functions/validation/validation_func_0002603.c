compare_symbols(const void *a, const void *b)
{
	const struct sym_entry *sa;
	const struct sym_entry *sb;
	int wa, wb;

	sa = a;
	sb = b;


	if (sa->addr > sb->addr)
		return 1;
	if (sa->addr < sb->addr)
		return -1;


	wa = (sa->sym[0] == 'w') || (sa->sym[0] == 'W');
	wb = (sb->sym[0] == 'w') || (sb->sym[0] == 'W');
	if (wa != wb)
		return wa - wb;


	return sa->start_pos - sb->start_pos;
}
