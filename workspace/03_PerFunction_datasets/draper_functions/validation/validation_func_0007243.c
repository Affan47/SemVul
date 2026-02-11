set_table_flags(cgats *p, int table, int sup_id, int sup_kwords, int sup_fields) {
	cgats_table *t;

	p->errc = 0;
	p->err[0] = '\000';
	if (table < 0 || table >= p->ntables)
		return err(p,-1, "cgats.set_table_flags(), table number '%d' is out of range",table);
	t = &p->t[table];

	if (sup_id == 0 && (sup_kwords != 0 || sup_fields != 0))
		return err(p,-1, "cgats.set_table_flags(), Can't suppress kwords or fields if ID is not suppressed");
	t->sup_id = sup_id;
	t->sup_kwords = sup_kwords;
	t->sup_fields = sup_fields;

	return 0;
}
