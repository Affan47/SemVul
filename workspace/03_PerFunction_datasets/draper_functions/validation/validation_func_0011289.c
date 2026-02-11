highest_bss_symbol(void)
{
	struct syment *sp;
	ulong highest = 0;

	for (sp = st->symtable; sp < st->symend; sp++) {
		if ((sp->type == 'b') || (sp->type == 'B')) {
			if (sp->value > highest)
				highest = sp->value;
		}
	}
	return highest;
}
