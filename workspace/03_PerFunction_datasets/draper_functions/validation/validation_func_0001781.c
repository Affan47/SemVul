symbol_entry_free(struct symbol_entry *se)
{
	symbol_entry_check(se);
	if (se->symbol != NULL)
		nv_pair_free(se->symbol);
	se->magic = 0;
	WFREE(se);
}
